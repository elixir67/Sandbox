using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace MarbleMazeGame
{
    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public class Maze : DrawableComponent3D
    {
        public List<Vector3> Ground = new List<Vector3>();
        public List<Vector3> Walls = new List<Vector3>();
        public List<Vector3> FloorSides = new List<Vector3>();
        public LinkedList<Vector3> Checkpoints = new LinkedList<Vector3>();
        public Vector3 StartPoistion;
        public Vector3 End;

        public Maze(Game game)
            : base(game, "maze1")
        {
            preferPerPixelLighting = false;
        }

        public override void Draw(GameTime gameTime)
        {
            var originalSamplerState = GraphicsDevice.SamplerStates[0];

            // Cause the maze's textures to linearly wrap            
            GraphicsDevice.SamplerStates[0] = SamplerState.LinearWrap;

            foreach (var mesh in Model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    // Set the effect for drawing the maze
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = preferPerPixelLighting;

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

        protected override void LoadContent()
        {
            base.LoadContent();

            // Load the start & end positions of the maze from the bone
            StartPoistion = Model.Bones["Start"].Transform.Translation;
            End = Model.Bones["Finish"].Transform.Translation;

            // Get the maze's triangles from its mesh
            Dictionary<string, List<Vector3>> tagData =
                (Dictionary<string, List<Vector3>>)Model.Tag;

            Ground = tagData["Floor"];
            FloorSides = tagData["floorSides"];

            Walls = tagData["walls"];

            // Add checkpoints to the maze
            Checkpoints.AddFirst(StartPoistion);
            foreach (var bone in Model.Bones)
            {
                if (bone.Name.Contains("spawn"))
                {
                    Checkpoints.AddLast(bone.Transform.Translation);
                }
            }
        }

        protected override void CalculateCollisions()
        {
            // Nothing to do - Maze doesn't collide with itself
        }

        protected override void CalculateVelocityAndPosition(GameTime gameTime)
        {
            // Nothing to do - Maze doesn't move
        }

        protected override void CalculateFriction()
        {
            // Nothing to do - Maze is not affected by friction
        }

        protected override void CalculateAcceleration()
        {
            // Nothing to do - Maze doesn't move
        }

        public void GetCollisionDetails(BoundingSphere boundingSphere, ref IntersectDetails intersectDetailes, bool light)
        {
            intersectDetailes.IntersectWithGround =
                TriangleSphereCollisionDetection.IsSphereCollideWithTringles(Ground,
                boundingSphere, out intersectDetailes.IntersectedGroundTriangle,
                true);
            intersectDetailes.IntersectWithWalls =
                TriangleSphereCollisionDetection.IsSphereCollideWithTringles(Walls,
                boundingSphere, out intersectDetailes.IntersectedWallTriangle, light);
            intersectDetailes.IntersectWithFloorSides =
                TriangleSphereCollisionDetection.IsSphereCollideWithTringles(
                FloorSides, boundingSphere, out intersectDetailes.IntersectedFloorSidesTriangle,
                true);
        }

    }
}
