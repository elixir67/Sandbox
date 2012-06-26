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

namespace TelerikToDo
{
	public partial class AllProjects : PhoneApplicationPage
	{
		public AllProjects()
		{
			InitializeComponent();
			this.Loaded += new RoutedEventHandler(AllProjects_Loaded);
		}

		void AllProjects_Loaded(object sender, RoutedEventArgs e)
		{
			ActiveProjects.ItemsSource = from k in SterlingService.Current.Database.Query<Project, int, int>("Project_Status")
								   where k.Index == AppModel.PROJECT_STATUS_ACTIVE_ID
								   orderby k.Key descending
								   select k.LazyValue;

			NotStartedProjects.ItemsSource = from k in SterlingService.Current.Database.Query<Project, int, int>("Project_Status")
											 where k.Index == AppModel.PROJECT_STATUS_NOT_STARTED_ID
									   orderby k.Key descending
									   select k.LazyValue;

			CompletedProjects.ItemsSource = from k in SterlingService.Current.Database.Query<Project, int, int>("Project_Status")
									where k.Index == AppModel.PROJECT_STATUS_COMPLETED_ID
									orderby k.Key descending
									select k.LazyValue;
		}

		private void ShowProjectDetails(Project project)
		{
			NavigationService.Navigate(new Uri("/Views/ViewProject.xaml?ProjectId=" + project.Id, UriKind.Relative));
		}

		private void OnItemTap(object sender, Telerik.Windows.Controls.ListBoxItemTapEventArgs e)
		{
			Project task = ((sender as RadDataBoundListBox).SelectedItem as Lazy<Project>).Value;
			if (task != null)
			{
				ShowProjectDetails(task);
			}
		}

		private void NewTask_Click(object sender, EventArgs e)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/AllProjects.xaml", UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/CreateTask.xaml", UriKind.Relative));
		}
	}
}