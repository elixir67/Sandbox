using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GameStateManagement;
using Microsoft.Xna.Framework;

namespace MarbleMazeGame
{
    class MainMenuScreen : MenuScreen
    {
        public MainMenuScreen()
            : base("")
        {
            IsPopup = true;

            // Create our menu entries.
            MenuEntry startGameMenuEntry = new MenuEntry("Play");
            MenuEntry highScoreMenuEntry = new MenuEntry("High Score");
            MenuEntry exitMenuEntry = new MenuEntry("Exit");

            // Hook up menu event handlers.
            startGameMenuEntry.Selected += StartGameMenuEntrySelected;
            highScoreMenuEntry.Selected += HighScoreMenuEntrySelected;
            exitMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(startGameMenuEntry);
            MenuEntries.Add(highScoreMenuEntry);
            MenuEntries.Add(exitMenuEntry);
        }

        void HighScoreMenuEntrySelected(object sender, EventArgs e)
        {
            foreach (GameScreen screen in ScreenManager.GetScreens())
                screen.ExitScreen();

            ScreenManager.AddScreen(new BackgroundScreen(), null);
            ScreenManager.AddScreen(new HighScoreScreen(), null);
        }

        void StartGameMenuEntrySelected(object sender, EventArgs e)
        {
            foreach (GameScreen screen in ScreenManager.GetScreens())
                screen.ExitScreen();

            ScreenManager.AddScreen(new LoadingAndInstructionScreen(), null);
        }

        protected override void OnCancel(PlayerIndex playerIndex)
        {
            HighScoreScreen.SaveHighscore();

            ScreenManager.Game.Exit();
        }

    }
}
