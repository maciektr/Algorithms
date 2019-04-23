from os import system
from enum import Enum, auto
from random import randint,choice 
from sortedcollections import SortedList

MAX_VAL = 1000000
MIN_VAL = -1000000
MAX_N = 10000
MIN_N = 1
COMPILE = False
PROGRAM_NAME = "solution"

class OperationType(Enum):
    insert_new = auto()
    insert_old = auto()
    find_new = auto()
    find_old = auto()
    print_all = auto()
    remove = auto()
    def random():
        i = choice(list(OperationType))
        while i==OperationType.print_all:
            i = choice(list(OperationType))
        return i

class Test:
    def randomValue():
        return randint(MIN_VAL,MAX_VAL)

    def symbol(x):
        if x==OperationType.insert_new or x==OperationType.insert_old:
            return 'i'
        if x==OperationType.find_new or x==OperationType.find_old:
            return 'f'
        if x==OperationType.print_all:
            return 'p'
        if x==OperationType.remove:
            return 'r'

    def __init__(self):
        self.operations = []
    
    def generate(self):
        self.operations = []
        val = Test.randomValue() 
        self.inside = [val]
        self.operations.append({'type':OperationType.insert_new, 'value':val})
        self.n = randint(MIN_N,MAX_N)
        for _ in range(self.n-1):
            t = OperationType.random() if len(self.inside) > 0 else OperationType.insert_new
            val = Test.randomValue() if t==OperationType.insert_new or t==OperationType.find_new else choice(self.inside)
            self.operations.append({'type':t,'value':val})
            if t==OperationType.insert_new:
                self.inside.append(val)
            elif t==OperationType.remove:
                self.inside.remove(val)

    def print(self):
        print(self.n)
        for i in self.operations:
            print(Test.symbol(i['type']),i['value'] if i['type']!=OperationType.print_all else '')
    
    def printToFile(self, filename):
        f = open(filename,'w')
        f.write(str(self.n))
        f.write('\n')
        for i in self.operations:
            f.write(Test.symbol(i['type']))
            f.write(' '+str(i['value'] if i['type']!=OperationType.print_all else ''))  
            f.write('\n')

    def resolveToFile(self,filename):
        f = open(filename,'w')
        inside = []
        for i in self.operations:
            if i['type']==OperationType.insert_new or i['type']==OperationType.insert_old:
                inside.append(i['value'])
            elif i['type']==OperationType.find_new or i['type']==OperationType.find_old:
                f.write(str(i['value']) if i['value'] in inside else 'None')
                f.write('\n')
            elif i['type']==OperationType.print_all:
                f.write(' '.join([str(x) for x in sorted(inside)]))
                f.write('\n')
            elif i['type']==OperationType.remove:
                inside.remove(i['value'])

def main():
    i=1
    if COMPILE:
        system("gcc -static -O2 -o "+PROGRAM_NAME+" "+PROGRAM_NAME+".c")
    while True:
        test = Test()
        test.generate()
        test.printToFile('t.in')
        test.resolveToFile('t.out')
        system('./'+PROGRAM_NAME+' < t.in > s.out')
        if system('diff -wq t.out s.out'):
            print("Failed")
            break
        else:
            print("OK ",i)
        i+=1

if __name__=='__main__':
    main()
