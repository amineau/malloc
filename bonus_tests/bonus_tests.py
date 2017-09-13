#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

import re
import subprocess as cmd
import os
import sys
import shlex
import glob
import shutil


os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

bin_folder = "bin/"
test_bonus = ["stack_logging", "verbose", "scribble", "guard_edges", "multi_thread"]

#############################################################
# functions
def cmd_output(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output.decode("utf-8") , errput.decode("utf-8") 

#############################################################
# compilation

com = "rm -rf " + bin_folder
cmd.call(com.split())
com = "mkdir " + bin_folder
cmd.call(com.split())

dest_dir = "."
files = glob.glob(r'../libft_malloc*')
for file in files:
    shutil.copy(file, dest_dir)

#############################################################
# BONUS
#############################################################

print("##### BONUS Tests #####")

for test in test_bonus:
    print("#####Test " + test)
    test =  "bonus_test_" + test
    com = "gcc -o" + bin_folder + test + " " + test + ".c -L./.. -lft_malloc"
    cmd.call(com.split())
    com = "./" + bin_folder + test
    output = cmd_output(com.split())
    print(output[0])


#############################################################
# decompilation

com = "rm -rf " + bin_folder + " " + " ".join(glob.glob(r'libft_malloc*'))
cmd.call(com.split())
