using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using GameStateManagement;
using System;

namespace MarbleMazeGame
{
    class BackgroundScreen : GameScreen
    {
        Texture2D background;

        public BackgroundScreen()
        {
            TransitionOnTime = TimeSpan.FromSeconds(0.0);
            TransitionOffTime = TimeSpan.FromSeconds(0.5);
        }

        public override void LoadContent()
        {
            background = Load<Texture2D>(@"Images\titleScreen");
        }

        public override void Draw(GameTime gameTime)
        {
            SpriteBatch spriteBatch = ScreenManager.SpriteBatch;

            spriteBatch.Begin();

            spriteBatch.Draw(background, new Vector2(0, 0),
                Color.White * TransitionAlpha);

            spriteBatch.End();
        } 
    }
}
