using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using GameStateManagement;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Media;

namespace CatapultGame
{
    class MainMenuScreen : MenuScreen
    {
        public MainMenuScreen()
            : base(String.Empty)
        {
            IsPopup = true;

            // Create our menu entries.
            MenuEntry startGameMenuEntry = new MenuEntry("Play");
            MenuEntry selectBackgroundMusic = new MenuEntry("Select Background Music");
            MenuEntry shareMenuEntry = new MenuEntry("Tell a Friend");
            MenuEntry exitMenuEntry = new MenuEntry("Exit");

            // Hook up menu event handlers.
            startGameMenuEntry.Selected += StartGameMenuEntrySelected;
            selectBackgroundMusic.Selected += SelectBackgroundMusicMenuEntrySelected;
            shareMenuEntry.Selected += ShareMenuEntrySelected;

            exitMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(startGameMenuEntry);
            MenuEntries.Add(selectBackgroundMusic);
            MenuEntries.Add(shareMenuEntry);
            MenuEntries.Add(exitMenuEntry);
        }


        // Handles "Play" menu item selection
        void StartGameMenuEntrySelected(object sender, EventArgs e)
        {
            ScreenManager.AddScreen(new InstructionsScreen(), null);
        }

        // Handles "Exit" menu item selection
        protected override void OnCancel(PlayerIndex playerIndex)
        {
            ScreenManager.Game.Exit();
        }

        protected override void UpdateMenuEntryLocations()
        {
            base.UpdateMenuEntryLocations();

            foreach (var entry in MenuEntries)
            {
                var position = entry.Position;

                position.Y += 60;

                entry.Position = position;
            }
        }

        /// Handles "Select Background Music" menu item selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void SelectBackgroundMusicMenuEntrySelected(object sender, EventArgs e)
        {
            var backgroundScreen = new BackgroundScreen();
            ScreenManager.AddScreen(backgroundScreen, null);
            ScreenManager.AddScreen(new MusicSelectionScreen(backgroundScreen), null);
        }

        /// <summary>
        /// Handler "Share" menu item selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void ShareMenuEntrySelected(object sender, EventArgs e)
        {
            //Execute a task defined in the game class
            ((CatapultGame)(ScreenManager.Game)).ExecuteTask();
        }
    }
}
