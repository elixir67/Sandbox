using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows;
using System.IO.IsolatedStorage;
using System.IO;
using Microsoft.Xna.Framework.Audio;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using Microsoft.Phone.Tasks;

namespace TelerikToDo
{
	public class Task : BaseModel
	{
		private string name;
		public string Name
		{
			get { return this.name; }

			set
			{
				if (value != this.name)
				{
					this.name = value;
                    this.OnPropertyChanged("Name");
				}
			}

		}
		private int categoryId;
		public int CategoryId
		{
			get { return this.categoryId; }

			set
			{
				if (value != this.categoryId)
				{
					this.categoryId = value;
                    this.OnPropertyChanged("CategoryId");
				}
			}
		}

		int projectId;
		public int ProjectId
		{
			get { return this.projectId; }

			set
			{
				if (value != this.projectId)
				{
					this.projectId = value;
                    this.OnPropertyChanged("ProjectId");
				}
			}
		}

		private DateTime? dueDate;
		public DateTime? DueDate
		{
			get { return this.dueDate; }

			set
			{
				if (value != this.dueDate)
				{
					this.dueDate = value;
                    this.OnPropertyChanged("DueDate");
				}
			}
		}

		TaskPriority priority;
		public TaskPriority Priority
		{
			get { return this.priority; }

			set
			{
				if (value != this.priority)
				{
					this.priority = value;
                    this.OnPropertyChanged("Priority");
				}
			}
		}

		string notes;
		public string Notes
		{
			get { return this.notes; }

			set
			{
				if (value != this.notes)
				{
					this.notes = value;
                    this.OnPropertyChanged("Notes");
				}
			}
		}

		string picture;
		public string PhotoFileName
		{
			get { return this.picture; }

			set
			{
				if (value != this.picture)
				{
					this.picture = value;
                    this.OnPropertyChanged("Picture");
				}
			}
		}

		string voice;
		public string VoiceMemoFileName
		{
			get { return this.voice; }

			set
			{
				if (value != this.voice)
				{
					this.voice = value;
                    this.OnPropertyChanged("Voice");
				}
			}
		}

		double latitude;
		public double Latitude
		{
			get { return this.latitude; }

			set
			{
				if (value != this.latitude)
				{
					this.latitude = value;
                    this.OnPropertyChanged("Latitude");
				}
			}
		}

		double longitute;
		public double Longitude
		{
			get { return this.longitute; }

			set
			{
				if (value != this.longitute)
				{
					this.longitute = value;
                    this.OnPropertyChanged("Longitute");
				}
			}
		}

		TaskRecurrence recurrence;
		public TaskRecurrence Recurrence
		{
			get { return this.recurrence; }

			set
			{
				if (value != this.recurrence)
				{
					this.recurrence = value;
                    this.OnPropertyChanged("Recurrence");
				}
			}
		}

		string url;
		public string Url
		{
			get { return this.url; }

			set
			{
				if (value != this.url)
				{
					this.url = value;
                    this.OnPropertyChanged("Url");
				}
			}
		}

		string email;
		public string Email
		{
			get { return this.email; }

			set
			{
				if (value != this.email)
				{
					this.email = value;
                    this.OnPropertyChanged("Email");
				}
			}
		}

		string phone;
		public string Phone
		{
			get { return this.phone; }

			set
			{
				if (value != this.phone)
				{
					this.phone = value;
                    this.OnPropertyChanged("Phone");
				}
			}
		}

		bool isCompleted;
		public bool IsCompleted
		{
			get { return this.isCompleted; }

			set
			{
				if (value != this.isCompleted)
				{
					this.isCompleted = value;
                    this.OnPropertyChanged("IsCompleted");
				}
			}
		}

		public void Delete()
		{
			this.DeletePhoto();
			this.DeleteVoiceMemo();

			SterlingService.Current.Database.Delete(this);
			SterlingService.Current.Database.Flush();
		}

