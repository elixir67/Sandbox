using BabyKit.DataModel;
using System;
using System.Collections.Generic;
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

namespace BabyKit.UI
{
    /// <summary>
    /// A basic page that provides characteristics common to most applications.
    /// </summary>
    public sealed partial class ZodiacPage : BabyKit.Common.LayoutAwarePage
    {
        private BabyInfo _baby;

        public ZodiacPage()
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

            if (string.IsNullOrEmpty(_baby.Name))
            {
                this.pageTitle.Text = "请输入宝宝信息";
                return;
            }
            else
            {
                string zodiac = getShengXiao(_baby.Birthday);
                string title = string.Format("{0}的生肖是{1}", _baby.NickName, zodiac);
                this.pageTitle.Text = title;
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
        }

        public string getShengXiao(DateTime birthday)
        {
            // winrt doesn't support ChineseLunisolarCalendar?
            //System.Globalization.ChineseLunisolarCalendar chinseCaleander = new System.Globalization.ChineseLunisolarCalendar();
            //string TreeYear = "鼠牛虎兔龙蛇马羊猴鸡狗猪";

            //int intYear = chinseCaleander.GetSexagenaryYear(birthday.Year);

            //string Tree = TreeYear.Substring(chinseCaleander.GetTerrestrialBranch(intYear) - 1, 1);

            //return Tree;
            return "蛇";
        } 

    }
}
