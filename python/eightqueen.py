#coding:utf-8
n = 3

def walk(row, column, result):
    for x in row:
        row.remove(x)
        for y in column:
            column.remove(y)
            result.append((x,y))
            walk(row, column, result)
            column.append(y)
        row.append(x)
        
def main():
    row = range(0,n)
    column = range(0,n)
    # result =[]
    # walk(row, column, result)
    # print result
    # print len(result)
    
main()    