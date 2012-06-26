using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Data;
using System.Collections.Generic;
using System.Windows.Media.Imaging;
using System.Diagnostics;

namespace TelerikToDo
{
	public class TaskIconsConverter : IValueConverter
	{
		#region IValueConverter Members

		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			List<Image> images = new List<Image>();
			Task task = value as Task;
			
			if (task == null) return images;

			if (!String.IsNullOrEmpty(task.PhotoFileName)) {
				images.Add(new Image() { Source = new BitmapImage(new Uri("/Images/TaskIcons/photo.png", UriKind.RelativeOrAbsolute)) });
			}

			if (!String.IsNullOrEmpty(task.VoiceMemoFileName))
			{
				images.Add(new Image() { Source = new BitmapImage(new Uri("/Images/TaskIcons/voiceMemo.png", UriKind.RelativeOrAbsolute)) });
			}

			if (task.Longitude != 0)
			{
				images.Add(new Image() { Source = new BitmapImage(new Uri("/Images/TaskIcons/location.png", UriKind.RelativeOrAbsolute)) });
			}

			if (task.Recurrence != TaskRecurrence.No)
			{
				images.Add(new Image() { Source = new BitmapImage(new Uri("/Images/TaskIcons/recurrence.png", UriKind.RelativeOrAbsolute)) });
			}

			return images;
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
