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
    public partial class ApplicationTile : PhoneApplicationPage
    {
        public ApplicationTile()
        {
            InitializeComponent();
        }

        // Set all the properties of the Application Tile.
        private void buttonSetApplicationTile_Click(object sender, RoutedEventArgs e)
        {
            int newCount = 0;

            // Application Tile is always the first Tile, even if it is not pinned to Start.
            ShellTile TileToFind = ShellTile.ActiveTiles.First();

            // Application should always be found
            if (TileToFind != null)
            {
                // if Count was not entered, then assume a value of 0
                if (textBoxCount.Text == "")
                {
                    // A value of '0' means do not display the Count.
                    newCount = 0;
                }
                // otherwise, get the numerical value for Count
                else
                {
                    newCount = int.Parse(textBoxCount.Text);
                }

                // Set the properties to update for the Application Tile.
                // Empty strings for the text values and URIs will result in the property being cleared.
                StandardTileData NewTileData = new StandardTileData
                {
                    Title = textBoxTitle.Text,
                    BackgroundImage = new Uri(textBoxBackgroundImage.Text, UriKind.Relative),
                    Count = newCount,
                    BackTitle = textBoxBackTitle.Text,
                    BackBackgroundImage = new Uri(textBoxBackBackgroundImage.Text, UriKind.Relative),
                    BackContent = textBoxBackContent.Text
                };

                // Update the Application Tile
                TileToFind.Update(NewTileData);
            }
        }

    }
}