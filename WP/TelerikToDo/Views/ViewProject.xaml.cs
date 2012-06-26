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
using Wintellect.Sterling.Keys;
using System.Diagnostics;
using Wintellect.Sterling.Indexes;

namespace TelerikToDo
{
	public partial class ViewProject : PhoneApplicationPage
	{
		private Project project;
		public ViewProject()
		{
			InitializeComponent();
		}

		protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
		{
			base.OnNavigatedTo(e);
			InitProject();
			InitTasks();

			DataContext = project;
		}

		private void InitTasks()
		{
			ProjectTasks.ItemsSource = project.Tasks;
		}

		private void InitProject()
		{
			int projectId = -1;
			int.TryParse(NavigationContext.QueryString["ProjectId"], out projectId);

			Debug.Assert(projectId != -1, "ProjectId should not be null");

			project = SterlingService.Current.Database.Query<Project, int>()
					.Where(delegate(TableKey<Project, int> key) { return key.Key == projectId; })
					.First<TableKey<Project, int>>()
					.LazyValue.Value;

			Debug.Assert(project != null, "Project should not be null");
		}

		private void ShowTaskDetails(Task task)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/ViewProject.xaml?ProjectId=" + project.Id, UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative));
		}

		private void ProjectTasks_ItemTap(object sender, Telerik.Windows.Controls.ListBoxItemTapEventArgs e)
		{
			Task task = (ProjectTasks.SelectedItem as TableIndex<Task, Tuple<int, bool>, int>).LazyValue.Value;
			if (task != null)
			{
				ShowTaskDetails(task);
			}
		}
		private void CompleteButton_Click(object sender, EventArgs e)
		{
			project.MarkAsCompleted();
			NavigateToNextPage();
		}
		
		private void NavigateToNextPage()
		{
			NavigationService.GoBack();
		}

		private void DeleteButton_Click(object sender, EventArgs e)
		{
			project.Delete();
			NavigateToNextPage();
		}

		private void EditButton_Click(object sender, EventArgs e)
		{
			NavigationService.Navigate(new Uri("/Views/EditProject.xaml?ProjectId=" + project.Id, UriKind.Relative));
		}

		private void AddTaskButton_Click(object sender, RoutedEventArgs e)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/ViewProject.xaml?ProjectId=" + project.Id, UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/CreateTask.xaml?ProjectId=" + project.Id, UriKind.Relative));
		}
	}
}