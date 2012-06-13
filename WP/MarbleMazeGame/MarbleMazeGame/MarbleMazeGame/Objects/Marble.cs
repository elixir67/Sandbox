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

    }
}
