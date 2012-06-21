using System;
using System.Linq;
using Microsoft.Xna.Framework;
using GameStateManagement;

namespace MarbleMazeGame
{
    class PauseScreen : MenuScreen
    {
        public PauseScreen()
            : base("Game Paused")
        {
            // Create our menu entries.
            MenuEntry returnGameMenuEntry = new MenuEntry("Return");
            MenuEntry restartGameMenuEntry = new MenuEntry("Restart");
            MenuEntry exitMenuEntry = new MenuEntry("Quit Game");

            // Hook up menu event handlers.
            returnGameMenuEntry.Selected += ReturnGameMenuEntrySelected;
            restartGameMenuEntry.Selected += RestartGameMenuEntrySelected;
            exitMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(returnGameMenuEntry);
            MenuEntries.Add(restartGameMenuEntry);
            MenuEntries.Add(exitMenuEntry);
        }

        void ReturnGameMenuEntrySelected(object sender, EventArgs e)
        {
            AudioManager.PauseResumeSounds(true);

            var res = from screen in ScreenManager.GetScreens()
                      where screen.GetType() != typeof(GameplayScreen)
                      select screen;

            foreach (GameScreen screen in res)
                screen.ExitScreen();

            (ScreenManager.GetScreens()[0] as GameplayScreen).IsActive =
                true;
        }

        void RestartGameMenuEntrySelected(object sender, EventArgs e)
        {
            AudioManager.PauseResumeSounds(true);

            var res = from screen in ScreenManager.GetScreens()
                      where screen.GetType() != typeof(GameplayScreen)
                      select screen;

            foreach (GameScreen screen in res)
                screen.ExitScreen();

            (ScreenManager.GetScreens()[0] as GameplayScreen).IsActive = true;

            (ScreenManager.GetScreens()[0] as GameplayScreen).Restart();
        }

        protected override void OnCancel(PlayerIndex playerIndex)
        {
            foreach (GameScreen screen in ScreenManager.GetScreens())
                screen.ExitScreen();

            ScreenManager.AddScreen(new BackgroundScreen(), null);
            ScreenManager.AddScreen(new MainMenuScreen(), null);
        }

    }
}