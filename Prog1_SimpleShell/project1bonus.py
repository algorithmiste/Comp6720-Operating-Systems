'''
some of comment is on the first program
these comment will be the extra part 
'''
import datetime as date
import os
import re
from pathlib import Path
import subprocess

home = str(Path.home())

def main():
    f1 = open("1.txt", "a+")

    old_path = os.getcwd()

    while True:
        current_path = os.getcwd()

        cmd = input(current_path+"> ").strip()

        currentDT = date.datetime.now()

        list = re.split('\s+',cmd)
        list2 = re.split('\s+',cmd)
        if (list[0] == ""):
            continue
        if (list[0] == "stat"):
            f1.close()
            try:
                f2 = open("1.txt", "r")
                print(f2.read())
            except Exception:
                print("File not found")
            f1 = open("1.txt", "a+")

        elif(list[0] == "exit"):
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n")
            exit(0)

        elif(list[0] == "cd"):
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n") 
            if (len(list) == 1 ):
                old_path = current_path
                os.chdir(home)

            elif (list[1] == "."):
                old_path = current_path

            elif (list[1] == ".."):
                old_path = current_path
                os.chdir("..")

            elif(list[1] == "-"):
                temp_path = os.getcwd()
                os.chdir(old_path)
                old_path = temp_path
            else:
                try:
                    old_path = current_path
                    os.chdir(r""+current_path+"/"+list[1])
                except FileNotFoundError:
                    os.chdir(r""+home+list[1].strip('~'))
                except Exception:
                    print("No such file or directory!")
                    continue

        elif (cmd != ""):
            f1.write(currentDT.strftime("%H:%M")+"\t"+cmd+"\n") 
            newpid = os.fork()
            if newpid == 0:
                action = list[0]
                list.pop(0)
                list.insert(0, " ")
                f1.write(currentDT.strftime("%H:%M") + "\t" + cmd + "\n")
                if (list.__contains__(">")):            # if the list contain > 

                    index = cmd.index(">")              # find the index of ">" in the string 
                    first_cmd = re.split('\s+', cmd[:index].strip())    # split the cmd before > 
                    second_cmd = re.split('\s+', cmd[index+1:].strip()) # and after > by space

                    str = second_cmd[0] # the second part the first element is the file name 
                    file_ = open(str, "w+") # create a file as write mode with the file name 
                    p = subprocess.Popen(  first_cmd ,stdout=file_) # Popen is open a program, first argument is the list of cmd and stdout is the output of the program and write it to file
                    os._exit(0)           # quit the child process 
                elif (list.__contains__("<")) :         # if the cmd has "<"
                    try:
                        temp = list[list.index("<") + 1]    # get the file name after the "<"
                        list.remove("<")                    # remove the "<" in the list 
                        list[-1] = current_path+"/"+temp    # add the path on the file name
                        env = {"PATH": "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"}
                        os.execvpe(action, list, env)   # pass the action and the list of arguments and path to execvpe
                        os._exit(0)
                    except Exception:
                        print("No file Error")
                        os._exit(0)
                elif (list.__contains__("|")):         # if the cmd has "|"
                    index = cmd.index("|")              # find the index of "|"
                    first_cmd = re.split('\s+', cmd[:index].strip()) #split the cmd as two parts, first part is the command before "|"
                    second_cmd = re.split('\s+', cmd[index+1:].strip()) # the other part is after "|"
                    op1 = subprocess.Popen(first_cmd,   # open the program with the fist part command and pass the program output to PIPE to save it temporary 
                                                stdout=subprocess.PIPE)
                    op2 = subprocess.Popen(second_cmd,                      # open the second program and use the first output as input. 
                                                 stdin=op1.stdout,
                                                 stdout=subprocess.PIPE)
                    print(op2.communicate()[0].strip()) # print the second program output and communicate() returns a tuple with (output and error), use the [0] as output
                    os._exit(0) # quit the child process
                else:
                    try:
                        env = {"PATH": "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"}
                        os.execvpe(action,list,env)
                        os._exit(0)
                    except PermissionError:
                        print("You dont have permission to access the command!")
                        os._exit(0)
                    except FileNotFoundError:
                        print("FileNotFoundError")
                        os._exit(0)
                    except Exception:
                        print("Error!")
                        os._exit(0)
            elif newpid < 0:
                print("error")
            else:
                os.wait()





main()
