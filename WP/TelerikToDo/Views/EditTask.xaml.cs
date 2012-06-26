using System;
using System.Collections.Generic;
using System.Device.Location;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Controls.Maps;
using Microsoft.Phone.Tasks;
using Microsoft.Xna.Framework.Audio;
using Telerik.Windows.Controls;
using Wintellect.Sterling.Keys;

namespace TelerikToDo
{
	public partial class EditTask : PhoneApplicationPage
	{
		private Task task;
		private Microphone microphone = Microphone.Default;
		private byte[] voiceBuffer;
		private MemoryStream voiceStream = new MemoryStream();
		private SoundEffect voiceSoundEffect;
		private byte[] photoData;
		private byte[] voiceData;
		private GeoCoordinateWatcher geoCoordinateWatcher;
		private Pushpin mapPushpin;
		private bool isLoaded;

		public EditTask()
		{
			InitializeComponent();

			this.Loaded += this.OnLoaded;
			this.Unloaded += this.OnUnloaded;
		}

		protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
		{
			base.OnNavigatedTo(e);

			InitTask();
			OrderFields();

			SetRichElementsState();
			CategoryPresenter.DataContext = TaskCategory.GetById(task.CategoryId);
			this.DataContext = task;
		}

		private void SetRichElementsState()
		{
			// if tombstoning - don't overwrite any selected photo from user with the one from DB.
			if (photoData == null)
			{
				task.PreviewPhoto(PhotoPreviewElement);
			}

			SetPhotoPreviewState();
			SetVoiceMemoPreviewState();
		}

		private void InitTask()
		{
			if (task != null) return;

			if (!NavigationContext.QueryString.ContainsKey("TaskId"))
			{
				task = new Task();
				int categoryId = 0;
				int.TryParse(NavigationContext.QueryString["CategoryId"], out categoryId);

				task.CategoryId = categoryId;

				if (NavigationContext.QueryString.ContainsKey("ProjectId"))
				{
					int projectId;
					int.TryParse(NavigationContext.QueryString["ProjectId"], out projectId);
					task.ProjectId = projectId;
				}
			}
			else
			{
				int taskId;
				int.TryParse(NavigationContext.QueryString["TaskId"], out taskId);

				task = SterlingService.Current.Database.Query<Task, int>()
						.Where(delegate(TableKey<Task, int> key) { return key.Key == taskId; })
						.First<TableKey<Task, int>>()
						.LazyValue.Value;

				Debug.Assert(task != null, "Task should not be null");
			}
		}

		// For each category we want to display different fields. The rest of the fields remain in the advanced panel.
		private void OrderFields()
		{
			string[] categoryFields = TaskCategory.GetById(task.CategoryId).DefaultFields;
			if (categoryFields == null) return;

			for (int i = 0; i < categoryFields.Length; i++)
			{
				UIElement field = this.FindName(categoryFields[i]) as UIElement;
				if (AdvancedFieldsContainer.Children.Contains(field)) // in case of thombstoning
				{
					AdvancedFieldsContainer.Children.Remove(field);
					CategoryFieldsContainer.Children.Add(field);
				}
			}

			CategoryFieldsContainer.DataContext = task;
		}

		private void OnLoaded(object sender, RoutedEventArgs e)
		{
			this.PopulateProjects();
			this.isLoaded = true;
		}

		private void OnUnloaded(object sender, RoutedEventArgs e)
		{
			this.isLoaded = false;

			this.microphone.BufferReady -= Microfone_BufferReady;
			this.microphone.Stop();

			if (this.geoCoordinateWatcher != null)
			{
				this.geoCoordinateWatcher.StatusChanged -= this.geoCoordinateWatcher_StatusChanged;
				this.geoCoordinateWatcher.Stop();
			}

			if (this.voiceSoundEffect != null)
			{
				this.voiceSoundEffect.Dispose();
			}

			this.voiceStream.Dispose();
		}

