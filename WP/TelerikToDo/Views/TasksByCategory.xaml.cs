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
using System.Diagnostics;
using Wintellect.Sterling.Indexes;

namespace TelerikToDo
{
	public partial class TasksByCategory : PhoneApplicationPage
	{
		int categoryId = -1;
		public TasksByCategory()
		{
			InitializeComponent();
			Loaded += new RoutedEventHandler(AllTasks_Loaded);
		}
		
		void AllTasks_Loaded(object sender, RoutedEventArgs e)
		{			
			int.TryParse(NavigationContext.QueryString["CategoryId"], out categoryId);
			Debug.Assert(categoryId != -1, "CategoryId should not be null");

			CategoryTasks.ItemsSource = from k in SterlingService.Current.Database.Query<Task, int, int>("Task_CategoryId")
									  where k.Index == categoryId
									  select k;
		}

		private void ShowTaskDetails(Task task)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/TasksByCategory.xaml?CategoryId=" + categoryId, UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative));
		}

		private void Tasks_ItemTap(object sender, Telerik.Windows.Controls.ListBoxItemTapEventArgs e)
		{
			Task task = ((sender as RadDataBoundListBox).SelectedItem as TableIndex<Task, int, int>).LazyValue.Value;
			if (task != null)
			{
				ShowTaskDetails(task);
			}
		}

		private void NewTask_Click(object sender, EventArgs e)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/TasksByCategory.xaml?CategoryId=" + categoryId, UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/CreateTask.xaml", UriKind.Relative));
		}
	}
}