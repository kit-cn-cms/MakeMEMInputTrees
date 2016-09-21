# MakeMEMInputTrees
MakeMEMInputTrees

Script for creating the input trees for MEM production
see 
https://github.com/cms-ttH/CommonClassifier/blob/master/README.md    

1)    
Edit Definitions.py
python OnlyPrepareTrees.py

Some things still need to be done    
grep DANGERZONE Splitter.C

2)     
Rename output files e.g.
ttHbb_11_182_nominal.root ->  ttHbb_11_182_nominal.root___0___200    
where 0 and 200 are the first and last event in this case    
Splitting might not be actually necessary :(

3) 
Put the stuff on dcache if you want to use crab     
PATH=$PATH:/afs/desy.de/group/it/services/dcache/bin     
dcmkdir and dcput  can be used for this
DANGERZONE
dcmkdir /pnfs/desy.de/cms/tier2/store/user/$USER/MEMProd_ttHbb_test     
for i in `ls *`; do dcput -v "$i" /pnfs/desy.de/cms/tier2/store/user/$USER/MEMProd_ttHbb_test/"$i"; done


4)
create sample list e.g.     
for i in `ls *`; do echo root://xrootd-cms.infn.it///store/user/kelmorab/MEMProd_ttHbb_test/"$i" >> samplelist.txt ; done 

5) Run mem      
Check out the CommonClassifier repository     
put in the sample list     
copy and edit multicrab.py     
then e.g.     
python karim_multicrab.py -out T2_DE_DESY --tag ttHbbMEMtest
