# MakeMEMInputTrees
MakeMEMInputTrees

Script for creating the input trees for MEM production
see 
https://github.com/cms-ttH/CommonClassifier/blob/master/README.md    

1)    
Edit Definitions.py
python OnlyPrepareTrees.py

Too fine Splitting complicates things    
Set MaxEventsPerTree to 999999 !!!!!
Some things still need to be done    
grep DANGERZONE Splitter.C

2) 
Hadd output trees for samples_Syst   

3) 
Put the stuff on dcache if you want to use crab     
PATH=$PATH:/afs/desy.de/group/it/services/dcache/bin     
dcmkdir and dcput  can be used for this    
DANGERZONE
dcmkdir /pnfs/desy.de/cms/tier2/store/user/$USER/MEMProd_ttHbb_test     
dcput ttHbb_nominal.root /pnfs/desy.de/cms/tier2/store/user/$USER/MEMProd_ttHbb_test/ttHbb_nominal.root   


4) Run mem      
Check out the CommonClassifier repository     
copy and edit splitsample.py
This will create sample list for the specified input files. It will say which are the first and last events for each MEM job.
copy and edit multicrab.py     
then e.g.     
python karim_multicrab.py -out T2_DE_DESY --tag ttHbbMEMtest    
This will create crab jobs for the sample. For each package of 200 events a separate job, but they can run over the same input file.
