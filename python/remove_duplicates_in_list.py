def remove_duplicates(list):
    if(list):
        list.sort()
        last = list[-1]
        for i in range(len(list)-2, -1, -1):
            if last == list[i]:
                del list[i]
            else:
                last = list[i]

l = [5,3,2,2,6,4,4,1]
remove_duplicates(l)
print l
