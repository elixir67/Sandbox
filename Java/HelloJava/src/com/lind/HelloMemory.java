package com.lind;

import org.junit.Test;

/**
 * Created by dlin on 10/24/15.
 */
public class HelloMemory {

    @Test
    public void OutputMaxMemory(){
        long max = Runtime.getRuntime().maxMemory();


        System.out.format("Max memory is: %d MB %n", max / (1024 * 1024));
    }

}
