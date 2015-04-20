package com.lind;

import java.util.Random;

/**
 * Created by lind on 4/20/2015.
 */
public class HelloSort {
     public static void Test()
     {
         Random ran = new Random();
         final int MaxNum = 5;
//         int a[] = new int[MaxNum];
//         for(int i = 0; i < MaxNum; ++i )
//             a[i] = ran.nextInt(10);
         int a[] = {6,5,1,4,5};
         System.out.print("Before sort is:");
         for(int i: a)
             System.out.print(i + " ");
         System.out.println();
         //BubbleSort(a);
         //SelectSort(a);
         QuickSort(a, 0, a.length);
         System.out.print("After sort is:");
         for(int i: a)
             System.out.print(i + " ");
     }

     public static void BubbleSort(int[] a)
     {
         // two next values compare and makes the first big number into the last one
         // then return to the next round
         for(int i = 0; i < a.length; ++i)
             for(int j = 1; j < a.length - i; ++j)
             {
                 if(a[j-1] > a[j])
                 {
                     int temp = a[j-1];
                     a[j-1] = a[j];
                     a[j] = temp;
                 }
             }
     }

    public static void SelectSort(int[] a)
    {
        int len = a.length;
        // Find the max number each round and swap it once each round
        for(int i = 0; i < len; ++i) {
            // Find the max number index
            int maxPos = 0, j = 0;
            for (; j < len - i; ++j) {
                if (a[j] > a[maxPos])
                    maxPos = j;
            }
            // End this round, swap the max number to the end
            int temp = a[j-1];
            a[j-1] = a[maxPos];
            a[maxPos] = temp;
        }
    }

    public static void QuickSort(int[] a, int start, int end)
    {
        int len = end - start;
        if(len == 0 || len == 1)
            return;

        int keyIndex = start;
        for(int i = start + 1; i < end; ++i)
        {
            if(a[i] < a[keyIndex])
            {
                int temp = a[keyIndex];
                a[keyIndex] = a[i];
                a[i] = temp;
                keyIndex = i;
            }
        }
        QuickSort(a, start, keyIndex-1);
        QuickSort(a, keyIndex+1, end);
    }
}
