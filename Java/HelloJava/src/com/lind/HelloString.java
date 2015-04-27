package com.lind;
import java.net.URLEncoder;
import java.util.*;

/**
 * Created by lind on 4/18/2015.
 */
public class HelloString {
    public static void Test() {
//        HelloString.URLEncodeAmpersands();
//        HelloString.ReverseCharactersOfString();
//        HelloString.ReverseWordsOfString();
//        HelloString.TextWrapping();
        int i = StringToInt("123");
        System.out.println(i);

        i = StringToInt("-123");
        System.out.println(i);

        i = StringToInt("0");
        System.out.println(i);

        i = StringToInt("-1230");
        System.out.println(i);


        // i = StringToInt("");
        String s = IntToString(321);
        System.out.println(s);

        s = IntToString(-321);
        System.out.println(s);

        s = IntToString(0);
        System.out.println(s);

        s = IntToString(120);
        System.out.println(s);

        s = IntToString(-120);
        System.out.println(s);

        System.out.println(Reverse("I am a student."));
    }

    public static int StringToInt(String s) throws IllegalArgumentException {
        if(s == null || s.isEmpty())
            throw new IllegalArgumentException();

        boolean isNegative = false;
        int i = 0;
        switch(s.charAt(0)){
            case '+':
                isNegative = false;
                ++i;
                break;
            case '-':
                isNegative = true;
                ++i;
            default:
                break;
        }
        int num = 0;
        for(; i < s.length(); ++i)
        {
            int digital = s.charAt(i) - '0';
            if(digital >= 0 && digital < 9 )
                num = num * 10 + digital;
            else
                throw new IllegalArgumentException();
        }
        return num*(isNegative? -1: 1);
    }

    public static String IntToString(int i){
        StringBuilder s = new StringBuilder();
        if(i == 0)
            return "0";
        boolean isNegative = i < 0? true: false;
        i = Math.abs(i);
        while(i != 0){
            int digital = i%10;
            i = i/10;
            s.insert(0,digital);
        }
        if(isNegative)
            s.insert(0, '-');
        return s.toString();
    }

    public static String Reverse(String s){
//        Use String Builder
//        int len = s.length();
//        StringBuilder sb = new StringBuilder(len);
//        for(int i = len - 1; i >=0; --i)
//            sb.append(s.charAt(i));
//        return sb.toString();

        // Use the raw chars array
        char[] chars = s.toCharArray();
        int start = 0;
        int end = s.length() - 1;
        while(start < end)
        {
           char temp = chars[start];
            chars[start] = chars[end];
            chars[end] = temp;
            ++start;
            --end;
        }
        return new String(chars);
    }

    public static String ReverseWordsInSentence(String s)
    {
        if(s == null || s.isEmpty())
            return "";

        StringBuilder r = new StringBuilder(s);
        r.reverse();

       return "UnImplementedYet";
    }

    public static void TextWrapping() {
        // Way One
        StringBuilder builder = new StringBuilder();
        String words = "The quick brown fox jumps over the lazy dog. ";

        for (int i = 0; i < 10; i++)
        {
            builder.append(words);
        }

        String toWrap = builder.toString();
        int width = 76;
        while (toWrap!=null && toWrap.length()>0)
        {
            String first = toWrap.length() > width ? toWrap.substring(0, width+1) : toWrap;
            toWrap = (!toWrap.equals(first)) ? toWrap.substring(width + 1).trim() : null;
            System.out.println("> " + first);
        }
        // Way Two, WordUtils cannot be found
//        String prefix = "> "; String input = "The quick brown fox jumps over the lazy dog.";
//
//        String[] lines = WordUtils.wrap(StringUtils.repeat(input, 10), 72 - prefix.length()).split("\n");
//
//        for (String line : lines) System.out.printf("%s%s\n", prefix, line);
    }

    public static void ReverseWordsOfString() {
        String text = "This is an end, my only friend!";
        // Way One
        List list = new ArrayList();
        StringTokenizer st = new StringTokenizer(text, " ")  ;
        while(st.hasMoreTokens()) {
            list.add(0, st.nextToken());
        }
        StringBuilder sb = new StringBuilder();
        for(Iterator it = list.iterator(); it.hasNext();)
        {
            String word = (String)it.next();
            sb.append(word);
            if(it.hasNext())
                sb.append(" ");
        }
        String reversed1 = sb.toString();
        System.out.println(reversed1);
        // Way Two
        List<String> ls = Arrays.asList(text.split("\\s"));
        Collections.reverse(ls);
        sb = new StringBuilder(32);
        for(String s: ls)
            sb.append(" ").append(s);
        String reverse2 = sb.toString().trim();
        System.out.println(reverse2);
    }

    public static void URLEncodeAmpersands() {
        Map<String, String> params = new HashMap<String, String>();
        params.put("mode", "view");
        params.put("fname", "Ron & Jean");
        params.put("lname", "Smith");

        StringBuilder buffer = new StringBuilder();
        try {
            for (Map.Entry<String, String> entry : params.entrySet()) {
                buffer.append(URLEncoder.encode(entry.getKey(), "UTF-8"))
                        .append("=")
                        .append(URLEncoder.encode(entry.getValue(), "UTF-8"));
            }
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
        }

        System.out.println(buffer.toString());
    }

    public static void ReverseCharactersOfString(){
        String reverse = new StringBuffer("reverse me").reverse().toString();
        System.out.println(reverse);

        reverse = new StringBuilder("reverse me").reverse().toString();
        System.out.println(reverse);

        //reverse = StringUtils.re("reverse me");
    }

}
