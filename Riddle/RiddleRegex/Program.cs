using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace RiddleRegex
{
    class Program
    {
        public static string ParseRiddleHTMLContent(string linkText)
        {
            var answer = string.Empty;
            // <strong>谜底</strong>：喜从天降</p>
            // <strong>谜底：</strong>肥皂</p>
            // <strong>谜底：</strong>峠[qiǎ]<span style="display: none">&nbsp;</span></p>
            string ANSWER_PATTERN_1 = @"<strong>谜底</strong>：(.+?)<";
            string ANSWER_PATTERN_2 = @"<strong>谜底：</strong>(.+?)<";
            answer = RegexQuery(linkText, ANSWER_PATTERN_1);
            if (string.IsNullOrWhiteSpace(answer))
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

        static void test1()
        { 
            string testStr = "<strong>谜底：</strong>斑林狸<span style=\"display: none\">&nbsp;</span></p>";
            Console.WriteLine(ParseRiddleHTMLContent(testStr));
        }

        static void Main(string[] args)
        {
            test1();
        }
    }
}
