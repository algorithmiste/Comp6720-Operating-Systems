'''
author: Casey Carr

OS homework 4 task2 

'''
import matplotlib.pyplot as plt
import numpy as np
import random
import time

# time based LRU
# the same as task 1
def time_based_LRU_algorithm(ref_str, number_of_frame):
    number_of_page_fault = 0

    page_frame = [None] * number_of_frame
    counter_list = [0] * number_of_frame

    counter = time.time()

    for d in range(len(ref_str)):

        counter = time.time()

        if ref_str[d] in page_frame:

            index = page_frame.index(ref_str[d])

            counter_list[index] = counter

            continue

        if None in page_frame:

            index = page_frame.index(None)

            page_frame[index] = ref_str[d]

            counter_list[index] = counter

            number_of_page_fault += 1

        else:
            index = counter_list.index(min(counter_list))

            page_frame[index] = ref_str[d]

            counter_list[index] = counter

            number_of_page_fault += 1

    return number_of_page_fault
# the same as task 1 

# the stack based LRU
# if the page referred, put to the top of stack
# if the page need to replace, remove the bottom page 
def stack_based_LRU_algorithm(ref_str, number_of_frame):
    number_of_page_fault = 0

    page_frame = [None] * number_of_frame

    stack = []

    for d in range(len(ref_str)):

        if ref_str[d] in page_frame:    # if the page in the frame, move it to the top 

            stack.remove(ref_str[d])    
            stack.append(ref_str[d])

            continue
        # if the page not in the frame
        if None in page_frame:         # if the page has space 

            index = page_frame.index(None)  # add it to frame

            page_frame[index] = ref_str[d]

            stack.append(ref_str[d])

            number_of_page_fault += 1

        else:                           # if the frame has no space

            stack.append(ref_str[d])    # add to the top of stack

            temp = stack.pop(0)      # pop the bottom page

            index = page_frame.index(temp)  # replace it with the new one in the frame

            page_frame[index] = ref_str[d]

            number_of_page_fault += 1



    return number_of_page_fault




def main():
    ref_str = []
    # size 500 string, each number is  from 0 - 20
    for i in range(500):
        ref_str.append(random.randint(0, 21))

    #frame size from 1 - 10
    number_of_frame = [x for x in range(1, 11)]

    # record the time for each algo
    runtime_for_time_LRU = []
    runtime_for_stack_LRU = []

    #  add the runtime for each algo
    for i in number_of_frame:
        start = time.time()
        time_based_LRU_algorithm(ref_str,i)
        end = time.time()
        runtime_for_time_LRU.append((end-start))

    for i in number_of_frame: 
        start = time.time()
        stack_based_LRU_algorithm(ref_str,i)
        end = time.time()
        runtime_for_stack_LRU.append((end-start))


    # make a graph for two line
    plt.subplot()
    plt.plot(runtime_for_time_LRU, color = 'b', label="Timer-base")
    plt.plot(runtime_for_stack_LRU, color = 'g',label="Stack-base")
    plt.xlabel('Number of Frames')
    plt.ylabel('Running time')
    plt.xticks(np.arange(0, 11, 1))
    plt.legend()
    plt.show()



main()
