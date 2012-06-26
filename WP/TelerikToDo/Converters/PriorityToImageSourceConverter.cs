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

namespace TelerikToDo
{
	public class PriorityToImageSourceConverter : IValueConverter
	{

		#region IValueConverter Members

		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			
			if (!(value is TaskPriority))
			{
				throw new InvalidOperationException();
			}

			TaskPriority taskPriority = (TaskPriority)value;

			string imageName = "";
			switch (taskPriority)
			{
				case TaskPriority.Low:
					imageName = "low.png";
					break;
				case TaskPriority.Medium:
					imageName = "medium.png";
					break;
				case TaskPriority.High:
					imageName = "high.png";
					break;
				case TaskPriority.Must:
					imageName = "must.png";
					break;
				default:
					break;
			}
			return new Uri("/Images/Priorities/" + imageName, UriKind.RelativeOrAbsolute);

		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
