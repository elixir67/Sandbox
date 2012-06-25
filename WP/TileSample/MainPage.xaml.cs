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

namespace TileSample
{
    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();
        }

        // Navigate to the page for modifying Application Tile properties.
        private void buttonChangeApplicationTile_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("/ApplicationTile.xaml", UriKind.Relative));
        }


        // Navigate to the page for modifying secondary Tile properties. 
        // Pass a parameter that lets the SecondaryTile page know that it was navigated to from MainPage.
        // (DefaultTitle will equal 'FromTile' when the user navigates to the SecondaryTile page from a Tile.
        private void buttonChangeSecondaryTile_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("/SecondaryTile.xaml?DefaultTitle=FromMain", UriKind.Relative));
        }
    }
}