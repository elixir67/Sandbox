using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using System.Reflection;

namespace Riddle
{
    public class CsvExport<T> where T : class
    {
        public IList<T> Objects;

        public CsvExport(IList<T> objects)
        {
            Objects = objects;
        }

        public string Export()
        {
            return Export(true);
        }

        public string Export(bool includeHeaderLine)
        {

            var sb = new StringBuilder();

            //Get properties using reflection. 
            var propertyInfos = typeof(T).GetTypeInfo();

            if (includeHeaderLine)
            {
                //add header line. 
                foreach (var propertyInfo in propertyInfos.DeclaredProperties)
                {
                    sb.Append(propertyInfo.Name).Append(System.Globalization.CultureInfo.CurrentCulture.TextInfo.ListSeparator);
                }
                sb.Remove(sb.Length - 1, 1).AppendLine();
            }

            //add value for each property. 
            foreach (T obj in Objects)
            {
                foreach (var propertyInfo in propertyInfos.DeclaredProperties)
                {
                    sb.Append(MakeValueCsvFriendly(propertyInfo.GetValue(obj, null))).Append(System.Globalization.CultureInfo.CurrentCulture.TextInfo.ListSeparator);
                }
                sb.Remove(sb.Length - 1, 1).AppendLine();
            }

            return sb.ToString();
        }

        //export to a file. 
        public async void ExportToFile(string path)
        {
            var storageFolder = KnownFolders.DocumentsLibrary;
            var file = await storageFolder.CreateFileAsync(path, CreationCollisionOption.OpenIfExists);
            string content = Export();

            // Add BOM flag in the beginning of the file to output CSV correctly
            // http://www.haogongju.net/art/1778905
            byte[] buffer = System.Text.Encoding.UTF8.GetBytes(content); 
            byte[] outBuffer = new byte[buffer.Length + 3]; 
            outBuffer[0] = (byte)0xEF; outBuffer[1] = (byte)0xBB; outBuffer[2] = (byte)0xBF; Array.Copy(buffer, 0, outBuffer, 3, buffer.Length);

            await FileIO.WriteBytesAsync(file, outBuffer);
        }

        //export as binary data. 
        public byte[] ExportToBytes()
        {
            return Encoding.UTF8.GetBytes(Export());
        }

        //get the csv value for field. 
        private string MakeValueCsvFriendly(object value)
        {
            if (value == null) return "";

            if (value is DateTime)
            {
                if (((DateTime)value).TimeOfDay.TotalSeconds == 0)
                    return ((DateTime)value).ToString("yyyy-MM-dd");
                return ((DateTime)value).ToString("yyyy-MM-dd HH:mm:ss");
            }
            string output = value.ToString();

            if (output.Contains(",") || output.Contains("\""))
                output = '"' + output.Replace("\"", "\"\"") + '"';

            return output;

        }
    }
}