		private void PopulateProjects()
		{
			List<DummyProjectViewModel> projects = new List<DummyProjectViewModel>();

			// Create one virtual project so that an item always has a project assigned 
			// by default. This is the reason why we need to have this view model. 
			// Otherwise it would be better to bind the projects directly to the result of the query.
			DummyProjectViewModel virtualProject = new DummyProjectViewModel() { Name = "Common", Id = -1 };
			projects.Add(virtualProject);

			DummyProjectViewModel selectedItem = virtualProject;
			foreach (var item in SterlingService.Current.Database.Query<Project, string, int>("Project_Name"))
			{
				DummyProjectViewModel dummyItem = new DummyProjectViewModel() { Name = item.Index, Id = item.Key };
				projects.Add(dummyItem);
				if (item.Key == task.ProjectId)
				{
					selectedItem = dummyItem;
				}
			}

			ProjectPicker.ItemsSource = projects;
			ProjectPicker.SelectedItem = selectedItem;
		}

		bool deletePhotoOnSave = false;
		private void DeletePhoto_Click(object sender, MouseButtonEventArgs e)
		{
			photoData = null;
			deletePhotoOnSave = true;
			PhotoPreviewElement.Source = new BitmapImage(new Uri("/Images/PhotoPreviewPlaceholder.png", UriKind.RelativeOrAbsolute));
			SetPhotoPreviewState();
		}

		private void SetPhotoPreviewState()
		{
			bool isPhotoAvailable = false;
			if (photoData != null || ((!String.IsNullOrEmpty(task.PhotoFileName)) && !deletePhotoOnSave))
			{
				isPhotoAvailable = true;
			}

			EditPhotoIcon.Visibility = (isPhotoAvailable) ? Visibility.Visible : Visibility.Collapsed;
			DeletePhotoIcon.Visibility = (isPhotoAvailable) ? Visibility.Visible : Visibility.Collapsed;
			AddPhotoIcon.Visibility = (!isPhotoAvailable) ? Visibility.Visible : Visibility.Collapsed;
		}

		private void EditPhoto_Click(object sender, MouseButtonEventArgs e)
		{
			ChooseNewPhoto();
		}


		private void AddPhoto_Click(object sender, MouseButtonEventArgs e)
		{
			ChooseNewPhoto();
		}

		bool isPhotoChooserTaskOpen = false;
		private void ChooseNewPhoto()
		{
			if (isPhotoChooserTaskOpen) return; // an exception will be thrown if we try to open the task more than once
			PhotoChooserTask photoChooserTask;

			photoChooserTask = new PhotoChooserTask();
			photoChooserTask.Completed += new EventHandler<PhotoResult>(photoChooserTask_Completed);
			isPhotoChooserTaskOpen = true;
			photoChooserTask.Show();
		}

		private void photoChooserTask_Completed(object sender, PhotoResult e)
		{
			if (!this.isLoaded || e.TaskResult != TaskResult.OK)
			{
				return;
			}
			isPhotoChooserTaskOpen = false;
			photoData = new byte[e.ChosenPhoto.Length];

			e.ChosenPhoto.Read(photoData, 0, photoData.Length);

			BitmapImage image = new BitmapImage();
			image.SetSource(e.ChosenPhoto);
			deletePhotoOnSave = false;
			PhotoPreviewElement.Source = image;
			SetPhotoPreviewState();
		}

		bool deleteVoiceMemoOnSave = false;
		private void DeleteVoiceMemo_Click(object sender, MouseButtonEventArgs e)
		{
			voiceBuffer = null;
			deleteVoiceMemoOnSave = true;
			VoicePicker.Source = new BitmapImage(new Uri("/Images/VoicePreviewPlaceholder.png", UriKind.RelativeOrAbsolute));
			SetVoiceMemoPreviewState();
		}

		private void EditVoiceMemo_Click(object sender, MouseButtonEventArgs e)
		{
			voiceBuffer = null;
			StartVoiceMemoRecording();
		}

		private void AddVoiceMemo_Click(object sender, MouseButtonEventArgs e)
		{
			StartVoiceMemoRecording();
		}

