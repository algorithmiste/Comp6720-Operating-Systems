'''
import the required libraries
date 
os
regular expression 
path
'''
import datetime as date
import os
import re
from pathlib import Path

home = str(Path.home())     #get the home path as string
def main():
    f1 = open("1.txt", "a+")    # create a file that records the input
    old_path = os.getcwd()      # old_path to save the old direction #os.getcwd() is to get the dir
    while True:
        current_path = os.getcwd()             #current_path to store the current dir.
        cmd = input(current_path+"> ").strip() # cmd is the input string, input() the input method strip() is trim the string with space
        currentDT = date.datetime.now()        # get the current time now
        list = re.split('\s+',cmd)             # use regular expression to split input with space into a list
        if (list[0] == ""):                    # nothing input, next loop
            continue
        if (list[0] == "stat"):                # input == 'stat' 
            f1.close()                         # close the file that records the input
            try:
                f2 = open("1.txt", "r")        # open the record file with read mode 
                print(f2.read())               # print the file with all the content
            except Exception:                  # exception handling
                print("File not found")        # no file error, print error message
            f1 = open("1.txt", "a+")           # open the file again with append mode for next loop
        elif(list[0] == "exit"):               # the input == 'exit'
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n") # write the file with current time and input command 
            exit(0)                            # exit the program with status 0
        elif(list[0] == "cd"):                 # if the input == cd
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n")                
            if (len(list) == 1 ):              # if no argument -- only cd command 
                old_path = current_path        # current path become the old path
                os.chdir(home)                 # os.chdir() change the dir to HOME path

            elif (list[1] == "."):             # if the arg is .
                old_path = current_path        # stay current path and make the old path = the current path

            elif (list[1] == ".."):            # if the arg is ..
                old_path = current_path        # current path become the old path
                os.chdir("..")                 # the dir change to upper level one, and parameter .. move up

            elif(list[1] == "-"):              # if the arg is -
                temp_path = os.getcwd()        # use temp path to save the current path
                os.chdir(old_path)             # change the dir to old path 
                old_path = temp_path           # and the old path swaps to current path
            else:                              # if the arg with a folder
                try:
                    old_path = current_path    
                    os.chdir(r""+current_path+"/"+list[1]) # change dir to the path+folder 
                except FileNotFoundError:                  # error handling with no file
                    os.chdir(r""+home+list[1].strip('~'))  # try with home path + dir
                except Exception:
                    print("No such file or directory!")    # print error message 
                    continue

        elif (cmd != ""):                      # if the cmd is others but not empty
            newpid = os.fork()                  # fork creates a child process 
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n")   # record the command                     
            if newpid == 0:                     # if the new process id is 0
                action = list[0]                # the action command is the first element of list
                list.pop(0)                     # pop the first element out 
                list.insert(0, " ")             # and change it as empty string in the front of list 
                f1.write(currentDT.strftime("%H:%M") + "\t" + cmd + "\n") # write the file with current time and input command 
                try:                            
                    env = {"PATH": "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"} # let the env as a dictionary path is key and value is all possible location of the program
                    os.execvpe(action,list,env) # execvpe is exec() in python and action is the program name, list is the list of arguments, env is the path 
                    os._exit(0)                 # the child process quit 
                except PermissionError:         # no permission error 
                    print("You dont have permission to access the command!")
                    os._exit(0)
                except FileNotFoundError:       # no file found error
                    print("FileNotFoundError")
                    os._exit(0)
                except Exception:               # other error
                    print("Error!")
                    os._exit(0)
            elif newpid < 0:                    # if the pid < 0, error
                print("error")
            else:
                os.wait()                       # the parent process is waiting





main()
