import subprocess as sp
import time

p = sp.run("ls", capture_output=True)

print(p.stdout)
# process = sp.Popen(["./test"], stdout=sp.PIPE, stderr=sp.PIPE, stdin=sp.PIPE, shell=True)
# AI_col = (process.stdout.readline())
# print(AI_col)
# output = process.communicate(input=b"3\n")
# process.wait
# print("a")
# print(output)