		private void StartVoiceMemoRecording()
		{
			if (microphone.State == MicrophoneState.Started) return;

			microphone.BufferReady += Microfone_BufferReady;
			microphone.BufferDuration = TimeSpan.FromMilliseconds(200);
			voiceBuffer = new byte[microphone.GetSampleSizeInBytes(microphone.BufferDuration)];
			microphone.Start();

			SetVoiceMemoPreviewState();
		}

		private void StopVoiceMemo_Click(object sender, MouseButtonEventArgs e)
		{
			if (microphone.State != MicrophoneState.Started) return;
			deleteVoiceMemoOnSave = false;
			microphone.Stop();
			microphone.BufferReady -= Microfone_BufferReady;

			voiceData = voiceStream.ToArray();

			voiceSoundEffect = new SoundEffect(voiceData, microphone.SampleRate, AudioChannels.Mono);
			voiceSoundEffect.Play();

			SetVoiceMemoPreviewState();
		}

		private void SetVoiceMemoPreviewState()
		{
			bool isVoiceMemoAvailable = false;
			if (voiceBuffer != null || ((!String.IsNullOrEmpty(task.VoiceMemoFileName)) && !deleteVoiceMemoOnSave))
			{
				isVoiceMemoAvailable = true;
			}

			bool isRecordingInProgress = (microphone.State == MicrophoneState.Started) ? true : false;

			DeleteVoiceMemoIcon.Visibility = (isVoiceMemoAvailable) ? Visibility.Visible : Visibility.Collapsed;
			AddVoiceMemoIcon.Visibility = (!isVoiceMemoAvailable) ? Visibility.Visible : Visibility.Collapsed;

			EditVoiceMemoIcon.Visibility = (isVoiceMemoAvailable && !isRecordingInProgress) ? Visibility.Visible : Visibility.Collapsed;
			StopVoiceMemoIcon.Visibility = (isRecordingInProgress) ? Visibility.Visible : Visibility.Collapsed;
		}

		private void Microfone_BufferReady(object sender, EventArgs e)
		{
			microphone.GetData(voiceBuffer);
			voiceStream.Write(voiceBuffer, 0, voiceBuffer.Length);
		}

		private void AddPhoneButton_Click(object sender, RoutedEventArgs e)
		{
			PhoneNumberChooserTask phoneNumberChooserTask = new PhoneNumberChooserTask();
			phoneNumberChooserTask.Completed += new EventHandler<PhoneNumberResult>(phoneNumberChooserTask_Completed);
			phoneNumberChooserTask.Show();
		}

		private void phoneNumberChooserTask_Completed(object sender, PhoneNumberResult e)
		{
			if (e.TaskResult == TaskResult.OK)
			{
				task.Phone = e.PhoneNumber;
			}
		}

		private void ShowAdvancedOptions_Click(object sender, RoutedEventArgs e)
		{
			AdvancedFieldsContainer.Visibility = Visibility.Visible;
			(sender as UIElement).Visibility = Visibility.Collapsed;

			// if the image element was in the collapsed panel the photo has not been previewed so far.
			SetRichElementsState();
		}

		private void GetEmail_Click(object sender, RoutedEventArgs e)
		{
			EmailAddressChooserTask emailAddressChooserTask = new EmailAddressChooserTask();
			emailAddressChooserTask.Completed += new EventHandler<EmailResult>(emailAddressChooserTask_Completed);
			emailAddressChooserTask.Show();
		}

		private void emailAddressChooserTask_Completed(object sender, EmailResult e)
		{
			if (e.TaskResult == TaskResult.OK)
			{
				task.Email = e.Email;
			}
		}

		private void BingMap1_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
		{
			Point tapPoint = e.GetPosition(BingMap1);

			BingMap1.Children.Clear();

			GeoCoordinate loc = BingMap1.ViewportPointToLocation(tapPoint);

			mapPushpin = new Pushpin();
			mapPushpin.Location = loc;

			// Add the MapLayer to the Map so the "Pushpin" gets displayed
			BingMap1.Children.Add(mapPushpin);

			task.Latitude = loc.Latitude;
			task.Longitude = loc.Longitude;
		}

