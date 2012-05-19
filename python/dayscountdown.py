#coding:utf-8

from datetime import date

MONTH = 5
DAY = 25

today = date.today()
birthday = date(today.year, MONTH, DAY)
if birthday < today:
    birthday = birthday.replace(year = today.year + 1)
time_to_birthday = abs(birthday - today)
print time_to_birthday.days

print birthday.isoweekday()
