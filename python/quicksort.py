#coding:utf-8

def qsort(l):
    def quicksort(l, left, right):
        if left < right:
            #get first number p from left end
            pivot, j, tmp = left, left + 1, l[left]
            #move elements<p to the left side
            #move elements>=p to the right side
            while j<= right:
                if l[j] < tmp:
                    pivot=pivot+1
                    l[pivot],l[j]=l[j],l[pivot]
                j=j+1
            l[left],l[pivot] = l[pivot],l[left]
            quicksort(l, left, pivot - 1)
            quicksort(l, pivot + 1, right)
    quicksort(l, 0, len(l) - 1)
    
l = [3,4,7,1,6,0,2,8,5,9]    
print l
qsort(l)
print l

