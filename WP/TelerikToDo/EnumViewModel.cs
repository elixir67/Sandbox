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
using System.Collections;
using System.ComponentModel;
using System.Reflection;
using System.Linq;

namespace TelerikToDo
{
	public class EnumViewModel
	{
		private Type enumType;

		public IEnumerable Values
		{
			get;
			private set;
		}

		[TypeConverter(typeof(TypeTypeConverter))]
		public Type EnumType
		{
			get
			{
				return this.enumType;
			}
			set
			{
				this.enumType = value;
				this.InitValues();
			}
		}

		private void InitValues()
		{
			this.Values = this.EnumType.GetFields(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Static)
							.Select<FieldInfo, object>((FieldInfo x) => x.GetValue(this.EnumType));
		}
	}

	public class TypeTypeConverter : TypeConverter
	{
		public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
		{
			return sourceType.IsAssignableFrom(typeof(string));
		}

		public override object ConvertFrom(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
		{
			Type t = Type.GetType((string)value, false);
			return t;
		}

		private Type GetTypeFromAssembly(string typeName, Type knownType)
		{
			string assemblyName = knownType.AssemblyQualifiedName;
			return Type.GetType(assemblyName.Replace(knownType.FullName, typeName), false);
		}
	}
}
