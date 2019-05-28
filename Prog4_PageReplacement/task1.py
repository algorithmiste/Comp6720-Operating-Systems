'''
author: Casey Carr

OS homework 4 task1 

'''
import matplotlib.pyplot as plt
import numpy as np
import random
import time

# get the distance for next reference
# if it will not refer in the future 
# it will assign a infinity
def get_distance(rest_str, ref):
    if ref in rest_str:
        return rest_str.index(ref)
    else:
        return float("inf")

# the Optimal page algo
# it will replace the longest page not use in the future

def optimal_page_replacement(ref_str, number_of_frame):

    number_of_page_fault = 0

    page_frame = [None] * number_of_frame # nothing in the frame in the beginning

    for d in range(len(ref_str)):
        if ref_str[d] in page_frame:    # if the refer page in frame, skip it.
            continue

        if None in page_frame:          # if the frame has space, put it in and add 1 fault
            page_frame[page_frame.index(None)] = ref_str[d]
            number_of_page_fault += 1

        else:                           # no space in frame, it need to be replaced
            rest_str = ref_str[d+1:]    # get the distance for each page in frame, replace the max one and add 1 fault
            m = {x: get_distance(rest_str, x) for x in page_frame}
            m = sorted(m, key=m.__getitem__)
            m = list(m)
            page_frame[page_frame.index(m[-1])] = ref_str[d]
            number_of_page_fault += 1

    return number_of_page_fault

# it is a time based LRU algo
# it will replace the one has no use for the longest time

def LRU_algorithm(ref_str, number_of_frame):
    number_of_page_fault = 0

    page_frame = [None] * number_of_frame
    counter_list = [0] * number_of_frame # a counter to record the time of page reference

    counter = time.time()   

    for d in range(len(ref_str)):

        counter = time.time()   # record the time when page referred

        if ref_str[d] in page_frame:    # already in the page, only update the time

            index = page_frame.index(ref_str[d])

            counter_list[index] = counter

            continue

        if None in page_frame:  # frame has space, add the page and update its time

            index = page_frame.index(None)

            page_frame[index] = ref_str[d]

            counter_list[index] = counter

            number_of_page_fault += 1

        else:   # frame no space, need to replace the oldest page in the frame 
            index = counter_list.index(min(counter_list)) # pick the oldest one

            page_frame[index] = ref_str[d]  # change to new page

            counter_list[index] = counter   # update the counter

            number_of_page_fault += 1       # add 1 fault

    return number_of_page_fault


def main():
    ref_str = []
    for i in range(10): # size 10 string
        ref_str.append(random.randint(0, 10)) # char is 0 - 9

    number_of_frame = [x for x in range(1, 8)]  # number of frame from 1 to 8

    list_optimal_page_replacement = []  # record the fault for each algo in 1 - 8 frames
    list_LRU_algorithm = []

    #add the fault number in to each list
    for i in number_of_frame:
        list_optimal_page_replacement.append(
            optimal_page_replacement(ref_str, i))
        list_LRU_algorithm.append(LRU_algorithm(ref_str, i))

    # make a bar graph for each list
    fig, ax = plt.subplots()

    index = np.arange(7)

    rects1 = plt.bar(index, list_LRU_algorithm, 0.35,
                     alpha=0.8,
                     color='b',
                     label='LRU')

    rects2 = plt.bar(index + 0.35, list_optimal_page_replacement, 0.35,
                     alpha=0.8,
                     color='g',
                     label='OPT')

    plt.xlabel('Number of Frames')
    plt.ylabel('Number of page faults')
    
    plt.xticks(index + 0.35/2, number_of_frame)
    plt.legend()
    plt.show()

main()
