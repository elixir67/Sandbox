using BabyKit.Data;
using BabyKit.UI;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.ApplicationModel.Background;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Graphics.Display;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Items Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234233

namespace BabyKit
{
    /// <summary>
    /// A page that displays a collection of item previews.  In the Split Application this page
    /// is used to display and select one of the available groups.
    /// </summary>
    public sealed partial class ItemsPage : BabyKit.Common.LayoutAwarePage
    {
        public ItemsPage()
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
        protected override void LoadState(Object navigationParameter, Dictionary<String, Object> pageState)
        {
            // TODO: Create an appropriate data model for your problem domain to replace the sample data
            var sampleDataGroups = SampleDataSource.GetGroups((String)navigationParameter);
            this.DefaultViewModel["Items"] = sampleDataGroups;
        }

        private const string TASK_NAME = "TileUpdater"; 
        private const string TASK_ENTRY = "BackgroundTasks.TileUpdater"; 

        ///// <summary> 
        ///// Invoked when this page is about to be displayed in a Frame. 
        ///// </summary> 
        ///// <param name="e">Event data that describes how this page was reached.  The Parameter 
        ///// property is typically used to configure the page.</param> 
        //protected async override void OnNavigatedTo(NavigationEventArgs e)
        //{
        //    var result = await BackgroundExecutionManager.RequestAccessAsync();
        //    if (result == BackgroundAccessStatus.AllowedMayUseActiveRealTimeConnectivity ||
        //        result == BackgroundAccessStatus.AllowedWithAlwaysOnRealTimeConnectivity)
        //    {
        //        foreach (var task in BackgroundTaskRegistration.AllTasks)
        //        {
        //            if (task.Value.Name == TASK_NAME)
        //                task.Value.Unregister(true);
        //        }

        //        BackgroundTaskBuilder builder = new BackgroundTaskBuilder();
        //        builder.Name = TASK_NAME;
        //        builder.TaskEntryPoint = TASK_ENTRY;
        //        builder.SetTrigger(new TimeTrigger(15, false));
        //        var registration = builder.Register();
        //    }
        //}

        /// <summary>
        /// Invoked when an item is clicked.
        /// </summary>
        /// <param name="sender">The GridView (or ListView when the application is snapped)
        /// displaying the item clicked.</param>
        /// <param name="e">Event data that describes the item clicked.</param>
        void ItemView_ItemClick(object sender, ItemClickEventArgs e)
        {
            // Navigate to the appropriate destination page, configuring the new page
            // by passing required information as a navigation parameter
            var groupId = ((SampleDataGroup)e.ClickedItem).UniqueId;

            switch(groupId)
            {
                case SampleDataSource.GROUP_DATE:
                    this.Frame.Navigate(typeof(ShowDatePage), groupId);
                    break;
                case SampleDataSource.GROUP_SETTING:
                    this.Frame.Navigate(typeof(InputInfoPage), groupId);
                    break;
                case SampleDataSource.GROUP_CONSTELLATION:
                    this.Frame.Navigate(typeof(ConstellationPage), groupId);
                    break;
                case SampleDataSource.GROUP_ZODIAC:
                    this.Frame.Navigate(typeof(ZodiacPage), groupId);
                    break;
                case SampleDataSource.GROUP_WEIGHT:
                    this.Frame.Navigate(typeof(WeightPage), groupId);
                    break;
                case SampleDataSource.GROUP_HISTORY:
                    {
                        string uriToLaunch = "http://zh.wikipedia.org/wiki/06%E6%9C%8830%E6%97%A5";//TODO
                        var uri = new Uri(uriToLaunch);

                        // Launch the URI
                        Windows.System.Launcher.LaunchUriAsync(uri);
                    }
                    break;
                default:
                    this.Frame.Navigate(typeof(SplitPage), groupId);
                    break;
                   
            }                
        }
    }
}
