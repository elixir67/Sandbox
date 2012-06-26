using System;
using System.Collections.Generic;
using TelerikToDo;
using Wintellect.Sterling.Database;

namespace TelerikToDo
{
	public class ToDoDatabase : BaseDatabaseInstance
	{
		/// <summary>
		///     The name of the database instance
		/// </summary>
		public override string Name
		{
			get { return "ToDo Database"; }
		}

		/// <summary>
		///     Method called from the constructor to register tables
		/// </summary>
		/// <returns>The list of tables for the database</returns>
		protected override List<ITableDefinition> _RegisterTables()
		{
			return new List<ITableDefinition>
                       {
							CreateTableDefinition<Project, int>(fg => fg.Id)
						       .WithIndex<Project, int, int>("Project_Status", fg => fg.StatusId)
							   .WithIndex<Project, string, int>("Project_Name", fg => fg.Name),
							CreateTableDefinition<Task, int>(fg => fg.Id)
						       .WithIndex<Task, DateTime, bool, int>("Task_DueDate_IsCompleted", task => Tuple.Create(task.DueDate.HasValue ? task.DueDate.Value : DateTime.MaxValue, task.IsCompleted))
							   .WithIndex<Task, int, bool, int>("Task_ProjectId_IsCompleted", task => Tuple.Create(task.ProjectId, task.IsCompleted))
							   .WithIndex<Task, int, int>("Task_CategoryId", task => task.CategoryId),
							CreateTableDefinition<TaskCategory, int>(fg => fg.Id)
                       };
		}
	}
}