		void geoCoordinateWatcher_StatusChanged(object sender, GeoPositionStatusChangedEventArgs e)
		{
			if (e.Status == GeoPositionStatus.Ready)
			{
				geoCoordinateWatcher.Stop();

				GeoCoordinate location = geoCoordinateWatcher.Position.Location;

				double zoomLevel = 15;
				BingMap1.SetView(location, zoomLevel);

				mapPushpin = new Pushpin();
				mapPushpin.Location = location;

				BingMap1.Children.Add(mapPushpin);
			}
		}

		private void ApplicationBarInfo_ButtonClick(object sender, ApplicationBarButtonClickEventArgs e)
		{
			if (e.Button == LocationPicker.ApplicationBarInfo.Buttons[0])
			{
				if (geoCoordinateWatcher == null)
				{
					geoCoordinateWatcher = new GeoCoordinateWatcher(GeoPositionAccuracy.High);
					geoCoordinateWatcher.MovementThreshold = 20; // Use MovementThreshold to ignore noise in the signal.
					geoCoordinateWatcher.StatusChanged += this.geoCoordinateWatcher_StatusChanged;
				}
				geoCoordinateWatcher.Start();
			}
			else if (e.Button == LocationPicker.ApplicationBarInfo.Buttons[1])
			{
				GeoCoordinate location;
				if (mapPushpin != null)
				{
					location = mapPushpin.Location;
				}
				else
				{
					location = BingMap1.TargetBoundingRectangle.Center;
				}
				task.Latitude = location.Latitude;
				task.Longitude = location.Longitude;
				LocationPicker.IsPopupOpen = false;
			}
			else if (e.Button == LocationPicker.ApplicationBarInfo.Buttons[2])
			{
				task.Latitude = 0;
				task.Longitude = 0;
				LocationPicker.IsPopupOpen = false;
			}
		}

		// when click on the app button the textboxes are not blurred and thus binding update is not triggered.
		private void EnsureBindingIsApplied()
		{
			object focusedElement = FocusManager.GetFocusedElement();
			if (focusedElement is TextBox)
			{
				(focusedElement as TextBox).GetBindingExpression(TextBox.TextProperty).UpdateSource();
			}
		}

		private void SaveButton_Click(object sender, EventArgs e)
		{
			EnsureBindingIsApplied();

			if (!ValidateTask())
			{
				return;
			}

			DummyProjectViewModel selectedProject = ProjectPicker.SelectedItem as DummyProjectViewModel;
			if (selectedProject.Id > -1)
			{
				task.ProjectId = selectedProject.Id;
			}

			if (deletePhotoOnSave)
			{
				task.DeletePhoto();
			}
			else if (photoData != null)
			{
				task.AssignPhoto(photoData);
			}

			if (deleteVoiceMemoOnSave)
			{
				task.DeleteVoiceMemo();
			}
			else if (voiceData != null)
			{
				task.AssignVoiceMemo(voiceData);
			}

			task.Save();

			this.NavigateToNextPage();
		}

		private bool ValidateTask()
		{
			if (String.IsNullOrEmpty(task.Name))
			{
				TaskName.Focus();
				return false;
			}

			return true;
		}

		private void CancelButton_Click(object sender, EventArgs e)
		{
			task = null;
			this.NavigateToNextPage();
		}

		private void NavigateToNextPage()
		{
			Uri uriToNavigate = GetUriToNavigate();
			AppModel.TaskDoneNextPage = null;
			NavigationService.Navigate(uriToNavigate);

		}

		private Uri GetUriToNavigate()
		{
			return (AppModel.TaskDoneNextPage != null) ? AppModel.TaskDoneNextPage : new Uri("/Views/MainPage.xaml", UriKind.Relative);
		}
	}

	public class DummyProjectViewModel
	{
		public string Name
		{
			get;
			set;
		}

		public int Id
		{
			get;
			set;
		}
	}
}

