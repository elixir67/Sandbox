using System;
using Microsoft.Xna.Framework;
using GameStateManagement;

namespace MarbleMazeGame
{
    /// This is the main type for your game
   public class MarbleMazeGame : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        ScreenManager screenManager;

        public MarbleMazeGame()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
 
            // Frame rate is 30 fps by default for Windows Phone.
            TargetElapsedTime = TimeSpan.FromTicks(333333);
            //Create a new instance of the Screen Manager
            screenManager = new ScreenManager(this);
            Components.Add(screenManager);
 
            // Switch to full screen for best game experience
            graphics.IsFullScreen = true;
 
            graphics.SupportedOrientations = DisplayOrientation.LandscapeLeft;

            // Add two new screens
            screenManager.AddScreen(new BackgroundScreen(), null);
            screenManager.AddScreen(new MainMenuScreen(), null);

            // Initialize sound system
            AudioManager.Initialize(this);
        }

        protected override void LoadContent()
        {
            AudioManager.LoadSounds();
            HighScoreScreen.LoadHighscore();
            base.LoadContent();
        }

    }
}


