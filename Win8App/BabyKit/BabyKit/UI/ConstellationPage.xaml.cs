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
    public sealed partial class ConstellationPage : BabyKit.Common.LayoutAwarePage
    {
        private BabyInfo _baby;

        public ConstellationPage()
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
                string constellation = GetAtomFromBirthday(_baby.Birthday);
                string title = string.Format("{0}的星座是{1}",_baby.NickName, constellation);
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

        public string GetAtomFromBirthday(DateTime birthday)
	    {
	        float birthdayF = 0.00F;
	
	        if (birthday.Month == 1 && birthday.Day < 20)
	        {
	            birthdayF = float.Parse(string.Format("13.{0}", birthday.Day));
	        }
	        else
	        {
	            birthdayF = float.Parse(string.Format("{0}.{1}", birthday.Month, birthday.Day));
	        }
	        float[] atomBound ={ 1.20F, 2.20F, 3.21F, 4.21F, 5.21F, 6.22F, 7.23F, 8.23F, 9.23F, 10.23F, 11.21F, 12.22F, 13.20F };
	        string[] atoms = { "水瓶座", "双鱼座", "白羊座", "金牛座", "双子座", "巨蟹座", "狮子座", "处女座", "天秤座", "天蝎座", "射手座", "魔羯座" };
	
	        string ret = "靠！外星人啊。";
	        for (int i = 0; i < atomBound.Length - 1; i++)
	        {
	            if (atomBound[i] <= birthdayF && atomBound[i + 1] > birthdayF)
	            {
	                ret = atoms[i];
	                break;
	            }
	        }
	        return ret;
	    } 

    }
}
