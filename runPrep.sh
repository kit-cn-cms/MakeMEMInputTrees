qsub -l h=bird* -hard -l os=sld6 -l h_vmem=2000M -l s_vmem=2000M -cwd -S /bin/bash -o /nfs/dust/cms/user/kelmorab/MEMProd/MakeMEMInputTrees//logs/\$JOB_NAME.o\$JOB_ID -e /nfs/dust/cms/user/kelmorab/MEMProd/MakeMEMInputTrees//logs/\$JOB_NAME.e\$JOB_ID -q 'default.q' PreparationScripts/Tranche3_ttbar_DL_984.sh
