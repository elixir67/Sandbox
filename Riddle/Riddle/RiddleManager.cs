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
using System.Net.Http;
using System.Text.RegularExpressions;
//using System.Xml.Linq;

namespace Riddle
{
    // Make it as class, so it can be modified in foreach
    class RiddleItem
    {
        public string Title { get; set; }
        public string PubDate { get; set; }
        public string Link { get; set; }
        public string Category { get; set; }
        public string Answer { get; set; }
    }

    class RiddleManager
    {
        const string RiddleRSS = "http://www.xhxsw88.cn/data/rss/80.xml"; 

        public static async Task<XDocument> GetRiddleRssContents()
        {
            string riddleRss = await GetReponseTextFromURL(RiddleRSS);
            XDocument doc = string.IsNullOrEmpty(riddleRss) ? null : XDocument.Parse(riddleRss);
            var rtnTask = Task.Factory.StartNew(() => doc);
            return await rtnTask;
        }

        public static async Task<string> GetReponseTextFromURL(string url)
        {
            string responseBody = string.Empty;
            try
            {
                HttpClient client = new HttpClient();
                
                HttpResponseMessage response = await client.GetAsync(url);
                response.EnsureSuccessStatusCode();
                // Do not ReadAsString directly because the string is not encoded correctly
                // responseBody = await response.Content.ReadAsStringAsync();
                Encoding encode = Encoding.GetEncoding("gb2312");
                var responseStream = await response.Content.ReadAsStreamAsync();
                var encodedStream = new StreamReader(responseStream, encode);
                responseBody = encodedStream.ReadToEnd();
            }
            catch (HttpRequestException e)
            {
                Debug.WriteLine("Message:{0}", e.Message);
            }
            var rtnTask = Task.Factory.StartNew(() => responseBody);
            return await rtnTask;
        }

        // Stub function for testing
        public static async Task<XDocument> LoadTestRssXml()
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

        public static async Task<string> LoadTestRiddleLink()
        {
            StorageFolder storageFolder = await Package.Current.InstalledLocation.GetFolderAsync("Test");
            StorageFile storageFile = await storageFolder.GetFileAsync("TestRiddleLink.html");

            string content = string.Empty;
            using(StreamReader reader = new StreamReader(await storageFile.OpenStreamForReadAsync(),Encoding.GetEncoding("gb2312")))
            {
                content = await reader.ReadToEndAsync();
            }
            
            var rtnTask = Task.Factory.StartNew(() => content);
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

        internal static async Task<bool> FetchAnswers(List<RiddleItem> riddles)
        {
            //riddles.ForEach(riddle => FetchAnswer(riddle));
            foreach (var riddle in riddles)
            {
                riddle.Answer = await FetchAnswer(riddle.Link);
            }

            var result = true;
            var rtnTask = Task.Factory.StartNew(() => result);
            return await rtnTask;
        }

        private async static Task<string> FetchAnswer(string link)
        {
            string linkText = await GetReponseTextFromURL(link);

            var answer = ParseRiddleHTMLContent(linkText);

            var rtnTask = Task.Factory.StartNew(() => answer);
            return await rtnTask;
        }

        public static string ParseRiddleHTMLContent(string linkText)
        {
            var answer = string.Empty;
            // <strong>谜底</strong>：喜从天降</p>
            string ANSWER_PATTERN = @"<strong>谜底</strong>：(.+)</p>";
            Regex rgx = new Regex(ANSWER_PATTERN, RegexOptions.IgnoreCase);
            Match match = rgx.Match(linkText);
            if (match.Success)
            {

                //Console.WriteLine("{0} ({1} matches):", input, matches.Count);
                answer = match.Groups[1].Value;
                Debug.WriteLine(answer);
            }
            return answer;
        }
    }
}
