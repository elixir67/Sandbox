using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using System.Diagnostics;
using System.Xml.Linq;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.Data.Xml.Dom;
//using System.Xml.Linq;

namespace Riddle
{
    struct RiddleItem
    {
        public string Title { get; set; }
        public string PubDate { get; set; }
        public string Link { get; set; }
        public string Category { get; set; }
    }

    class RiddleManager
    {
        const string RiddleRSS = "http://www.xhxsw88.cn/data/rss/80.xml"; 

        public XDocument GetRiddleRssContents()
        { 
            string content = string.Empty;
            var req = (HttpWebRequest)WebRequest.Create(RiddleRSS);
            req.BeginGetResponse((callback) =>
            {
                try
                {
                    Encoding encode = Encoding.GetEncoding("gb2312");
                    var request = callback.AsyncState as HttpWebRequest;
                    var response = request.EndGetResponse(callback) as HttpWebResponse;
                    try
                    {
                        var responseStream = new StreamReader(response.GetResponseStream(), encode);
                        content = responseStream.ReadToEnd();
                        Debug.WriteLine(content);

                    }
                    catch (IOException ex) { }
                    catch (OutOfMemoryException ex) { }

                }
                catch (WebException ex) { }
                catch (IOException ex) { }
                catch (OutOfMemoryException ex) { }
                catch (Exception ex) { }
            },req);
            return string.IsNullOrWhiteSpace(content) ? null :XDocument.Parse(content);
        }

        public static async Task<XDocument> LoadXml()
        {
            StorageFolder storageFolder = await Package.Current.InstalledLocation.GetFolderAsync("Test");
            StorageFile storageFile = await storageFolder.GetFileAsync("TestRss.xml");

            XmlLoadSettings loadSettings = new XmlLoadSettings();
            loadSettings.ProhibitDtd = false;
            loadSettings.ResolveExternals = false;
                
            XmlDocument xmlDoc = await XmlDocument.LoadFromFileAsync(storageFile, loadSettings);
            XDocument doc = XDocument.Parse(xmlDoc.GetXml());
            var rtnTask = Task.Factory.StartNew(() => doc);
            return await rtnTask;
        }

        public static async Task<List<RiddleItem>> ParseRiddles(XDocument doc)
        {
            var result = doc.Descendants("channel").Elements("item")
                         .Select(item => new RiddleItem
                         {
                             Title = item.Element("title").Value,
                             Link = item.Element("link").Value,
                             PubDate = item.Element("pubDate").Value,
                             Category = item.Element("category").Value
                         });
            var rtnTask = Task.Factory.StartNew(() => result.ToList());
            return await rtnTask;
        }
    }
}
