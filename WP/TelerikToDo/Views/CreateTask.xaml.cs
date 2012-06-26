using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using System.Diagnostics;
using Telerik.Windows.Controls;

namespace TelerikToDo.Views
{
	public partial class CreateTask : PhoneApplicationPage
	{
		public CreateTask()
		{
			InitializeComponent();
			PopulateCategories();			
		}

		private void PopulateCategories()
		{
			CategoryPicker.ItemsSource = (from k in SterlingService.Current.Database.Query<TaskCategory, int>()
						  orderby k.Key
						  select k.LazyValue.Value);
		}

		private void CategoryPicker_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			TaskCategory selectedCategory = CategoryPicker.SelectedItem as TaskCategory;

			int projectId = -1;
			if (NavigationContext.QueryString.ContainsKey("ProjectId"))
			{
				int.TryParse(NavigationContext.QueryString["ProjectId"], out projectId);
			}
			this.SetValue(RadTileAnimation.ContainerToAnimateProperty, CategoryPicker);
			NavigationService.Navigate(new Uri("/Views/EditTask.xaml?CategoryId=" + selectedCategory.Id + "&ProjectId=" + projectId, UriKind.Relative));
		}
	}
}