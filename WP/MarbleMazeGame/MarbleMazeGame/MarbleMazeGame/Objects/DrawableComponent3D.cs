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
    public abstract class DrawableComponent3D : DrawableGameComponent
    {
        string modelName;
        protected bool preferPerPixelLighting = false;
        public Model Model = null;
        public Camera Camera;

        public Vector3 Position = Vector3.Zero;
        public Vector3 Rotation = Vector3.Zero;

        public Matrix[] AbsoluteBoneTransforms;
        public Matrix FinalWorldTransforms;
        public Matrix OriginalWorldTransforms = Matrix.Identity;

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

        public override void Update(GameTime gameTime)
        {
            // Update the final transformation to properly place the component in the
            // game world.
            UpdateFinalWorldTransform();

            base.Update(gameTime);
        }

        protected virtual void UpdateFinalWorldTransform()
        {
            FinalWorldTransforms = Matrix.Identity *
                Matrix.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z) *
                    OriginalWorldTransforms *
                    Matrix.CreateTranslation(Position);
        }

    }
}

