using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace MarbleMazeGame
{
    class Marble : DrawableComponent3D
    {
        private Texture2D m_marbleTexture;
        public Maze Maze { get; set; }
        Matrix rollMatrix = Matrix.Identity;
        Vector3 normal;
        public float angleX;
        public float angleZ;

        public BoundingSphere BoundingSphereTransformed
        {
            get
            {
                BoundingSphere boundingSphere = Model.Meshes[0].BoundingSphere;
                boundingSphere = boundingSphere.Transform(AbsoluteBoneTransforms[0]);
                boundingSphere.Center += Position;
                return boundingSphere;
            }
        }


        public Marble(Game game)
            : base(game, "marble")
        {
            preferPerPixelLighting = true;
        }

        protected override void LoadContent()
        {
            base.LoadContent();

            // Load the texture of the marble
            m_marbleTexture = Game.Content.Load<Texture2D>(@"textures\Marble");
        }

        public override void Draw(GameTime gameTime)
        {
            var originalSamplerState = GraphicsDevice.SamplerStates[0];

            // Cause the marble's textures to linearly clamp            
            GraphicsDevice.SamplerStates[0] = SamplerState.LinearClamp;

            foreach (var mesh in Model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    // Set the effect for drawing the marble
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = preferPerPixelLighting;
                    effect.TextureEnabled = true;
                    effect.Texture = m_marbleTexture;

                    // Apply camera settings
                    effect.Projection = Camera.Projection;
                    effect.View = Camera.View;

                    // Apply necessary transformations
                    effect.World = AbsoluteBoneTransforms[mesh.ParentBone.Index] *
                        FinalWorldTransforms;
                }

                mesh.Draw();
            }

            // Return to the original state
            GraphicsDevice.SamplerStates[0] = originalSamplerState;
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            // Make the camera follow the marble
            Camera.ObjectToFollow = Vector3.Transform(Position,
                Matrix.CreateFromYawPitchRoll(Maze.Rotation.Y,
                Maze.Rotation.X, Maze.Rotation.Z));

            PlaySounds();
        }

        private void PlaySounds()
        {
            // Calculate the pitch by the velocity
            float volumeX = MathHelper.Clamp(Math.Abs(Velocity.X) / 400,
                               0, 1);
            float volumeZ = MathHelper.Clamp(Math.Abs(Velocity.Z) / 400,
                               0, 1);
            float volume = Math.Max(volumeX, volumeZ);
            float pitch = volume - 1.0f;

            // Play the roll sound only if the marble roll on maze
            if (intersectDetails.IntersectWithGround &&
                (Velocity.X != 0 || Velocity.Z != 0))
            {
                if (AudioManager.Instance["rolling"].State !=
                    SoundState.Playing)
                    AudioManager.PlaySound("rolling", true);

                // Update the volume & pitch by the velocity
                AudioManager.Instance["rolling"].Volume =
                    Math.Max(volumeX, volumeZ);
                AudioManager.Instance["rolling"].Pitch = pitch;
            }
            else
            {
                AudioManager.StopSound("rolling");
            }

            // Play fall sound when fall
            if (Position.Y < -50)
            {
                AudioManager.PlaySound("pit");
            }

            // Play collision sound when collide with walls
            if (intersectDetails.IntersectWithWalls)
            {
                AudioManager.PlaySound("collision");
                AudioManager.Instance["collision"].Volume =
                    Math.Max(volumeX, volumeZ);
            }
        }


        protected override void UpdateFinalWorldTransform()
        {
            // Calculate the appropriate rotation matrix to represent the marble
            // rolling inside the maze
            rollMatrix *= Matrix.CreateFromAxisAngle(Vector3.Right, Rotation.Z) *
                Matrix.CreateFromAxisAngle(Vector3.Forward, Rotation.X);

            // Multiply by two matrices which will place the marble in its proper 
            // position and align it to the maze (which tilts due to user input)
            FinalWorldTransforms = rollMatrix *
                        Matrix.CreateTranslation(Position) *
                        Matrix.CreateFromYawPitchRoll(Maze.Rotation.Y,
                        Maze.Rotation.X, Maze.Rotation.Z);
        }

        protected override void CalculateCollisions()
        {
            Maze.GetCollisionDetails(BoundingSphereTransformed, ref intersectDetails, false);

            if (intersectDetails.IntersectWithWalls)
            {
                foreach (var triangle in intersectDetails.IntersectedWallTriangle)
                {
                    Axis direction = CollideDirection(triangle);
                    if ((direction & Axis.X) == Axis.X &&
                        (direction & Axis.Z) == Axis.Z)
                    {
                        Maze.GetCollisionDetails(BoundingSphereTransformed,
                                                 ref intersectDetails, true);
                    }
                }
            }
        }

        protected override void CalculateAcceleration()
        {
            if (intersectDetails.IntersectWithGround)
            {
                // We must take both the maze's tilt and the angle of the floor
                // section beneath the marble into account
                angleX = 0;
                angleZ = 0;
                if (intersectDetails.IntersectedGroundTriangle != null)
                {
                    intersectDetails.IntersectedGroundTriangle.Normal(out normal);
                    angleX = (float)Math.Atan(normal.Y / normal.X);
                    angleZ = (float)Math.Atan(normal.Y / normal.Z);

                    if (angleX > 0)
                    {
                        angleX = MathHelper.PiOver2 - angleX;
                    }
                    else if (angleX < 0)
                    {
                        angleX = -(angleX + MathHelper.PiOver2);
                    }

                    if (angleZ > 0)
                    {
                        angleZ = MathHelper.PiOver2 - angleZ;
                    }
                    else if (angleZ < 0)
                    {
                        angleZ = -(angleZ + MathHelper.PiOver2);
                    }
                }


                // Set the final X, Y and Z axis acceleration for the marble
                Acceleration.X = -gravity * (float)Math.Sin(Maze.Rotation.Z - angleX);
                Acceleration.Z = gravity * (float)Math.Sin(Maze.Rotation.X - angleZ);
                Acceleration.Y = 0;
            }
            else
            {
                // If the marble is not touching the floor, it is falling freely
                Acceleration.Y = -gravity;
            }


            if (intersectDetails.IntersectWithWalls)
            {
                // Change the marble's acceleration due to a collision with a maze
                // wall
                UpdateWallCollisionAcceleration(
                    intersectDetails.IntersectedWallTriangle);
            }
            if (intersectDetails.IntersectWithFloorSides)
            {
                // Change the marble's acceleration due to collision with a pit wall
                UpdateWallCollisionAcceleration(
                    intersectDetails.IntersectedFloorSidesTriangle);
            }
        }

        protected Axis CollideDirection(Triangle collideTriangle)
        {
            if (collideTriangle.A.Z == collideTriangle.B.Z &&
                collideTriangle.B.Z == collideTriangle.C.Z)
            {
                return Axis.Z;
            }
            else if (collideTriangle.A.X == collideTriangle.B.X &&
                collideTriangle.B.X == collideTriangle.C.X)
            {
                return Axis.X;
            }
            else if (collideTriangle.A.Y == collideTriangle.B.Y &&
                collideTriangle.B.Y == collideTriangle.C.Y)
            {
                return Axis.Y;
            }
            return Axis.X | Axis.Z;
        }

        protected void UpdateWallCollisionAcceleration(IEnumerable<Triangle> wallTriangles)
        {
            foreach (var triangle in wallTriangles)
            {
                Axis direction = CollideDirection(triangle);
                // Decrease the acceleration in x-axis of the component
                if ((direction & Axis.X) == Axis.X)
                {
                    if (Velocity.X > 0)
                        Acceleration.X -= wallFriction;
                    else if (Velocity.X < 0)
                        Acceleration.X += wallFriction;
                }

                // Decrease the acceleration in z-axis of the component
                if ((direction & Axis.Z) == Axis.Z)
                {
                    if (Velocity.Z > 0)
                        Acceleration.Z -= wallFriction;
                    else if (Velocity.Z < 0)
                        Acceleration.Z += wallFriction;
                }
            }
        }

        protected override void CalculateFriction()
        {
            if (intersectDetails.IntersectWithGround)
            {
                if (Velocity.X > 0)
                {
                    Acceleration.X -= staticGroundFriction * gravity *
                        (float)Math.Cos(Maze.Rotation.Z - angleX);
                }
                else if (Velocity.X < 0)
                {
                    Acceleration.X += staticGroundFriction * gravity *
                        (float)Math.Cos(Maze.Rotation.Z - angleX);
                }

                if (Velocity.Z > 0)
                {
                    Acceleration.Z -= staticGroundFriction * gravity *
                        (float)Math.Cos(Maze.Rotation.X - angleZ);
                }
                else if (Velocity.Z < 0)
                {
                    Acceleration.Z += staticGroundFriction * gravity *
                        (float)Math.Cos(Maze.Rotation.X - angleZ);
                }

            }
        }

        protected override void CalculateVelocityAndPosition(GameTime gameTime)
        {
            // Calculate the current velocity
            float elapsed = (float)gameTime.ElapsedGameTime.TotalSeconds;

            Vector3 currentVelocity = Velocity;

            Velocity = currentVelocity + (Acceleration * elapsed);

            // Set a bound on the marble's velocity
            Velocity.X = MathHelper.Clamp(Velocity.X, -250, 250);
            Velocity.Z = MathHelper.Clamp(Velocity.Z, -250, 250);

            if (intersectDetails.IntersectWithGround)
            {
                Velocity.Y = 0;
            }

            if (intersectDetails.IntersectWithWalls)
            {
                UpdateWallCollisionVelocity(
                    intersectDetails.IntersectedWallTriangle, ref currentVelocity);
            }

            if (intersectDetails.IntersectWithFloorSides)
            {
                UpdateWallCollisionVelocity(
                    intersectDetails.IntersectedFloorSidesTriangle,
                    ref currentVelocity);
            }

            // If the velocity is low, simply cause the marble to halt
            if (-1 < Velocity.X && Velocity.X < 1)
            {
                Velocity.X = 0;
            }
            if (-1 < Velocity.Z && Velocity.Z < 1)
            {
                Velocity.Z = 0;
            }

            // Update the marble's position
            UpdateMovement((Velocity + currentVelocity) / 2, elapsed);
        }

        protected void UpdateWallCollisionVelocity(IEnumerable<Triangle> wallTriangles, ref Vector3 currentVelocity)
        {
            foreach (var triangle in wallTriangles)
            {
                Axis direction = CollideDirection(triangle);
                // Swap the velocity between x & z if the wall is diagonal
                if ((direction & Axis.X) == Axis.X && (direction & Axis.Z) == Axis.Z)
                {
                    float tmp = Velocity.X;
                    Velocity.X = Velocity.Z;
                    Velocity.Z = tmp;

                    tmp = currentVelocity.X;
                    currentVelocity.X = currentVelocity.Z * 0.3f;
                    currentVelocity.Z = tmp * 0.3f;
                }
                // Change the direction of the velocity in the x-axis
                else if ((direction & Axis.X) == Axis.X)
                {
                    if ((Position.X > triangle.A.X && Velocity.X < 0) ||
                        (Position.X < triangle.A.X && Velocity.X > 0))
                    {
                        Velocity.X = -Velocity.X * 0.3f;
                        currentVelocity.X = -currentVelocity.X * 0.3f;
                    }
                }
                // Change the direction of the velocity in the z-axis
                else if ((direction & Axis.Z) == Axis.Z)
                {
                    if ((Position.Z > triangle.A.Z && Velocity.Z < 0) ||
                        (Position.Z < triangle.A.Z && Velocity.Z > 0))
                    {
                        Velocity.Z = -Velocity.Z * 0.3f;
                        currentVelocity.Z = -currentVelocity.Z * 0.3f;
                    }
                }
            }
        }

        private void UpdateMovement(Vector3 deltaVelocity, float deltaTime)
        {
            // Calculate the change in the marble's position
            Vector3 deltaPosition = deltaVelocity * deltaTime;

            // Before setting the new position, we must make sure it is legal
            BoundingSphere nextPosition = this.BoundingSphereTransformed;
            nextPosition.Center += deltaPosition;
            IntersectDetails nextIntersectDetails = new IntersectDetails();
            Maze.GetCollisionDetails(nextPosition, ref nextIntersectDetails, true);
            nextPosition.Radius += 1.0f;

            // Move the marble
            Position += deltaPosition;

            // If the floor not straight then we must reposition the marble vertically
            Vector3 forwardVecX = Vector3.Transform(normal,
               Matrix.CreateRotationZ(-MathHelper.PiOver2));

            Vector3 forwardVecZ = Vector3.Transform(normal,
                Matrix.CreateRotationX(-MathHelper.PiOver2));

            bool isGroundStraight = true;
            if (forwardVecX.X != -1 && forwardVecX.X != 0)
            {
                Position.Y += deltaPosition.X / forwardVecX.X * forwardVecX.Y;
                isGroundStraight = false;
            }
            if (forwardVecZ.X != -1 && forwardVecZ.X != 0)
            {
                Position.Y += deltaPosition.Z / forwardVecZ.Z * forwardVecZ.Y;
                isGroundStraight = false;
            }
            // If the marble is already inside the floor, we must reposition it
            if (isGroundStraight && nextIntersectDetails.IntersectWithGround)
            {
                Position.Y = nextIntersectDetails.IntersectedGroundTriangle.A.Y +
                    BoundingSphereTransformed.Radius;
            }
            // Finally, we "roll" the marble in accordance to its movement
            if (BoundingSphereTransformed.Radius != 0)
            {
                Rotation.Z = deltaPosition.Z / BoundingSphereTransformed.Radius;
                Rotation.X = deltaPosition.X / BoundingSphereTransformed.Radius;
            }
        }

    }
}
