using System;
using System.Collections.Generic;
using System.Diagnostics;
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

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234237

namespace BabyKit
{
    /// <summary>
    /// A basic page that provides characteristics common to most applications.
    /// </summary>
    public sealed partial class ShowDate : BabyKit.Common.LayoutAwarePage
    {
        public ShowDate()
        {
            this.InitializeComponent();
            DateTime birth;
            //string strBirth = "2013-06-30T17:35:0+08:00";
            string strBirth = "2013-06-30 17:35";
            if (!DateTime.TryParse(strBirth, out birth))
            {
                Debug.Assert(false);
                return;
            }
            TimeSpan span = DateTime.Now - birth;

            int days = span.Days;
            string daysToShow = string.Format("{0}天", days);
            this.tbDays.Text = daysToShow;

            int hours = days*24 + span.Hours;
            string hoursToShow = string.Format("{0}小时", hours);
            this.tbHours.Text = hoursToShow;

            int minutes = hours*60 + span.Hours;
            double totalMinutes = span.TotalMinutes;
            string minutesToShow = string.Format("{0}分钟", totalMinutes.ToString("0.00"));
            this.tbMinutes.Text = minutesToShow;

            DispatcherTimer timer = new DispatcherTimer();
            timer.Tick += timer_Tick;
            timer.Interval = new TimeSpan(0, 0, 10);
            timer.Start();
        }

        void timer_Tick(object sender, object e)
        {
            DateTime birth;
            //string strBirth = "2013-06-30T17:35:0+08:00";
            string strBirth = "2013-06-30 17:35";
            if (!DateTime.TryParse(strBirth, out birth))
            {
                Debug.Assert(false);
                return;
            }

            TimeSpan span = DateTime.Now - birth;
            double totalMinutes = span.TotalMinutes;
            string minutesToShow = string.Format("{0}分钟", totalMinutes.ToString("0.00"));
            this.tbMinutes.Text = minutesToShow;
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
        protected override void LoadState(Object navigationParameter, Dictionary<String, Object> pageState)
        {
        }

        /// <summary>
        /// Preserves state associated with this page in case the application is suspended or the
        /// page is discarded from the navigation cache.  Values must conform to the serialization
        /// requirements of <see cref="SuspensionManager.SessionState"/>.
        /// </summary>
        /// <param name="pageState">An empty dictionary to be populated with serializable state.</param>
        protected override void SaveState(Dictionary<String, Object> pageState)
        {
        }
    }
}
