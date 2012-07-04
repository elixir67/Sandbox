#coding:utf-8

#Call WindowAPI to lock computer
import ctypes;

dll = ctypes.WinDLL('user32.dll');
dll.LockWorkStation();
