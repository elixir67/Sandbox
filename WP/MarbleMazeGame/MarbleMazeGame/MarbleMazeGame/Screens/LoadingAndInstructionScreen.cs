using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using GameStateManagement;
using Microsoft.Xna.Framework.Input.Touch;
using System.Threading;

namespace MarbleMazeGame
{
    class LoadingAndInstructionScreen : GameScreen
    {
        Texture2D background;
        SpriteFont font;
        bool isLoading;
        GameplayScreen gameplayScreen;
        Thread thread;

        public LoadingAndInstructionScreen()
        {
            EnabledGestures = GestureType.Tap;

            TransitionOnTime = TimeSpan.FromSeconds(0);
            TransitionOffTime = TimeSpan.FromSeconds(0.5);
        }

        public override void LoadContent()
        {
            background = Load<Texture2D>(@"Textures\instructions");
            font = Load<SpriteFont>(@"Fonts\MenuFont");

            // Create a new instance of the gameplay screen
            gameplayScreen = new GameplayScreen();
            gameplayScreen.ScreenManager = ScreenManager;
        }

        public override void HandleInput(InputState input)
        {
            if (!isLoading)
            {
                if (input.Gestures.Count > 0)
                {
                    if (input.Gestures[0].GestureType == GestureType.Tap)
                    {
                        // Start loading the resources in additional thread
                        thread = new Thread(
                            new ThreadStart(gameplayScreen.LoadAssets));

                        isLoading = true;
                        thread.Start();
                    }
                }
            }
            base.HandleInput(input);
        }

        public override void Update(GameTime gameTime,
            bool otherScreenHasFocus, bool coveredByOtherScreen)
        {
            // If additional thread is running, skip
            if (null != thread)
            {
                // If additional thread finished loading and the screen is
                // not exiting
                if (thread.ThreadState ==
                    ThreadState.Stopped && !IsExiting)
                {
                    // Exit the screen and show the gameplay screen 
                    // with pre-loaded assets
                    foreach (GameScreen screen in
                        ScreenManager.GetScreens())
                        screen.ExitScreen();

                    ScreenManager.AddScreen(gameplayScreen, null);
                }
            }

            base.Update(gameTime, otherScreenHasFocus,
                coveredByOtherScreen);
        }

        public override void Draw(GameTime gameTime)
        {
            SpriteBatch spriteBatch = ScreenManager.SpriteBatch;

            spriteBatch.Begin();

            // Draw Background
            spriteBatch.Draw(background, new Vector2(0, 0),
                    new Color(255, 255, 255, TransitionAlpha));

            // If loading gameplay screen resource in the 
            // background show "Loading..." text
            if (isLoading)
            {
                string text = "Loading...";
                Vector2 size = font.MeasureString(text);
                Vector2 position = new Vector2(
                    (ScreenManager.GraphicsDevice.Viewport.Width -
                        size.X) / 2,
                    (ScreenManager.GraphicsDevice.Viewport.Height -
                        size.Y) / 2);
                spriteBatch.DrawString(font, text, position, Color.White);
            }

            spriteBatch.End();
        }

    }
}
