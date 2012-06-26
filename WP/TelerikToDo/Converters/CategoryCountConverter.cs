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
using System.Diagnostics;

namespace TelerikToDo
{
	public class CategoryCountConverter : IValueConverter
	{
		#region IValueConverter Members

		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			
			int categoryId = (int)value;
			var categoryTasksRange = from k in SterlingService.Current.Database.Query<Task, int, int>("Task_CategoryId")
									 where k.Index == categoryId
									 select k.LazyValue;
			return categoryTasksRange.Count();
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
