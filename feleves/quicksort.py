from queue import Queue 
import threading
import time
from random import randint as r

size = 10000
maxsize = 500000
array = []

def aux(i,j):
    if i<j:
        pivot = j
        k = 0
        global array 
        while k<pivot:
            if array[k]>array[pivot]:
                temp = array[k]
                l = k+1
                while l<=pivot:
                    array[l-1]=array[l]
                    l+=1
                array[pivot]=temp

                k-=1
                pivot-=1
            else:
                pass
            k+=1
        thread.put([i, pivot-1])
        thread.put([pivot+1, j])
    else:
        pass



def quicksort():
    while  True:
        if thread.empty():
            pass
        else:
            indices = thread.get()
            aux(indices[0],indices[1])
            thread.task_done()




while size<maxsize:
    for i in range(size-10000,size):
        array.insert(i,r(-100,100))
    thread = Queue()
    thread.put([0,size-1])
    start = time.time()
    for i in range (0,15):
        threads = threading.Thread(target = lambda: quicksort())
        threads.daemon = True
        threads.start()
    thread.join()
    print(time.time()-start)
    size=size+10000


