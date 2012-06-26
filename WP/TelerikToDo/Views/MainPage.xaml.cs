using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using Microsoft.Phone.Controls;
using Telerik.Windows.Controls;
using Telerik.Windows.Data;
using Wintellect.Sterling.Indexes;
using System.Windows.Media;
using Wintellect.Sterling.Database;

namespace TelerikToDo
{
	public partial class MainPage : PhoneApplicationPage
	{
		public MainPage()
		{
			InitializeComponent();
			this.Loaded += new RoutedEventHandler(MainPage_Loaded);
		}

		private void MainPage_Loaded(object sender, RoutedEventArgs e)
		{
			/* Uncomment the line below to delete the data */
			//SterlingService.Current.Database.Purge();

			/*
			 * Uncomment the line below to generate some test data 
			 * remember to comment it again after the data is populated.
			 */
			//GenerateTestData();

			if (IsFirstTimeAppAccess())
			{
				InitApplicationForFirstTimeUse();
			}

			PopulateCategories();
			PopulateTasks();
			PopulateProjects();
			SetOverdueState();

			if (TasksList.SortDescriptors.Count > 0)
			{
				// we don't need to recreate the descriptors everytime the page is loaded.
				return;
			}

			// Tasks are sorted by DueDate by default. We are using Sterling Indexes so that the operations are fast and not values are get from database.
			TasksList.SortDescriptors.Add(new GenericSortDescriptor<TableIndex<Task, Tuple<DateTime, bool>, int>, DateTime>(task => task.Index.Item1));

			// Tasks are grouped by DueDate and here we create custom groups based on the app logic.
			TasksList.GroupDescriptors.Add(new GenericGroupDescriptor<TableIndex<Task, Tuple<DateTime, bool>, int>, string>(delegate(TableIndex<Task, Tuple<DateTime, bool>, int> tableIndex)
			{
				if (tableIndex.Index.Item1.Date == DateTime.Now.Date)
				{
					return "TODAY";
				}
				else if (tableIndex.Index.Item1.Date == DateTime.Now.Date.AddDays(1))
				{
					return "TOMORROW";
				}
				else
				{
					return "NEXT";
				}
			})
			{
				/*
				 * this is needed so that the JumpList do not order the groups by their name. 
				 * It will keep the groups sorted in the way specified by the sort descriptors
				 */
				SortMode = ListSortMode.None
			});

		}

		// This is added in order to be able to fastly populate the database and to see the application running with a real data.
		private void InitApplicationForFirstTimeUse()
		{
			// this is the first time the app is run on device
			// populate the deatabase with the predefined categories
			TaskCategory.PopulateDataBase();

			MessageBoxResult result = MessageBox.Show("This is the first time you open the application. Do you want to generate a test data?", "One time message", MessageBoxButton.OKCancel);
			if (result == MessageBoxResult.OK)
			{
				GenerateTestData();
			}
		}

		private bool IsFirstTimeAppAccess()
		{
			return SterlingService.Current.Database.Query<TaskCategory, int>().Count() == 0;
		}

		private void PopulateCategories()
		{
			var categories = (from k in SterlingService.Current.Database.Query<TaskCategory, int>()
							  orderby k.Key
							  select k.LazyValue.Value);

			CategoriesList.ItemsSource = categories;
		}

		private void PopulateProjects()
		{
			var projectsRange = (from k in SterlingService.Current.Database.Query<Project, int, int>("Project_Status")
								 where k.Index != AppModel.PROJECT_STATUS_COMPLETED_ID
								 select k.LazyValue);

			ProjectsList.ItemsSource = projectsRange;
		}

		private void SetOverdueState()
		{
			int overdueTasksCount = (from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
									 where k.Index.Item1 < DateTime.Today.Date
									 where k.Index.Item2 == false
									 select k).Count();

			OverdueCountTextBlock.Text = overdueTasksCount.ToString();
			OverdueIcon.Visibility = (overdueTasksCount > 0) ? Visibility.Visible : Visibility.Collapsed;
		}

		private void PopulateTasks()
		{
			TasksList.ItemsSource = (from k in SterlingService.Current.Database.Query<Task, DateTime, bool, int>("Task_DueDate_IsCompleted")
									 where k.Index.Item1 >= DateTime.Today.Date
									 where k.Index.Item2 == false
									 orderby k.Index.Item1 ascending
									 select k);
		}

		private void NewProjectButton_Click(object sender, RoutedEventArgs e)
		{
			NavigationService.Navigate(new Uri("/Views/EditProject.xaml", UriKind.Relative));
		}

		private void NewTaskButton_Click(object sender, RoutedEventArgs e)
		{
			NavigationService.Navigate(new Uri("/Views/CreateTask.xaml", UriKind.Relative));
		}

		private void AllTasks_Click(object sender, RoutedEventArgs e)
		{
			NavigationService.Navigate(new Uri("/Views/AllTasks.xaml", UriKind.Relative));
		}

		private void AllProjects_Click(object sender, RoutedEventArgs e)
		{
			NavigationService.Navigate(new Uri("/Views/AllProjects.xaml", UriKind.Relative));
		}

		private void TasksList_ItemTap(object sender, ListBoxItemTapEventArgs e)
		{
			if (TasksList.SelectedItem != null)
			{
				Task task = (TasksList.SelectedItem as TableIndex<Task, Tuple<DateTime, bool>, int>).LazyValue.Value;
				NavigationService.Navigate(new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative));
			}
		}

		private void ProjectsList_ItemTap(object sender, ListBoxItemTapEventArgs e)
		{
			if (ProjectsList.SelectedItem != null)
			{
				Project project = (ProjectsList.SelectedItem as Lazy<Project>).Value;
				NavigationService.Navigate(new Uri("/Views/ViewProject.xaml?ProjectId=" + project.Id, UriKind.Relative));
			}
		}

		private void CategoriesList_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			TaskCategory selectedCategory = CategoriesList.SelectedItem as TaskCategory;
			if (selectedCategory != null)
			{
				this.SetValue(RadTransitionControl.TransitionProperty, new RadTileTransition());
				this.SetValue(RadTileAnimation.ContainerToAnimateProperty, CategoriesList);
				NavigationService.Navigate(new Uri("/Views/TasksByCategory.xaml?CategoryId=" + selectedCategory.Id, UriKind.Relative));
			}
		}





		/* ----- for testing purposes only */
		private void GenerateTestData()
		{
			int tasksCount = 50;
			int projectsCount = 5;
			int categoriesCount = 6;
			int projectStatusCount = 3;
			List<Task> tasks = new List<Task>();

			for (int i = 0; i < tasksCount; i++)
			{
				tasks.Add(new Task()
				{
					Name = "Task" + i,
					CategoryId = (int)(i % categoriesCount) + 1,
					ProjectId = (int)(i % projectsCount),
					DueDate = DateTime.Today.AddDays((int)i % (tasksCount / 5)),
					Priority = TaskPriority.Medium,
					Notes = "Notes" + i,
					Recurrence = TaskRecurrence.Daily
				});
			}

			foreach (var item in tasks)
			{
				SterlingService.Current.Database.Save(item);
			}

			List<Project> projects = new List<Project>();
			for (int i = 0; i < projectsCount; i++)
			{
				projects.Add(new Project()
				{
					Name = "Project" + i,
					DueDate = DateTime.Today.AddDays((int)i % (tasksCount / 5)),
					Notes = "Notes" + i,
					StatusId = (int)(i % projectStatusCount)
				});
			}

			foreach (var item in projects)
			{
				SterlingService.Current.Database.Save(item);
			}

			SterlingService.Current.Database.Flush();
		}
	}
}