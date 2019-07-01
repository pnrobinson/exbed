#convertps.py
#this script takes the output of the MONDO-phenoseries file produced by phenol and
#makes a file of the form
#MONDOid:entrez1,entrez2,...
#where the entrez's are the entrez gene ids of the relevant diseases

from collections import defaultdict
import sys
import argparse

# initiate the parser
text = 'This script converts the output of phenol to the input format of exbed.'
parser = argparse.ArgumentParser(description = text)
parser.add_argument("-p","--phenoseries",help="phenoseries file, output of phenol")
parser.add_argument("-m","--medgen",help="path to mim2gene_medgen file")
parser.add_argument("-o","--out",help="name of output file")
args = parser.parse_args()

if args.phenoseries:
    phenoseries_fname = args.phenoseries
else:
    print("[ERROR] -p/--phenoseries option required")
    exit(1)
if args.medgen:
    mim2gene_fname = args.medgen
else:
    print("[ERROR] -m/--medgen option required")
    exit(1)
if args.out:
    outfile_name = args.out
else:
    outfile_name = 'ps2gene.txt'

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

with open(outfile_name,'w') as fh:
    for item in mondoDict:
        sys.stdout.write(item)
        fh.write(item)
        for x in mondoDict[item]:
            if x in pheno2gene:
                for y in pheno2gene[x]:
                    if y == "-":
                        continue
                    sys.stdout.write("\t{}".format(y))
                    fh.write("\t{}".format(y))
        sys.stdout.write('\n')
        fh.write('\n')

print("Done, we wrote the transformed data to ",outfile_name)
