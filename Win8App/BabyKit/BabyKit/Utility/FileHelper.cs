using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace BabyKit.Utility
{
    class FileHelper
    {
        public static async Task<string> ReadFile(string filename, string folderPath="DataCache", bool isInstallationFolder = false)
        {
            StorageFolder localFolder;
            if(isInstallationFolder)
                localFolder = Windows.ApplicationModel.Package.Current.InstalledLocation;
            else
                localFolder = Windows.Storage.ApplicationData.Current.LocalFolder;
                
            var folder = await localFolder.GetFolderAsync(folderPath);

            //var folder = await installFolder.GetFolderAsync("Assets/Constellation");

            var file = await folder.GetFileAsync(filename);
            var fs = await file.OpenAsync(Windows.Storage.FileAccessMode.Read);
            var inStream = fs.GetInputStreamAt(0);
            Windows.Storage.Streams.DataReader reader = new Windows.Storage.Streams.DataReader(inStream);
            await reader.LoadAsync((uint)fs.Size);
            string data = reader.ReadString((uint)fs.Size);
            reader.DetachStream();
            return data;
        }

        public static async void WriteFile(string filename, string contents)
        {
            var localFolder = Windows.Storage.ApplicationData.Current.LocalFolder;
            var folder = await localFolder.CreateFolderAsync("DataCache", Windows.Storage.CreationCollisionOption.OpenIfExists);
            var file = await folder.CreateFileAsync(filename, Windows.Storage.CreationCollisionOption.ReplaceExisting);
            var fs = await file.OpenAsync(Windows.Storage.FileAccessMode.ReadWrite);
            var outStream = fs.GetOutputStreamAt(0);
            var dataWriter = new Windows.Storage.Streams.DataWriter(outStream);
            dataWriter.WriteString(contents);
            await dataWriter.StoreAsync();
            dataWriter.DetachStream();
            await outStream.FlushAsync();
        }

        private static string SerializeObjectGraph(object graph)
        {
            if (graph == null) return null;
            DataContractJsonSerializer ser = new DataContractJsonSerializer(graph.GetType());
            MemoryStream ms = new MemoryStream();
            ser.WriteObject(ms, graph);
            var bytes = ms.ToArray();
            return UTF8Encoding.UTF8.GetString(bytes, 0, bytes.Length);
        }

        public static async Task<T> LoadData<T>(string filename, string folderPath = "DataCache", bool isInstallationFolder = false)
        {
            var json = await ReadFile(filename, folderPath, isInstallationFolder);
            MemoryStream ms = new MemoryStream(UTF8Encoding.UTF8.GetBytes(json));
            DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(T));
            T result = (T)ser.ReadObject(ms);
            return result;
        }

        public static void SaveData(string filename, object objectGraph, bool overwriteIfNull = true)
        {
            string json = null;
            if (objectGraph != null)
                json = SerializeObjectGraph(objectGraph);
            if (json != null || overwriteIfNull)
            {
                WriteFile(filename, json);
            }
        }
    }
}
