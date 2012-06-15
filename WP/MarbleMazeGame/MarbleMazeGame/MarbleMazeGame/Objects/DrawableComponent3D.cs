using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Collections;
using System.Collections.Generic;

namespace MarbleMazeGame
{
    [Flags]
    public enum Axis
    {
        X = 0x1,
        Y = 0x2,
        Z = 0x4
    }

    public abstract class DrawableComponent3D : DrawableGameComponent
    {
        public const float gravity = 100 * 9.81f;
        public const float wallFriction = 100 * 0.8f;

        string modelName;
        protected bool preferPerPixelLighting = false;
        public Model Model = null;
        protected IntersectDetails intersectDetails = new IntersectDetails();
        protected float staticGroundFriction = 0.1f;

        public Vector3 Position = Vector3.Zero;
        public Vector3 Rotation = Vector3.Zero;
        public Vector3 Velocity = Vector3.Zero;
        public Vector3 Acceleration = Vector3.Zero;

        public Matrix[] AbsoluteBoneTransforms;
        public Matrix FinalWorldTransforms;
        public Matrix OriginalWorldTransforms = Matrix.Identity;
        public Camera Camera;

        public DrawableComponent3D(Game game, string modelName)
            : base(game)
        {
            this.modelName = modelName;
        }

        protected override void LoadContent()
        {
            // Load the model
            Model = Game.Content.Load<Model>(@"Models\" + modelName);

            // Copy the absolute transforms
            AbsoluteBoneTransforms = new Matrix[Model.Bones.Count];
            Model.CopyAbsoluteBoneTransformsTo(AbsoluteBoneTransforms);

            base.LoadContent();
        }

        public override void Draw(GameTime gameTime)
        {
            foreach (ModelMesh mesh in Model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    // Set the effect for drawing the component
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = preferPerPixelLighting;

                    // Apply camera settings
                    effect.Projection = Camera.Projection;
                    effect.View = Camera.View;

                    // Apply necessary transformations
                    effect.World = FinalWorldTransforms;
                }

                // Draw the mesh by the effect that set
                mesh.Draw();
            }

            base.Draw(gameTime);
        }

        protected virtual void UpdateFinalWorldTransform()
        {
            FinalWorldTransforms = Matrix.Identity *
                Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) *
                    OriginalWorldTransforms *
                    Matrix.CreateTranslation(Position);
        }

        public override void Update(GameTime gameTime)
        {
            // Perform physics calculations
            CalcPhysics(gameTime);

            // Update the final transformation to properly place the component in the
            // game world.
            UpdateFinalWorldTransform();

            base.Update(gameTime);
        }

        protected virtual void CalcPhysics(GameTime gameTime)
        {
            CalculateCollisions();
            CalculateAcceleration();
            CalculateFriction();
            CalculateVelocityAndPosition(gameTime);
        }

        protected abstract void CalculateFriction();

        protected abstract void CalculateAcceleration();

        protected abstract void CalculateVelocityAndPosition(GameTime gameTime);

        protected abstract void CalculateCollisions();
    }
}