		public void DeleteVoiceMemo()
		{
			if (String.IsNullOrEmpty(this.VoiceMemoFileName))
			{
				return;
			}
			string filePath = System.IO.Path.Combine(AppModel.ASSETS_FOLDER, this.VoiceMemoFileName);
			this.DeleteAsset(filePath);
			this.VoiceMemoFileName = null;
		}

		public void DeletePhoto()
		{
			if (String.IsNullOrEmpty(this.PhotoFileName))
			{
				return;
			}
			string filePath = System.IO.Path.Combine(AppModel.ASSETS_FOLDER, this.PhotoFileName);
			this.DeleteAsset(filePath);
			this.PhotoFileName = null;
		}

		private void DeleteAsset(string assetFilePath)
		{
			var isoFile = IsolatedStorageFile.GetUserStoreForApplication();
			if (isoFile.FileExists(assetFilePath))
			{
				isoFile.DeleteFile(assetFilePath);
			}
		}

		public void SaveAssetToLocalStorage(string fileName, byte[] content)
		{
			string assetsFolder = AppModel.ASSETS_FOLDER;
			var isoFile = IsolatedStorageFile.GetUserStoreForApplication();
			if (!isoFile.DirectoryExists(assetsFolder))
			{
				isoFile.CreateDirectory(assetsFolder);
			}

			string filePath = System.IO.Path.Combine(assetsFolder, fileName);
			using (var stream = isoFile.CreateFile(filePath))
			{
				stream.Write(content, 0, content.Length);
			}
		}

		public void AssignPhoto(byte[] photoData)
		{
			this.DeletePhoto();

			string imgName = Guid.NewGuid().ToString();
			SaveAssetToLocalStorage(imgName, photoData);
			this.PhotoFileName = imgName;
		}

		public void AssignVoiceMemo(byte[] voiceData)
		{
			this.DeleteVoiceMemo();

			string voiceRecordingName = Guid.NewGuid().ToString();
			this.SaveAssetToLocalStorage(voiceRecordingName, voiceData);
			this.VoiceMemoFileName = voiceRecordingName;
		}

		public void Save()
		{
			SterlingService.Current.Database.Save(this);
			SterlingService.Current.Database.Flush();
		}

		public void PlayVoiceMemo()
		{
			if (String.IsNullOrEmpty(this.VoiceMemoFileName)) return;

			var isoFile = IsolatedStorageFile.GetUserStoreForApplication();

			string filePath = System.IO.Path.Combine(AppModel.ASSETS_FOLDER, this.VoiceMemoFileName);
			using (IsolatedStorageFileStream voiceStream = isoFile.OpenFile(
				filePath, FileMode.Open, FileAccess.Read))
			{
				byte[] voiceData = new byte[voiceStream.Length];
				voiceStream.Read(voiceData, 0, voiceData.Length);

                using (SoundEffect voiceSoundEffect = new SoundEffect(voiceData, Microphone.Default.SampleRate, AudioChannels.Mono))
                {
                    voiceSoundEffect.Play();
                }
			}
		}

		public void PreviewPhoto(Image imageElement)
		{
			if (String.IsNullOrEmpty(this.PhotoFileName) || imageElement == null)
			{
				return;
			}

			string filePath = System.IO.Path.Combine(AppModel.ASSETS_FOLDER, this.PhotoFileName);
			var isoFile = IsolatedStorageFile.GetUserStoreForApplication();
			if (!isoFile.FileExists(filePath)) return;

			using (var imageStream = isoFile.OpenFile(
				filePath, FileMode.Open, FileAccess.Read))
			{
				BitmapImage bi = new BitmapImage();
				bi.SetSource(imageStream);
				imageElement.Source = bi;
			}
		}

		public void ShowLocation()
		{
			if (this.Latitude != 0 && this.Longitude != 0)
			{
				WebBrowserTask webBrowserTask = new WebBrowserTask();
				webBrowserTask.URL = "maps:" + this.Latitude + "%2C" + this.Longitude;
				webBrowserTask.Show();
			}
		}
	}
}
