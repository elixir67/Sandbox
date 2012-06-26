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
using System.Collections.Generic;

namespace TelerikToDo
{
	public class TaskCategory : IBaseModel
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

		// this is of type string because as arelative URI it can not be serialized in DB
		public string IconUri
		{
			get;
			set;
		}

		// this is of type string because as arelative URI it can not be serialized in DB
		public string SmallIconUri
		{
			get;
			set;
		}

		public Brush ColorBrush
		{
			get;
			set;
		}

		public string[] DefaultFields
		{
			get;
			set;
		}

		public static TaskCategory GetById(int categoryId)
		{
			return SterlingService.Current.Database.Load(typeof(TaskCategory), categoryId) as TaskCategory;
		}

		public static void PopulateDataBase()
		{
			List<TaskCategory> taskCategories = new List<TaskCategory>();
			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "to-dos",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 51, 153, 51)),
				IconUri = "/Images/Categories/ToDoLarge.png",
				SmallIconUri = "/Images/Categories/ToDoSmall.png",
				DefaultFields = new string[] { "PriorityPicker", "NotesContainer", "RichContent" }
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "link",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 0, 171, 169)),
				IconUri = "/Images/Categories/LinkLarge.png",
				SmallIconUri = "/Images/Categories/LinkSmall.png",
				DefaultFields = new string[] { "UrlContainer", "NotesContainer" }
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "mail",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 27, 161, 226)),
				IconUri = "/Images/Categories/MailLarge.png",
				SmallIconUri = "/Images/Categories/MailSmall.png",
				DefaultFields = new string[] { "EmailPicker" }
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "call",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 140, 191, 38)),
				IconUri = "/Images/Categories/PhoneLarge.png",
				SmallIconUri = "/Images/Categories/PhoneSmall.png",
				DefaultFields = new string[] { "PhonePicker" }
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "shopping list",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 230, 113, 184)),
				IconUri = "/Images/Categories/ShoppingLarge.png",
				SmallIconUri = "/Images/Categories/ShoppingSmall.png"
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "idea",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 240, 150, 9)),
				SmallIconUri = "/Images/Categories/IdeaSmall.png",
				IconUri = "/Images/Categories/IdeaLarge.png"
			});

			SterlingService.Current.Database.Save(new TaskCategory()
			{
				Name = "location",
				ColorBrush = new SolidColorBrush(Color.FromArgb(255, 229, 20, 0)),
				SmallIconUri = "/Images/Categories/LocationSmall.png",
				IconUri = "/Images/Categories/LocationLarge.png"
			});

			SterlingService.Current.Database.Flush();
		}
	}
}
