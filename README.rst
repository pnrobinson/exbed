#####
exbed
#####


Analyze embedded vectors

Phenoseries
~~~~~~~~~~~

To get the information about the p[henoseries, run the develp version of phenol (1.4./0-SNAPSHOT)
the phenol-cli (Main.java) with the following parameters. ::

  mondo --mondo /path/to/mondo.obo --outfile mondo2ps.txt

The name/path of the outfile is arbitrary but will be needed as input for this
this app.

We then need to transform this file into the input format needed by this
program (we transform the OMIM disease ids to Entrez Gene ids).

To do so, use the script in the scripts directory. ::
  
  $ python convertps.py -p mondo2ps.txt -m mim2gene_medgen


Embedded vector data
~~~~~~~~~~~~~~~~~~~~

We also require the output file with the embedded vectors from hn2v. In this example,
I have named those vectors ``p1q1gamma1.txt``.

Running exbed
~~~~~~~~~~~~~

To build the app, running ``make`` should suffice. Then run the app as. ::

  ./exbed p1q1gamma1.txt phenoseries.txt


# Purpose
