#!/usr/bin/python
import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, filename,stdinput,intarr):
        if filename == "stdi":
            self.lines = stdinput
        elif filename == "lowhigh":
            self.lines = intarr
        else:
            self.lines = [line.rstrip('\n') for line in open(filename)]
            arr=[]
            for i in self.lines:
                arr.append(str(i) + "\n")

            self.lines = arr
           # f = open(filename, 'r')
           # self.lines = f.readlines()
            #print(self.lines)
           # f.close()

    def chooseline(self):
        return random.choice(self.lines)
    
    def chooseliner(self):
        line1 = random.choice(self.lines)
        self.lines.remove(line1)
       # print(self.lines)
        return line1
def main():
    global count
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE
  or:  shuf -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input.

Mandatory arguments to long options are mandatory for short options too."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="count",default=None,
                      help="output at most COUNT lines")
    parser.add_option("-i", "--input-range",
                      action="store", dest="LOHI", default=None,
                      help="treat each number LO through HI as an input line")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False,
                      help="output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])
    temp = []
    stdinput = []
    linecount = 0
    fileinput = []
    if options.count:   
        try:
            count = int(options.count)
        except:
            parser.error("invalid line count: '{}'".
                         format(options.count))
            # inputfile = "broken"    
        if count < 0:
            parser.error("invalid line count: '{}'".
                         format(options.count))
            
       # inputfile = "broken" 
    try:
        inputfile = args[0]
    except:
        inputfile = "broken"
    if options.LOHI:
        inputfile="lowhigh"
        try:
            numbers = options.LOHI.split("-")
            p1 = int(numbers[0])
            p2 = int(numbers[1])
            linecount = p2 - p1 + 1 
        except:
            parser.error("Invalid Input Range: '{}'".
                         format(options.LOHI))
        if p2 < p1:
            parser.error("Invalid Input Range: '{}'".
                         format(options.LOHI))    
        if len(args) > 0:
            parser.error("extra operand '{}'".
                         format(args[0]))
        for i in range(p1,p2+1):
            temp.append(str(i) + "\n")       
    elif len(args) == 0 :
        stdinput  = sys.stdin.readlines()
        for i in stdinput:
            linecount += 1
        inputfile = "stdi"
    elif len(args) == 1 and args[0] == "-":
        stdinput  = sys.stdin.readlines()
        for i in stdinput:
            linecount += 1
        inputfile = "stdi"
    elif len(args) > 1:
        parser.error("extra operand '{}'".
                     format(args[1]))
        
    if len(args) == 1 and not options.LOHI and args[0] != "-":
        try:
            file1 = open(args[0])
            fileinput = file1.readlines()
            for i in fileinput:
                linecount+=1
            file1.close()
        except:
            parser.error("{} : No such file or directory".
                         format(args[0]))
            
    if options.count:
        if count >= linecount and not options.repeat:
            count = linecount
    if not options.count and not options.repeat:
        count = linecount
    if options.repeat and  not options.count:
        count = 1
    
    try:
        generator = shuf(inputfile,stdinput,temp)
        i = 0
        #print ("count is {}".format(count))
        while i < count :
            if options.repeat:
                sys.stdout.write(generator.chooseline())
            else:
                sys.stdout.write(generator.chooseliner())
            i += 1
            if options.repeat and not options.count:
                i -= 1
            
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".format(errno, strerror))

if __name__ == "__main__":
    main()
