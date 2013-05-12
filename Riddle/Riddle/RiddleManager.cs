using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using System.Diagnostics;

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

        public void GetRiddles()
        { 
            var req = (HttpWebRequest)WebRequest.Create(RiddleRSS);
            req.BeginGetResponse((callback) =>
            {
                try
                {
                    //Encoding encode = Encoding.GetEncoding("utf-8");
                    Encoding encode = Encoding.GetEncoding("gb2312");
                    var request = callback.AsyncState as HttpWebRequest;
                    var response = request.EndGetResponse(callback) as HttpWebResponse;
                    // while (true)
                    {
                        try
                        {
                            var responseStream = new StreamReader(response.GetResponseStream(), encode);
                            var line = responseStream.ReadToEnd();
                            Debug.WriteLine(line);
                        }
                        catch (IOException ex) { }
                        catch (OutOfMemoryException ex) { }
                    }
                }
                catch (WebException ex) { }
                catch (IOException ex) { }
                catch (OutOfMemoryException ex) { }
                catch (Exception ex) { }
            },req);
        }
    }
}
