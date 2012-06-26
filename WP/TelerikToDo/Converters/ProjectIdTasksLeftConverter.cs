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
using System.Linq;
using Wintellect.Sterling.Keys;
namespace TelerikToDo
{
	public class ProjectIdTasksLeftConverter : IValueConverter
	{
		#region IValueConverter Members

		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			int projectId = (int)value;

			var projectTasksRange = from k in SterlingService.Current.Database.Query<Task, int, bool, int>("Task_ProjectId_IsCompleted")
									where k.Index.Item1 == projectId
									where k.Index.Item2 == false
									select k;

			return projectTasksRange.Count();
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
