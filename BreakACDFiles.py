import sys
import os

def main(argv):
#    for p in argv:
#        print p

    if len(argv) != 2:
        print "Error: Input requires a source and destination path: > python BreakACDFiles.py FilesToProcess/ Output/"
	return
    #print "processing input directory"
    processDirectory(argv[0], argv[1])
    

def processDirectory(i, o):
    srcList = []
    if os.path.exists(i) and os.path.exists(o):
	for dirname, dirnames, filenames in os.walk(i):
	    for fname in filenames:
       	        srcList.append(os.path.join(dirname,fname))
	
	fileCount = len(srcList)
	print "Number of files to Process: %d" % fileCount
      	for s in srcList:
    	    processTheFile(s,o)
	
    else:
        print "Error: One or more of the paths provided do not exist."

    
def processTheFile(s,o):
    aCnt, cCnt, dCnt, tot = 0, 0, 0, 0
    aTmp, cTmp, DTmp = "", "", ""
    spt = []

    spt = s.rsplit("/",1)
    aTmp = o + "A_" + spt[1]
    cTmp = o + "C_" + spt[1]
    dTmp = o + "D_" + spt[1]        

    try:
	print "Opening: %s" % s
        inputfile = open(s,"r")
 	outputfileA = open(aTmp,"a")
	outputfileC = open(cTmp,"a")
	outputfileD = open(dTmp,"a")
        
	for line in inputfile:
	    if line[0] == "A":	
		outputfileA.write(line)
		aCnt += 1
    	    elif line[0] == "C":
		outputfileC.write(line)
  		cCnt += 1
	    elif line[0] == "D":
		outputfileD.write(line)
  		dCnt += 1
	
	print "A's Processed: %d" % aCnt
	print "C's Processed: %d" % cCnt
	print "D's Processed: %d" % dCnt
	print "Total Records Processed: %d" % (aCnt + cCnt + dCnt)

    finally:
	if inputfile:
	    #print "Closing: %s" % s
	    inputfile.close()
	if outputfileA:
	    #print "Closing: %s" % aTmp
	    outputfileA.close()
	if outputfileC:
	    #print "Closing: %s" % aTmp
	    outputfileC.close()
	if outputfileD:
	    #print "Closing: %s" % dTmp
	    outputfileD.close()

if __name__ == "__main__":
    main(sys.argv[1:])
