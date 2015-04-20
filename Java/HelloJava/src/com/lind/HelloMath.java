package com.lind;

/**
 * Created by lind on 4/18/2015.
 */
public class HelloMath {
    // 如何去小数点前两位，并四舍五入
    public static void Round(){
        double d=1256.22d;
        d=d/100;
        System.out.println(Math.round(d)*100);
    }
}
