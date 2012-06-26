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
using Telerik.Windows.Controls;
using Wintellect.Sterling.Indexes;

namespace TelerikToDo
{
	public partial class AllTasks : PhoneApplicationPage
	{
		public AllTasks()
		{
			InitializeComponent();
			Loaded += new RoutedEventHandler(AllTasks_Loaded);
		}

		void AllTasks_Loaded(object sender, RoutedEventArgs e)
		{
			TodayTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
								  where k.Index.Item1.Date == DateTime.Today.Date
								  where k.Index.Item2 == false
								  orderby k.Index ascending
								  select k;

			TomorrowTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
									 where k.Index.Item1.Date == DateTime.Today.Date.AddDays(1)
									 where k.Index.Item2 == false
									 orderby k.Index ascending
									 select k;

			NextTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
								 where k.Index.Item1.Date > DateTime.Today.Date.AddDays(1)
								 where k.Index.Item2 == false
								 orderby k.Index ascending
								 select k;

			CompletedTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
									  where k.Index.Item2 == true
									  orderby k.Index ascending
									  select k;

			DelayedTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
									where k.Index.Item1.Date < DateTime.Today.Date
									where k.Index.Item2 == false
									orderby k.Index descending
									select k;
		}

		private void ShowTaskDetails(Task task)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/AllTasks.xaml", UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative));
		}

		private void Tasks_ItemTap(object sender, Telerik.Windows.Controls.ListBoxItemTapEventArgs e)
		{
			object selectedItem = (sender as RadDataBoundListBox).SelectedItem;
			if (selectedItem != null)
			{
				Task task = (selectedItem as TableIndex<Task, Tuple<DateTime, bool>, int>).LazyValue.Value;
				if (task != null)
				{
					ShowTaskDetails(task);
				}
			}
		}

		private void NewTask_Click(object sender, EventArgs e)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/AllTasks.xaml", UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/CreateTask.xaml", UriKind.Relative));
		}
	}
}