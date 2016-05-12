package com.lind;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by dlin on 3/11/16.
 */
public class HelloRegex {

    private static final String REGEX = "Failed transactions: (?!0).+";
    private static final String INPUT = "Failed transactions: 23";
    private static Pattern pattern;
    private static Matcher matcher;

    public static void Test() {
        pattern = Pattern.compile(REGEX);
        matcher = pattern.matcher(INPUT);

//        System.out.println("Current REGEX is: " + REGEX);
//        System.out.println("Current INPUT is: " + INPUT);
//
//        System.out.println("lookingAt(): " + matcher.lookingAt());
//        System.out.println("matches(): " + matcher.matches());

        if(matcher.matches())
            System.out.println("Pass!");
        else
            System.out.println("Fail!");
    }

}
