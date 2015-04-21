package com.lind;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Calendar;

/**
 * Created by lind on 4/21/2015.
 */
public class HelloDateTime {
    public static void Test()
    {
        SimpleDateFormat sdt = new SimpleDateFormat("yyyy-MM-dd");
        try {
            // String to DateTime
            Date dt = sdt.parse("2015-04-21");
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
            cl.set(year, month-1, day);
            dt = cl.getTime();
            System.out.println(sdt.format(dt));
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }
}
