using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Graphics.Display;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Data;

namespace Riddle
{
    /// <summary>
    /// Add 谜底 as prefix to show for the RiddleAnswer
    /// <see cref="Visibility.Collapsed"/>.
    /// </summary>
    public sealed class RiddleAnswerConverter : IValueConverter
    {
        private static string AnswerPrefix = "谜底： ";
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return AnswerPrefix + (value != null ? value.ToString() : "我猜我猜");
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            // return value is Visibility && (Visibility)value == Visibility.Visible;
            throw new NotImplementedException();
        }
    }
}
