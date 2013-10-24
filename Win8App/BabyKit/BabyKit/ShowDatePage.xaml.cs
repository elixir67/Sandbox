using BabyKit.DataModel;
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
        private DispatcherTimer _timer;
        private BabyInfo _baby;
        public ShowDate()
        {
            this.InitializeComponent();
            //Init();
        }

        private async void Init()
        {
            //DateTime birth = MockBirth();
            //await BabyManager.Load();
            //_baby = BabyManager.BabyInstance();
            _baby = await BabyManager.Load();

            if (string.IsNullOrEmpty(_baby.Name))
            {
                this.pageName.Text = "请输入宝宝信息";
                return;
            }

            string title = string.Format("{0}诞生了：",_baby.NickName);
            this.pageName.Text = title;
            DateTime birth = _baby.Birthday;
    
            TimeSpan span = DateTime.Now - birth;

            int days = span.Days;
            string daysToShow = string.Format("总共{0}天", days);
            this.tbDays.Text = daysToShow;

            int hours = days * 24 + span.Hours;
            string hoursToShow = string.Format("总共{0}小时", hours);
            this.tbHours.Text = hoursToShow;

            int minutes = hours * 60 + span.Hours;
            //double totalMinutes = span.TotalMinutes;
            string minutesToShow = string.Format("总共{0}分钟", minutes);
            this.tbMinutes.Text = minutesToShow;

            ShowSeconds(span);

            _timer = new DispatcherTimer();
            _timer.Tick += timer_Tick;
            _timer.Interval = new TimeSpan(0, 0, 3);

            if(!_timer.IsEnabled)
                _timer.Start();
        }

        private void ShowSeconds(TimeSpan span)
        {
            int seconds = span.Seconds; //it's not the total second
            string secondsToShow = string.Format("还有{0}秒", seconds);
            this.tbSeconds.Text = secondsToShow;
        }

        private DateTime MockBirth()
        {
            DateTime birth;
            //string strBirth = "2013-06-30T17:35:0+08:00";
            string strBirth = "2013-06-30 17:35";
            if (!DateTime.TryParse(strBirth, out birth))
            {
                Debug.Assert(false);
            }
            return birth;
        }

        void timer_Tick(object sender, object e)
        {
            // DateTime birth = MockBirth();
            DateTime birth = _baby.Birthday;
            
            TimeSpan span = DateTime.Now - birth;
            ShowSeconds(span);
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
            Init();
            if (null != _timer && !_timer.IsEnabled)
                _timer.Start();
        }

        /// <summary>
        /// Preserves state associated with this page in case the application is suspended or the
        /// page is discarded from the navigation cache.  Values must conform to the serialization
        /// requirements of <see cref="SuspensionManager.SessionState"/>.
        /// </summary>
        /// <param name="pageState">An empty dictionary to be populated with serializable state.</param>
        protected override void SaveState(Dictionary<String, Object> pageState)
        {
            if (null != _timer && _timer.IsEnabled)
                _timer.Stop();
        }
    }
}
