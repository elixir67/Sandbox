using System;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Input;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Phone.Tasks;
using Wintellect.Sterling.Keys;

namespace TelerikToDo
{
	public partial class ViewTask : PhoneApplicationPage
	{
		private Task task;
		public ViewTask()
		{
			InitializeComponent();
		}

		protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
		{
			base.OnNavigatedTo(e);

			InitTask();
	
			DataContext = task;

			task.PreviewPhoto(PhotoPreview);

			(ApplicationBar.Buttons[0] as ApplicationBarIconButton).IsEnabled = !task.IsCompleted;			
		}

		private void InitTask()
		{
			int taskId = -1;
			int.TryParse(NavigationContext.QueryString["TaskId"], out taskId);

			Debug.Assert(taskId != -1, "TaskId should not be null");

			task = SterlingService.Current.Database.Query<Task, int>()
					.Where(delegate(TableKey<Task, int> key) { return key.Key == taskId; })
					.First<TableKey<Task, int>>()
					.LazyValue.Value;

			LocationPicker.Visibility = (task.Latitude != 0 && task.Longitude!= 0) ? Visibility.Visible : Visibility.Collapsed;

			Debug.Assert(task != null, "Task should not be null");
		}

		private void PlayTaskVoiceRecording(object sender, RoutedEventArgs e)
		{
			task.PlayVoiceMemo();
		}

		private void ShowTaskLocation(object sender, RoutedEventArgs e)
		{
			task.ShowLocation();
		}

		private void CompleteButton_Click(object sender, EventArgs e)
		{
			task.IsCompleted = true;
			task.Save();
			NavigateToNextPage();
		}

		private void DeleteButton_Click(object sender, EventArgs e)
		{
			task.Delete();
			NavigateToNextPage();
		}

		private void EditButton_Click(object sender, EventArgs e)
		{
			AppModel.TaskDoneNextPage = new Uri("/Views/ViewTask.xaml?TaskId=" + task.Id, UriKind.Relative);
			NavigationService.Navigate(new Uri("/Views/EditTask.xaml?TaskId=" + task.Id, UriKind.Relative));
		}

		private void NavigateToNextPage()
		{
			NavigationService.GoBack();
		}

		private void Url_Click(object sender, MouseButtonEventArgs e)
		{
			WebBrowserTask browserTask = new WebBrowserTask();
			browserTask.URL = task.Url;
			browserTask.Show();
		}

		private void Phone_Click(object sender, MouseButtonEventArgs e)
		{
			PhoneCallTask phoneCallTask = new PhoneCallTask();
			phoneCallTask.PhoneNumber = task.Phone;
			phoneCallTask.Show();
		}

		private void Email_Click(object sender, MouseButtonEventArgs e)
		{
			EmailComposeTask emailTask = new EmailComposeTask();
			emailTask.To = task.Email;
			emailTask.Show();
		}
	}
}