#!/usr/bin/python

import sys
import os
from subprocess import call

I_COORD_SIZE = 210.0;
J_COORD_SIZE = 260.0;

def usage():
    print "Usage: generate-hex-tile-quad-a4.py -i SHEET_I_COORD -j SHEET_J_COORD";
    sys.exit(0);

#Get command line arguments
if len(sys.argv) <= 1:
    usage();
icoord = -1;
jcoord = -1;
c = 1;
while c < len(sys.argv):
    if sys.argv[c] == "--help" or sys.argv[c] == "-h":
        usage();
    elif sys.argv[c] == "-i":
        c += 1;
        if c < len(sys.argv):
            icoord = int(float(sys.argv[c]));
    elif sys.argv[c] == "-j":
        c += 1;
        if c < len(sys.argv):
            jcoord = int(float(sys.argv[c]));
    else:
        print "Invalid argument: " + sys.argv[c]
        usage();
    c += 1;

if icoord < 0:
    print "i coordinate not given or not a positive integer."
    usage();
if jcoord < 0:
    print "j coordinate not given or not a positive integer."
    usage();

print "Generating quad hex tile A4 sheet at i, j = " + str(icoord) + ", " + str(jcoord) + " ...";

call("cp hex-tile-quad-a4.svg _temp-unlabeled.svg", shell=True)
call("sed -e \"s/SHEET_I_J/" + str(icoord) + "," + str(jcoord) +  "/g\" _temp-unlabeled.svg > _temp-labeled.svg", shell=True)
call("rm _temp-unlabeled.svg", shell=True)
call("inkscape _temp-labeled.svg --export-pdf=_temp-labeled.pdf", shell=True)
call("rm _temp-labeled.svg", shell=True)
call("libdots-pdf-overlayer --thick -i _temp-labeled.pdf -o hex-tile-quad-a4-" + str(icoord) + "-" + str(jcoord) + ".pdf --xmm " + str(icoord*I_COORD_SIZE) + " --ymm " + str(jcoord*J_COORD_SIZE), shell=True)
call("rm _temp-labeled.pdf", shell=True)
