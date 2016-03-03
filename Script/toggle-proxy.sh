#!/bin/bash

e=$(networksetup -getwebproxy wi-fi | grep "No")

if [ -n "$e" ]; then
  echo "Turning on proxy"
  sudo networksetup -setwebproxystate wi-fi on
  sudo networksetup -setsecurewebproxystate wi-fi on
  #sudo networksetup -setstreamingproxystate wi-fi on
  #sudo networksetup -setsocksfirewallproxystate wi-fi on
else
  echo "Turning off proxy"
  sudo networksetup -setwebproxystate wi-fi off
  sudo networksetup -setsecurewebproxystate wi-fi off
  #sudo networksetup -setstreamingproxystate wi-fi off
  #sudo networksetup -setsocksfirewallproxystate wi-fi off
fi
