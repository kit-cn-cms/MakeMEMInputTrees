#set up everything here

# edit
MaxEventsPerTree=999999
# edit
OutputDirectoryForPreparedTrees="/nfs/dust/cms/user/kelmorab/MEMInputTrees80x_newBTags"
# edit
# only the first category is used, select events you want to calc mem for
Categories=[
  ["all","(N_LooseLeptons==1 && N_TightLeptons==1 && N_Jets>=4 && N_BTagsM>=2)"],
]

# better do not touch
SystematicTreeNames=["nominal","JESUP","JESDOWN","JERUP","JERDOWN"]

#edit
MCinputDirectory="/nfs/dust/cms/user/kelmorab/samples8019_newBTags/"

#edit 
# no flavor or even/odd splitting is done
# add additional samples for JES and JER etc.
MCSamples=[
	["ttHbb",["ttHbb/ttHbb*.root"],"None","False",[["foobar",1.025]],[]],
	["ttHnonbb",["ttHnonbb/ttHnonbb*.root"],"None","False",[["foobar",1.025]],[]],
	["ttbar",["ttbar_incl_All/ttbar*.root"],"None","False",[["foobar",1.025]],[]],
	["el_data",["el_data/el_data*.root"],"None","False",[["foobar",1.025]],[]],
	["mu_data",["mu_data/mu_data*.root"],"None","False",[["foobar",1.025]],[]],
	
	#["ttHnonbb",["ttHnonbb/ttHnonbb*nominal*.root"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["ttbar",["ttbar_incl_All/ttbar*nominal*.root"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["SingleT",["st_tchan","stbar_tchan","st_schan","stbar_tWchan","st_tWchan"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["WJets",["Wjets"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["ZJets",["Zjets_m10to50","Zjets_m50toInf"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["QCD",["QCD-HT-700-1000","QCD-HT-500-700","QCD-HT-300-500","QCD-HT-2000-inf","QCD-HT-200-300","QCD-HT-1500-2000","QCD-HT-1000-1500","QCD-HT-100-200"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["DiBoson",["WW","ZZ","WZ"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["ttZ",["ttZ_hadr"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],
	#["ttW",["ttW_lept","ttW_hadr"],"EvenOdd","False",[["lumi",1.025],["pdf",1.03]],[]],

]

# do not touch
DataSamples=[]
DATAinputDirectory=""
