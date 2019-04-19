from os import system 
from random import randint 

MAX_VAL = 1000000
MAX_N = 1000000 
COMPILE = True
PROGRAM_NAME = "solution"

class Test:
    def generate(self,MAX_N,MAX_VAL):
        self.n = randint(1,MAX_N)
        self.tab = [randint(1,MAX_VAL) for _ in range(self.n)]
    def __init__(self):
        self.tab = []
        self.n = 0

def printTestToFile(name, test):
    programInput = open(name,"w")
    programInput.write(str(test.n))
    programInput.write("\n")
    programInput.write(" ".join([str(x) for x in test.tab]))
    programInput.write("\n")
    programInput.close()

def readResultFromFile(name):
    programResult = open(name,"r")
    r = programResult.read()
    programResult.close()
    return r

def checkResult(r,test):
    return [int(x) for x in r.split()]==sorted(test.tab)

if __name__=="__main__":
    if COMPILE:
        system("g++ -static -O2 -o "+PROGRAM_NAME+" "+PROGRAM_NAME+".cpp")
    i = 1
    while True:
        test = Test()
        test.generate(MAX_N,MAX_VAL)
        printTestToFile("test.in",test)
        system("./"+PROGRAM_NAME+" < test.in > test.out")
        result = readResultFromFile("test.out")
        if checkResult(result,test):
            print("OK: ",i)
        else:
            print("FAILED")
            break
        i+=1
