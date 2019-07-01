#convertps.py
#this script takes the output of the MONDO-phenoseries file produced by phenol and
#makes a file of the form
#MONDOid:entrez1,entrez2,...
#where the entrez's are the entrez gene ids of the relevant diseases

from collections import defaultdict
import sys


phenoseries_fname = "../phenoseries.txt"
mim2gene_fname = "../mim2gene_medgen"

mondoDict = defaultdict(list)
pheno2gene = defaultdict(list)

with open(phenoseries_fname) as f:
    for line in f:
        fields = line.rstrip('\n').split('\t')
        mondo = fields[0]
        omim  = fields[2]
        if omim.startswith("OMIM:"):
            omim = omim[5:]
        #print(mondo,' ',omim)
        mondoDict[mondo].append(omim)

#for item in mondoDict:#
#    print(item)#
#    for x in mondoDict[item]:
#        print ("\t",x)

with open(mim2gene_fname) as f:
    for line in f:
        #print(line)
        fields = line.split('\t')
        omim = fields[0]
        entrez = fields[1]
        type = fields[2]
        if type != 'phenotype':
            continue
        pheno2gene[omim].append(entrez)

print("MONDO2OMIM")

for item in mondoDict:
    sys.stdout.write(item)
    for x in mondoDict[item]:
        #print ("x",x)
        if x in pheno2gene:
            for y in pheno2gene[x]:
                if y == "-":
                    continue
                sys.stdout.write("\t{}".format(y))
    print()
