#set up everything here

# edit
MaxEventsPerTree=999999
# edit
OutputDirectoryForPreparedTrees="/nfs/dust/cms/user/kelmorab/MEMInputTrees80x_ICHEP_V5dl"
# edit
# only the first category is used, select events you want to calc mem for
Categories=[
  ["all","(N_LooseLeptons==1 && N_TightLeptons==1 && N_Jets>=4 && N_BTagsM>=2)"],
]

# better do not touch
SystematicTreeNames=["nominal","JESUP","JESDOWN","JERUP","JERDOWN"]

#edit
MCinputDirectory="/nfs/dust/cms/user/kelmorab/samples8019_ICHEP_V5DL/"

#edit 
# no flavor or even/odd splitting is done
# add additional samples for JES and JER etc.
MCSamples=[
	#["ttHbb",["ttHbb/ttHbb*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttHnonbb",["ttHnonbb/ttHnonbb*.root"],"None","False",[["foobar",1.025]],[]],
	#["Tranche3_ttHbb",["Tranche3_ttHbb/Tranche3_ttHbb*.root"],"None","False",[["foobar",1.025]],[]],
	#["Tranche3_ttHnonbb",["Tranche3_ttHnonbb/Tranche3_ttHnonbb*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttbar_incl_All",["ttbar_incl_All/ttbar*.root"],"None","False",[["foobar",1.025]],[]],
	
	#["ttbar_SL",["ttbar_SL/ttbar_SL*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleDown_ttbar_SL",["scaleDown_ttbar_SL/scaleDown_ttbar_SL*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleDown_ttbar_incl",["scaleDown_ttbar_incl/scaleDown_ttbar_incl*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleUp_ttbar_SL",["scaleUp_ttbar_SL/scaleUp_ttbar_SL*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleUp_ttbar_incl",["scaleUp_ttbar_incl/scaleUp_ttbar_incl*.root"],"None","False",[["foobar",1.025]],[]],
	#["stbar_s-channel",["stbar_s-channel/stbar_s-channel*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttW_JetToLNu",["ttW_JetToLNu/ttWJetToLNu*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttW_JetToQQ",["ttW_JetToQQ/ttWJetToQQ*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttZ_ToQQ",["ttZ_ToQQ/ttZToQQ*.root"],"None","False",[["foobar",1.025]],[]],
	#["Zjets_m50toInf",["Zjets_m50toInf/Zjet_m50toInf*.root"],"None","False",[["foobar",1.025]],[]],
	
	#["WW",["WW/WW*.root"],"None","False",[["foobar",1.025]],[]],
	#["WZ",["WZ/WZ*.root"],"None","False",[["foobar",1.025]],[]],
	#["ZZ",["ZZ/ZZ*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-800-1200",["WJets-HT-800-1200/WJets-HT-800-1200*.root"],"None","False",[["foobar",1.025]],[]],
	#["el_data",["el_data/el_data*.root"],"None","False",[["foobar",1.025]],[]],
	#["mu_data",["mu_data/mu_data*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-600-800",["WJets-HT-600-800/WJets-HT-600-800*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-400-600",["WJets-HT-400-600/WJets-HT-400-600*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-2500-Inf",["WJets-HT-2500-Inf/WJets-HT-2500-Inf*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-1200-2500",["WJets-HT-1200-2500/WJets-HT-1200-2500*.root"],"None","False",[["foobar",1.025]],[]],
	#["WJets-HT-100-200",["WJets-HT-100-200/WJets-HT-100-200*.root"],"None","False",[["foobar",1.025]],[]],
	#["st_tchan",["st_tchan/st_tchan*.root"],"None","False",[["foobar",1.025]],[]],
	#["stbar_tchan",["stbar_tchan/stbar_tchan*.root"],"None","False",[["foobar",1.025]],[]],
	#["st_tWchan",["st_tWchan/st_tWchan*.root"],"None","False",[["foobar",1.025]],[]],
	#["stbar_tWchan",["stbar_tWchan/stbar_tWchan*.root"],"None","False",[["foobar",1.025]],[]],
	
	["Tranche3_ttbar_DL",["Tranche3_ttbar_DL/Tranche3_ttbar_DL*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleDown_ttbar_DL",["scaleDown_ttbar_DL/scaleDown_ttbar_DL*.root"],"None","False",[["foobar",1.025]],[]],
	#["scaleUp_ttbar_DL",["scaleUp_ttbar_DL/scaleUp_ttbar_DL*.root"],"None","False",[["foobar",1.025]],[]],
	#["ttbar_DL",["ttbar_DL/ttbar_DL*.root"],"None","False",[["foobar",1.025]],[]],

]

# do not touch
DataSamples=[]
DATAinputDirectory=""
