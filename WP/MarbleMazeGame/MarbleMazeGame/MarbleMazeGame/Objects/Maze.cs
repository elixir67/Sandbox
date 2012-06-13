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

    }
}
