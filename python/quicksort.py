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

#use list comprehension to do quicksort
def q_sort(l):
    if len(l)<=1:
        return l
    else:
        #get first number p from l
        p=l[0]
        #move elements<p in l-{p} to the left side
        small_part=[x for x in l[1:] if x<p]
        #move elements>=p in l-{p} to the right side
        big_part=[x for x in l[1:] if x>=p]
        #recursively quicksort left and right part and combine them together
        return q_sort(small_part)+[p]+q_sort(big_part)
        
#use if else to simplify it        
def q_sort_simplify(l):
    return l if len(l)<=1 else q_sort([x for x in l[1:] if x<l[0]])+[l[0]]+q_sort([x for x in l[1:] if x>=l[0]])        

#use lambda to simplify it  
q_sort_lamda= lambda l: l if len(l)<=1 else q_sort([x for x in l[1:] if x<l[0]])+[l[0]]+q_sort([x for x in l[1:] if x>=l[0]])  

    
l = [3,4,7,1,6,0,2,8,5,9]    
print l
print q_sort_lamda(l)
