#region Using Statements
using System;
using System.Collections.Generic;
using System.Linq;
using GameStateManagement;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Media;
#endregion


namespace CatapultGame
{
    class MusicSelectionScreen : MenuScreen
    {
        #region Fields
        IList<MediaSource> mediaSourcesList;
        MediaLibrary mediaLibrary;
        GameScreen backgroundScreen;
        #endregion

        #region Initialization
        public MusicSelectionScreen(GameScreen backgroundScreen)
            : base("Main")
        {
            IsPopup = true;

            this.backgroundScreen = backgroundScreen;

            // Get the default media source
            mediaSourcesList = MediaSource.GetAvailableMediaSources();

            // Use only first one
            mediaLibrary = new MediaLibrary(mediaSourcesList[0]);

            // Create maximum 5 entries with music from music collection
            for (int i = 0; i < mediaLibrary.Songs.Count; i++)
            {
                if (i == 5)
                    break;

                Song song = mediaLibrary.Songs[i];

                // Create menu entry for the song.
                MenuEntry songMenuEntry = new MenuEntry(song.Name);
                // Hook up menu event handler
                songMenuEntry.Selected += OnSongSelected;
                // Add song to the menu
                MenuEntries.Add(songMenuEntry);
            }

            // Create our menu entries.
            MenuEntry cancelMenuEntry = new MenuEntry("Cancel");

            // Hook up menu event handlers.
            cancelMenuEntry.Selected += OnCancel;

            // Add entries to the menu.
            MenuEntries.Add(cancelMenuEntry);
        }
        #endregion

        #region Event Handlers for Menu Items
/// <summary>
/// Handles Song selection and exits the menu
/// </summary>
private void OnSongSelected(object sender, EventArgs e)
{
    var selection = from song in mediaLibrary.Songs
                    where song.Name == (sender as MenuEntry).Text
                    select song;

    Song selectedSong = selection.FirstOrDefault();

    if (null != selectedSong)
        MediaPlayer.Play(selectedSong);

    backgroundScreen.ExitScreen();
    ExitScreen();
}

/// <summary>
/// Handles "Exit" menu item selection
/// </summary>
protected override void OnCancel(Microsoft.Xna.Framework.PlayerIndex playerIndex)
{
    backgroundScreen.ExitScreen();
    ExitScreen();
}
#endregion

    }
}
