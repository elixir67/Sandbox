using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Items Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234233

namespace Riddle
{
    /// <summary>
    /// A page that displays a collection of item previews.  In the Split Application this page
    /// is used to display and select one of the available groups.
    /// </summary>
    public sealed partial class RiddlesPage : Riddle.Common.LayoutAwarePage
    {
        public RiddlesPage()
        {
            this.InitializeComponent();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void RaisePropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        /// <summary>
        /// Populates the page with content passed during navigation.  Any saved state is also
        /// provided when recreating a page from a prior session.
        /// </summary>
        /// <param name="navigationParameter">The parameter value passed to
        /// <see cref="Frame.Navigate(Type, Object)"/> when this page was initially requested.
        /// </param>
        /// <param name="pageState">A dictionary of state preserved by this page during an earlier
        /// session.  This will be null the first time a page is visited.</param>
        protected async override void LoadState(Object navigationParameter, Dictionary<String, Object> pageState)
        {
            ObservableCollection<RiddleItem> riddleObservable = new ObservableCollection<RiddleItem>();
            //CsvExport<RiddleItem> exporter = new CsvExport<RiddleItem>(riddleObservable);
            //exporter.ExportToFile("test.csv");
            busyIndicator.IsActive = true;
            busyIndicator.Visibility = Visibility.Visible;

            XDocument doc = await RiddleManager.GetRiddleRssContents();
            //XDocument doc = await RiddleManager.LoadTestRssXml();
            if (doc != null)
            {
                List<RiddleItem> riddles = await RiddleManager.ParseRiddles(doc);
                Debug.Assert(riddles.Count > 0);
                DefaultViewModel["Items"] = riddles;

                bool success = await RiddleManager.FetchAnswers(riddles);

                foreach (var riddle in riddles)
                    riddleObservable.Add(riddle);
                // Show the riddles without answers at first to give better user experience
                DefaultViewModel["Items"] = riddleObservable;

                //RaisePropertyChanged("DefaultViewModel");
            }

            busyIndicator.IsActive = false;
            busyIndicator.Visibility = Visibility.Collapsed;

            CsvExport<RiddleItem> exporter = new CsvExport<RiddleItem>(riddleObservable);
            string outputFile = GetOutputFileName();
            exporter.ExportToFile(outputFile);
        }

        private static string GetOutputFileName()
        {
            CultureInfo enUS = new CultureInfo("en-US");
            DateTimeFormatInfo dtfi = enUS.DateTimeFormat;
            dtfi.ShortDatePattern = "yyyy-MM-dd";
            DateTime date = DateTime.Today;
            string strDate = date.ToString("d", enUS);

            string outputFile = "Riddles_" + strDate + ".csv";
            return outputFile;
        }

        private async void itemGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            // Click the RiddleItem will open web browser to show the web content

            // Get the link first
            RiddleItem riddle = e.ClickedItem as RiddleItem;

            if (riddle == null)
                return;

            // The URI to launch
            string uriToLaunch = riddle.Link;

            // Create a Uri object from a URI string 
            var uri = new Uri(uriToLaunch);

            // Launch the URI
            await Windows.System.Launcher.LaunchUriAsync(uri);
        }
    }

}
