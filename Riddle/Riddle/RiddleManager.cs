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
using System.ComponentModel;
using Windows.Web.Syndication;
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

        private string _answer;
        public string Answer
        {
            get { return _answer; }
            set 
            {
                _answer = value; 
                RaisePropertyChanged("Answer"); 
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void RaisePropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }
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

        public static async Task<List<RiddleItem>> GetFeedAsync()
        {
            string feedUriString = RiddleRSS;
            Windows.Web.Syndication.SyndicationClient client = new SyndicationClient();
            Uri feedUri = new Uri(feedUriString);

            try
            {
                SyndicationFeed feed = await client.RetrieveFeedAsync(feedUri);

                // This code is executed after RetrieveFeedAsync returns the SyndicationFeed.
                // Process the feed and copy the data you want into the FeedData and FeedItem classes.
                //FeedData feedData = new FeedData();
                List<RiddleItem> riddles = new List<RiddleItem>();

                //if (feed.Title != null && feed.Title.Text != null)
                //{
                //    feedData.Title = feed.Title.Text;
                //}
                //if (feed.Subtitle != null && feed.Subtitle.Text != null)
                //{
                //    feedData.Description = feed.Subtitle.Text;
                //}
                if (feed.Items != null && feed.Items.Count > 0)
                {
                    // Use the date of the latest post as the last updated date.
                    //feedData.PubDate = feed.Items[0].PublishedDate.DateTime;

                    foreach (SyndicationItem item in feed.Items)
                    {
                        RiddleItem feedItem = new RiddleItem();
                        if (item.Title != null && item.Title.Text != null)
                        {
                            feedItem.Title = item.Title.Text;
                        }
                        if (item.PublishedDate != null)
                        {
                            feedItem.PubDate = item.PublishedDate.DateTime.ToString();
                        }
                        if (item.Authors != null && item.Authors.Count > 0)
                        {
                            feedItem.Category = item.Categories[0].Label.ToString();
                        }
                        // Handle the differences between RSS and Atom feeds.
                        if (feed.SourceFormat == SyndicationFormat.Atom10)
                        {
                            //if (item.Content != null && item.Content.Text != null)
                            //{
                            //    feedItem.Content = item.Content.Text;
                            //}
                            if (item.Id != null)
                            {
                                feedItem.Link = new Uri(item.Id).ToString();
                            }
                        }
                        else if (feed.SourceFormat == SyndicationFormat.Rss20)
                        {
                            //if (item.Summary != null && item.Summary.Text != null)
                            //{
                            //    feedItem.Content = item.Summary.Text;
                            //}
                            if (item.Links != null && item.Links.Count > 0)
                            {
                                feedItem.Link = item.Links[0].Uri.ToString();
                            }
                        }
                        riddles.Add(feedItem);
                    }
                }
                return riddles;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                return null;
            }
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
            foreach (var riddle in riddles)
            {
                riddle.Answer = await FetchAnswer(riddle.Link);
            }

            // Parallel.ForEach(riddles, async (riddle) => { riddle.Answer = await FetchAnswer(riddle.Link); });

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
            // <strong>谜底：</strong>肥皂</p>
            // <strong>谜底：</strong>峠[qiǎ]<span style="display: none">&nbsp;</span></p>
            string ANSWER_PATTERN_1 = @"<strong>谜底</strong>：(.+?)<"; // Add ? for non-greedy match
            string ANSWER_PATTERN_2 = @"<strong>谜底：</strong>(.+?)<";
            answer = RegexQuery(linkText, ANSWER_PATTERN_1);
            if(string.IsNullOrWhiteSpace(answer))
                answer = RegexQuery(linkText, ANSWER_PATTERN_2);
            return answer;
        }

        private static string RegexQuery(string linkText, string pattern)
        {
            var answer = string.Empty;
            Regex rgx = new Regex(pattern, RegexOptions.IgnoreCase);
            Match match = rgx.Match(linkText);
            if (match.Success)
            {
                answer = match.Groups[1].Value;
                Debug.WriteLine(answer);
            }
            return answer;
        }
    }
}
