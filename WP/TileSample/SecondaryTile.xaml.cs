using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace TileSample
{
    public partial class SecondaryTile : PhoneApplicationPage
    {
        public SecondaryTile()
        {
            InitializeComponent();
        }

        // Event handler for when this page is navigated to. Looks to see
        // whether the Tile exists and set the check box appropriately.
        // Also fills in the default value for the Title, based on the
        // value passed in in the QueryString - either FromMain or FromTile.        
        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            // See whether the Tile is pinned, and if so, make sure the check box for it is checked.
            // (User may have deleted it manually.)
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            checkBoxDisplaySecondaryTile.IsChecked = (TileToFind != null);

            // To demonstrate the use of the Navigation URI and query parameters, we set the default value
            // of the Title text box based on where we navigated from. If we navigated to this page
            // from the MainPage, the DefaultTitle parameter will be "FromMain". If we navigated here
            // when the secondary Tile was tapped, the parameter will be "FromTile".
            textBoxTitle.Text = this.NavigationContext.QueryString["DefaultTitle"];

        }

        // Event handler for when the check box is checked. Create a secondary Tile if it doesn't
        // already exist.
        private void checkBoxDisplaySecondaryTile_Checked(object sender, RoutedEventArgs e)
        {
            // Look to see whether the Tile already exists and if so, don't try to create it again.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // Create the Tile if we didn't find that it already exists.
            if (TileToFind == null)
            {
                // Create the Tile object and set some initial properties for the Tile.
                // The Count value of 12 shows the number 12 on the front of the Tile. Valid values are 1-99.
                // A Count value of 0 indicates that the Count should not be displayed.
                StandardTileData NewTileData = new StandardTileData
                {
                    BackgroundImage = new Uri("Red.jpg", UriKind.Relative),
                    Title = "Secondary Tile",
                    Count = 12,
                    BackTitle = "Back of Tile",
                    BackContent = "Welcome to the back of the Tile",
                    BackBackgroundImage = new Uri("Blue.jpg", UriKind.Relative)
                };

                // Create the Tile and pin it to Start. This will cause a navigation to Start and a deactivation of our application.
                ShellTile.Create(new Uri("/SecondaryTile.xaml?DefaultTitle=FromTile", UriKind.Relative), NewTileData);
            }

        }

        // Event handler for when the check box is unchecked.  Delete the secondary Tile
        // if it exists.
        private void checkBoxDisplaySecondaryTile_Unchecked(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to delete.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then delete it.
            if (TileToFind != null)
            {
                TileToFind.Delete();
            }

        }

        // Handle the Title button clicked event by setting the front of Tile title.
        private void buttonSetTitle_Click(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the Title.
            if (TileToFind != null)
            {
                StandardTileData NewTileData = new StandardTileData
                {
                    Title = textBoxTitle.Text
                };

                TileToFind.Update(NewTileData);
            }

        }


        // Handle the Background Image button clicked event by setting the front of Tile background image.
        private void buttonSetBackgroundImage_Click(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the background image.
            if (TileToFind != null)
            {
                StandardTileData NewTileData = new StandardTileData
                {
                    BackgroundImage = new Uri(textBoxBackgroundImage.Text, UriKind.Relative)
                };

                TileToFind.Update(NewTileData);
            }

        }

        // Handle the Count button clicked event by setting the front of Tile count value.
        private void buttonSetCount_Click(object sender, RoutedEventArgs e)
        {
            int newCount = 0;

            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the count.
            if (TileToFind != null)
            {
                // if Count was not entered, then assume a value of 0.
                if (textBoxCount.Text == "")
                {
                    newCount = 0;
                }
                // Otherwise, get the numerical value for Count.
                else
                {
                    newCount = int.Parse(textBoxCount.Text);
                }

                StandardTileData NewTileData = new StandardTileData
                {
                    Count = newCount
                };

                TileToFind.Update(NewTileData);
            }

        }


        // Handle the Back Title button clicked event by setting the back of Tile title.
        private void buttonSetBackTitle_Click(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the title on the back of the Tile.
            if (TileToFind != null)
            {
                StandardTileData NewTileData = new StandardTileData
                {
                    BackTitle = textBoxBackTitle.Text
                };

                TileToFind.Update(NewTileData);
            }

        }


        // Handle the Back Background Image button clicked event by setting the back of Tile background image.
        private void buttonSetBackBackgroundImage_Click(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the background image on the back of the Tile.
            if (TileToFind != null)
            {
                StandardTileData NewTileData = new StandardTileData
                {
                    BackBackgroundImage = new Uri(textBoxBackBackgroundImage.Text, UriKind.Relative)
                };

                TileToFind.Update(NewTileData);
            }

        }

        // Handle the Back Content button clicked event by setting the back of Tile content.
        private void buttonSetBackContent_Click(object sender, RoutedEventArgs e)
        {
            // Find the Tile we want to update.
            ShellTile TileToFind = ShellTile.ActiveTiles.FirstOrDefault(x => x.NavigationUri.ToString().Contains("DefaultTitle=FromTile"));

            // If the Tile was found, then update the content on the back of the Tile.
            if (TileToFind != null)
            {
                StandardTileData NewTileData = new StandardTileData
                {
                    BackContent = textBoxBackContent.Text
                };

                TileToFind.Update(NewTileData);
            }

        }


    }
}