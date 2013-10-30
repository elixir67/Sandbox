using BabyKit.DataModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using WinRTXamlToolkit.Controls.DataVisualization.Charting;

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234237

namespace BabyKit.UI
{
    /// <summary>
    /// A basic page that provides characteristics common to most applications.
    /// </summary>
    public sealed partial class WeightPage : BabyKit.Common.LayoutAwarePage
    {
        private BabyInfo _baby;
        private ObservableCollection<Record> _weights;

        public WeightPage()
        {
            this.InitializeComponent();
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
        protected override async void LoadState(Object navigationParameter, Dictionary<String, Object> pageState)
        {
            _baby = await BabyManager.Load();
            _weights = await WeightManager.Load();

            if (string.IsNullOrEmpty(_baby.Name))
            {
                this.pageTitle.Text = "请输入宝宝信息";
                return;
            }
            else
            {
                string title = string.Format("{0}的体重是:", _baby.NickName);
                this.pageTitle.Text = title;
            }

            if (0 == _weights.Count)
            {
                _weights = MockWeights();
            }

            if (_weights.Count > 0)
            {
                listWeight.ItemsSource = _weights;
                UpdateCharts();
            }
        }

        /// <summary>
        /// Preserves state associated with this page in case the application is suspended or the
        /// page is discarded from the navigation cache.  Values must conform to the serialization
        /// requirements of <see cref="SuspensionManager.SessionState"/>.
        /// </summary>
        /// <param name="pageState">An empty dictionary to be populated with serializable state.</param>
        protected override void SaveState(Dictionary<String, Object> pageState)
        {
            WeightManager.Save();
        }

        private void UpdateCharts()
        {
            ((LineSeries)LineChartWithAxes.Series[0]).ItemsSource = _weights;
            //((LineSeries)LineChartWithAxes.Series[0]).DependentRangeAxis =
            //    new LinearAxis
            //    {
            //        Minimum = 0,
            //        Maximum = 100,
            //        Orientation = AxisOrientation.Y,
            //        Interval = 1,
            //        ShowGridLines = true
            //    };
        }

        private static ObservableCollection<Record> MockWeights()
        {
            ObservableCollection<Record> items = new ObservableCollection<Record>();
            items.Add(new Record { Date = DateTime.Parse("2013-06-30"), Value = 3.5 });
            items.Add(new Record { Date = DateTime.Parse("2013-08-01"), Value = 4.0 });//?TODO
            items.Add(new Record { Date = DateTime.Parse("2013-09-01"), Value = 5.5 });//?TODO
            items.Add(new Record { Date = DateTime.Parse("2013-10-14"), Value = 8.0 });
            items.Add(new Record { Date = DateTime.Parse("2013-10-28"), Value = 8.7 });
            return items;
        }

        public class NameValueItem
        {
            public string Name { get; set; }
            public double Value { get; set; }
        }

        private void Button_Click_SaveWeightRecord(object sender, RoutedEventArgs e)
        {
            DateTime? dt = calendar.SelectedDate;
            if (dt.HasValue)
            {
                double value = numWeight.Value;
                _weights.Add(new Record { Date = dt.Value, Value = value });
            }
        }

        private void Button_Click_RemoveWeightRecord(object sender, RoutedEventArgs e)
        {
            Record record = this.listWeight.SelectedItem as Record;
            _weights.Remove(record);
        }
    }

    // TODO Record Converter
}
