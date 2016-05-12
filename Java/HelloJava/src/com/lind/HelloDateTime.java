package com.lind;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

/**
 * Created by lind on 4/21/2015.
 */
public class HelloDateTime {
    public static void Test() {
        String testDate = "2015-04-21";
//        HelloSimpleDateFormat(testDate);
//        ParseStringToDate(testDate);
        YesterdayCurrent();
    }

    private static void YesterdayCurrent() {
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, -1);
        System.out.println(cal.getTime());
    }


    private static void HelloSimpleDateFormat(String testDate) {
        SimpleDateFormat sdt = new SimpleDateFormat("yyyy-MM-dd");
        try {
            // String to DateTime
            Date dt = sdt.parse(testDate);
            System.out.println(dt.toString());
            // DateTime to String
            System.out.println(sdt.format(dt));

            // Get year, month, day
            Calendar cl = Calendar.getInstance();
            cl.setTime(dt);

            // month started from 0, so don't forget +1 to get moth
            int year = cl.get(cl.YEAR);
            int month = cl.get(cl.MONTH) + 1;
            int day = cl.get(cl.DAY_OF_MONTH);

            System.out.println(year + "-" + month + "-" + day);

            // month started from 0, so don't forget -1 to set month
            cl.set(year, month - 1, day);
            dt = cl.getTime();
            System.out.println(sdt.format(dt));
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    public static void ParseStringToDate(String ds) {
        String splitdate[] = ds.split("-");
        if (splitdate.length == 3) {
            int year = Integer.parseInt(splitdate[0]);
            int month = Integer.parseInt(splitdate[1]);
            int day = Integer.parseInt(splitdate[2]);
            Calendar cl = Calendar.getInstance(Locale.CHINA);
            cl.set(year, month - 1, day);
            Date dt = cl.getTime();
            System.out.println(dt.toString());
        }
    }
}
