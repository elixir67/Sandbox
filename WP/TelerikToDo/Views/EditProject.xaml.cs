using System;
using System.Diagnostics;
using System.Windows;
using Microsoft.Phone.Controls;
using Wintellect.Sterling.Keys;
using System.Linq;
using System.Windows.Input;
using System.Windows.Controls;
using Wintellect.Sterling.Indexes;

namespace TelerikToDo
{
	public partial class EditProject : PhoneApplicationPage
	{
		private Project project;
		public EditProject()
		{
			Loaded += new RoutedEventHandler(EditProject_Loaded);
			InitializeComponent();
		}

		protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
		{
			base.OnNavigatedTo(e);
			InitProject();
			DataContext = project;
		}

		private void InitTasks()
		{
			ProjectTasks.ItemsSource = project.Tasks;
		}

		private void InitProject()
		{
			if (project != null)
			{
				InitTasks(); // keep the project info untouched, but refresh the tasks list. Needed when performing back navigation.
				return;
			}

			int projectId = -1;
			if (!NavigationContext.QueryString.ContainsKey("ProjectId") || !int.TryParse(NavigationContext.QueryString["ProjectId"], out projectId))
			{
				project = new Project();
			}
			else
			{
				project = SterlingService.Current.Database.Query<Project, int>()
						.Where(delegate(TableKey<Project, int> key) { return key.Key == projectId; })
						.First<TableKey<Project, int>>()
						.LazyValue.Value;

				Debug.Assert(project != null, "Project should not be null");
			}
		}

		void EditProject_Loaded(object sender, RoutedEventArgs e)
		{
			PopulateProjectStatus();
			StatusPicker.SelectedIndex = project.StatusId;
		}

		private void PopulateProjectStatus()
		{
			StatusPicker.ItemsSource = AppModel.ProjectStatuses;
		}

		private void SaveButton_Click(object sender, EventArgs e)
		{
			EnsureBindingIsApplied();

			if (!ValidateProject())
			{
				return;
			}

			project.StatusId = (StatusPicker.SelectedItem as ProjectStatus).Id;
			project.Save();
			NavigationService.GoBack();
		}

		private void EnsureBindingIsApplied()
		{
			object focusedElement = FocusManager.GetFocusedElement();
			if (focusedElement is TextBox)
			{
				(focusedElement as TextBox).GetBindingExpression(TextBox.TextProperty).UpdateSource();
			}
		}

		private bool ValidateProject()
		{
			if (String.IsNullOrEmpty(project.Name))
			{
				return false;
			}
			return true;
		}

		private void CancelButton_Click(object sender, EventArgs e)
		{
			NavigationService.GoBack();
		}

		private void AddTaskButton_Click(object sender, RoutedEventArgs e)
		{
			if (project.Id > 0)
			{
				AppModel.TaskDoneNextPage = new Uri("/Views/EditProject.xaml?ProjectId=" + project.Id, UriKind.Relative);
				NavigationService.Navigate(new Uri("/Views/CreateTask.xaml?ProjectId=" + project.Id, UriKind.Relative));
			}
		}
		
		private void ProjectTasks_ItemTap(object sender, Telerik.Windows.Controls.ListBoxItemTapEventArgs e)
		{
			Task task = (ProjectTasks.SelectedItem as TableIndex<Task, Tuple<int, bool>, int>).LazyValue.Value;
			if (task != null)
			{
				ShowTaskDetails(task);
			}
		}

		private void ShowTaskDetails(Task task)
		{
			NavigationService.Navigate(new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative));
		}
	}
}