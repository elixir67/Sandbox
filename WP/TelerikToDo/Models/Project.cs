using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows;
using System.Collections;

namespace TelerikToDo
{
	public class Project : BaseModel
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

		int statusId;
		public int StatusId
		{
			get { return this.statusId; }

			set
			{
				if (value != this.statusId)
				{
					this.statusId = value;
                    this.OnPropertyChanged("StatusId");
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

		public void Delete()
		{
			MessageBoxResult mbr = MessageBox.Show("Delete project tasks?", "Deleting project", MessageBoxButton.OKCancel);

			// mark tasks as completed
			var projectTasksRange = from k in SterlingService.Current.Database.Query<Task, int, bool, int>("Task_ProjectId_IsCompleted")
									where k.Index.Item1 == this.Id
									select k.LazyValue.Value;

			foreach (Task item in projectTasksRange)
			{
				if (mbr == MessageBoxResult.OK)
				{
					item.Delete();
				}
				else
				{
					item.ProjectId = -1;//leave the current project tasks without project
				}
			}

			SterlingService.Current.Database.Delete(this);
			SterlingService.Current.Database.Flush();
		}

		public void MarkAsCompleted()
		{
			this.StatusId = 2;//completed // TODO
			MessageBoxResult mbr = MessageBox.Show("Mark the project tasks as completed aswel?", "Completing project", MessageBoxButton.OKCancel); ;

			// mark tasks as completed
			if (mbr == MessageBoxResult.OK)
			{
				var projectTasksRange = from k in SterlingService.Current.Database.Query<Task, int, bool, int>("Task_ProjectId_IsCompleted")
										where k.Index.Item1 == this.Id
										where k.Index.Item2 == false
										orderby k.Key descending
										select k.LazyValue.Value;

				foreach (Task item in projectTasksRange)
				{
					item.IsCompleted = true;
					item.Save();
				}
			}

			SterlingService.Current.Database.Save(this);
			SterlingService.Current.Database.Flush();
		}

		public void Save()
		{
			SterlingService.Current.Database.Save(this);
			SterlingService.Current.Database.Flush();
		}

		public IEnumerable Tasks
		{
			get
			{
				return from k in SterlingService.Current.Database.Query<Task, int, bool, int>("Task_ProjectId_IsCompleted")
					   where k.Index.Item1 == this.Id
					   //where k.Index.Item2 == false
					   orderby k.Key descending
					   select k;
			}
		}
	}
}
