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
	public class ProjectIdNameConverter : IValueConverter
	{
		#region IValueConverter Members

		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			int projectId = (int)value;
			string noProjectString = "Common";
			if (projectId == -1)
			{
				return noProjectString;
			}

			var projectRange = from k in SterlingService.Current.Database.Query<Project, string, int>("Project_Name")
										where k.Key == projectId
										select k.Index;
			if (projectRange.Count() > 0)
			{
				return projectRange.First();
			}
			else 
			{
				return noProjectString;
			}
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
