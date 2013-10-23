using BabyKit.DataModel;
using BabyKit.Utility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
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
    public sealed partial class InputInfoPage : BabyKit.Common.LayoutAwarePage
    {
        private BabyInfo babyInfo;
        private readonly string BABYINFO_PATH = "BabyInfo.json";
        public InputInfoPage()
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
            var storageFolder = KnownFolders.DocumentsLibrary;
            try
            {
                var file = storageFolder.GetFileAsync(BABYINFO_PATH);

                babyInfo = await FileHelper.LoadData<BabyInfo>(BABYINFO_PATH);
                tbName.Text = babyInfo.Name;
                tbNickname.Text = babyInfo.NickName;
                tbBirthday.Text = babyInfo.Birthday.ToString();
            }
            catch (FileNotFoundException ex)
            {
                tbName.Text = "千万别忘记宝宝名字哟";
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

        private void Button_Click_Save(object sender, RoutedEventArgs e)
        {
            babyInfo.Name = tbName.Text;
            babyInfo.NickName = tbNickname.Text;
            DateTime dt;
            if (DateTime.TryParse(tbBirthday.Text, out dt))
                babyInfo.Birthday = dt;
            FileHelper.SaveData(BABYINFO_PATH, babyInfo);
        }

    }
}
