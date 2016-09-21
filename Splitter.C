#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TGraph.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TTreeFormula.h"


class Splitter{
public:
  Splitter();
  ~Splitter();
  void PrepareTrees();
  void SetArraysTo(float* x ,int n,float y);
  void SetArraysTo(int* x ,int n, int y);
  void loop_initialize();
  bool makeNewMEMTree(TString name);
  bool closeCurrentMEMTree();
  

private:
  TString OutputDir;
  TString InName;
  TString OutName;
  TString SplitMode;
  TString Systematic;
  TString MaxEventString;
  int maxEventsPerTree;


  std::vector<TString> CategoryNames;
  std::vector<TString> CategorySelections;

  int nCats=0;
  
  std::vector<TTreeFormula*> CatFormulas;
  
//   TTreeFormula* weightFormula;
  
  TTree* inTree;
  TTree* currentMEMTree;
  TFile* currentMEMFile;
  
 // out variables
long run;
long lumi;
long event;
int systematic; //keep track of systematically variated events
int hypothesis; //MEM hypothesis type (e.g. 0 for SL, 1 for DL etc)
int numcalls; //MEM integration points

int nleps; //varying number of leptons
//the following arrays should be of varying length, with buffer sizes of 2 
float leps_pt[2];
float leps_eta[2];
float leps_phi[2];
float leps_mass[2];
float leps_charge[2];

int njets; //varying number of jets
//the following arrays should be of varying length, with buffer sizes of 10
float jets_pt[10];
float jets_eta[10];
float jets_phi[10];
float jets_mass[10];
float jets_csv[10];
float jets_cmva[10];
int jets_type[10]; //if jet is resolved, boosted

float met_pt;
float met_phi;

// invariables

int Evt_Run;
int Evt_Lumi;
int Evt_ID;

int N_TightElectrons;
int N_TightMuons;

float Muon_E[10];
float Muon_M[10];
float Muon_Pt[10];
float Muon_Eta[10];
float Muon_Phi[10];
float Muon_Charge[10];
float Electron_E[10];
float Electron_M[10];
float Electron_Pt[10];
float Electron_Eta[10];
float Electron_Phi[10];
float Electron_Charge[10];

int N_Jets;

float Jet_E[10];
float Jet_M[10];
float Jet_Pt[10];
float Jet_Eta[10];
float Jet_Phi[10];
float Jet_CMVA[10];
float Jet_CSV[10];

const int maxNJets=10;

float Evt_Pt_MET;
float Evt_Phi_MET;


};

void Splitter::SetArraysTo(int* x, int n, int y){
  for (int i=0; i<n; i++){
    x[i]=y;
  }
}

void Splitter::SetArraysTo(float* x, int n, float y){
  for (int i=0; i<n; i++){
    x[i]=y;
  }
}

bool Splitter::makeNewMEMTree(TString name){
  TString thisoutname=OutputDir+"/Category_"+CategoryNames.at(0)+"/"+name+"_"+Systematic+".root";
  currentMEMFile = new TFile(thisoutname,"RECREATE");
  currentMEMFile->cd();
  currentMEMTree=new TTree("tree","tree");
  currentMEMTree->Branch("run", &run, "run/L");
  currentMEMTree->Branch("event", &event, "event/L");
  currentMEMTree->Branch("lumi", &lumi, "lumi/L");
  currentMEMTree->Branch("nleps", &nleps, "nleps/I");
  currentMEMTree->Branch("njets", &njets, "njets/I");
  currentMEMTree->Branch("hypothesis", &hypothesis, "hypothesis/I");
  currentMEMTree->Branch("numcalls", &numcalls, "numcalls/I");
  currentMEMTree->Branch("systematic", &systematic, "systematic/I");
  currentMEMTree->Branch("met_pt", &met_pt, "met_pt/F");
  currentMEMTree->Branch("met_phi", &met_phi, "met_phi/F");
  currentMEMTree->Branch("leps_pt", leps_pt, "leps_pt[nleps]/F");
  currentMEMTree->Branch("leps_eta", leps_eta, "leps_eta[nleps]/F");
  currentMEMTree->Branch("leps_phi", leps_phi, "leps_phi[nleps]/F");
  currentMEMTree->Branch("leps_mass", leps_mass, "leps_mass[nleps]/F");
  currentMEMTree->Branch("leps_charge", leps_charge, "leps_charge[nleps]/F");
  currentMEMTree->Branch("jets_pt", jets_pt, "jets_pt[njets]/F");
  currentMEMTree->Branch("jets_eta", jets_eta, "jets_eta[njets]/F");
  currentMEMTree->Branch("jets_phi", jets_phi, "jets_phi[njets]/F");
  currentMEMTree->Branch("jets_mass", jets_mass, "jets_mass[njets]/F");
  currentMEMTree->Branch("jets_csv", jets_csv, "jets_csv[njets]/F");
  currentMEMTree->Branch("jets_cmva", jets_cmva, "jets_cmva[njets]/F");
  currentMEMTree->Branch("jets_type", jets_type, "jets_type[njets]/I");
  currentMEMTree->SetAutoFlush();
  std::cout<<"created new tree "<<thisoutname<<" "<<currentMEMTree<<std::endl;
  
  return true;
//   return currentMEMTree;
}

bool Splitter::closeCurrentMEMTree(){
  currentMEMTree->AutoSave();
  currentMEMFile->Close();
  
  return true;
}

void Splitter::loop_initialize(){
   run = 0;
  event = 0;
  lumi = 0;
  nleps = 0;
  njets = 0;
  hypothesis = 0;
  numcalls = 0;
  systematic = 0;
  met_pt = 0;
  met_phi = 0;
  SetArraysTo(leps_pt, 2, 0);
  SetArraysTo(leps_eta, 2, 0);
  SetArraysTo(leps_phi, 2, 0);
  SetArraysTo(leps_mass, 2, 0);
  SetArraysTo(leps_charge, 2, 0);
  SetArraysTo(jets_pt, 10, 0);
  SetArraysTo(jets_eta, 10, 0);
  SetArraysTo(jets_phi, 10, 0);
  SetArraysTo(jets_mass, 10, 0);
  SetArraysTo(jets_csv, 10, 0);
  SetArraysTo(jets_cmva, 10, 0);
  SetArraysTo(jets_type, 10, 0);
  
  Evt_Run=0;
  Evt_Lumi=0;
  Evt_ID=0;
  N_TightElectrons=0;
  N_TightMuons=0;
  N_Jets=0;
  Evt_Phi_MET=0.0;
  Evt_Pt_MET=0.0;
  
    SetArraysTo(Muon_E, 10, 0);
    SetArraysTo(Muon_M, 10, 0);
    SetArraysTo(Muon_Pt, 10, 0);
    SetArraysTo(Muon_Eta, 10, 0);
    SetArraysTo(Muon_Phi, 10, 0);
    SetArraysTo(Muon_Charge, 10, 0);
    SetArraysTo(Electron_E, 10, 0);
    SetArraysTo(Electron_M, 10, 0);
    SetArraysTo(Electron_Pt, 10, 0);
    SetArraysTo(Electron_Eta, 10, 0);
    SetArraysTo(Electron_Phi, 10, 0);
    SetArraysTo(Electron_Charge, 10, 0);
    SetArraysTo(Jet_E, 10, 0);
    SetArraysTo(Jet_M, 10, 0);
    SetArraysTo(Jet_Pt, 10, 0);
    SetArraysTo(Jet_Eta, 10, 0);
    SetArraysTo(Jet_Phi, 10, 0);
    SetArraysTo(Jet_CMVA, 10, 0);
    SetArraysTo(Jet_CSV, 10, 0);

}

Splitter::Splitter(){

  char* configfilename = getenv ("myCONFIGFILE");
  std::cout<<"Reading "<<configfilename<<std::endl;
  std::ifstream config(configfilename);
  std::string dump;
  std::string subdump;
  int posspace1;
  int posspace2;
    bool readline=true;
  int count=0;
  std::cout<<"reading Config"<<std::endl;
  while(readline==true && count<400){
    TString thisCatName;
    TString thisCatSelection;
    count++;
    std::getline(config,dump);
    std::cout<<dump<<std::endl;
    if(dump.find("INNAME")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      InName=subdump;
    }
    if(dump.find("OUTNAME")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      OutName=subdump;
    }
    if(dump.find("OUTDIR")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      OutputDir=subdump;
    }
    if(dump.find("SPLITMODE")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      SplitMode=subdump;
    }
    if(dump.find("SYSTEMATIC")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      Systematic=subdump;
    }
    if(dump.find("MAXEVENTSPERTREE")!=std::string::npos){
      posspace1=dump.find(" ");
      subdump=dump.substr(posspace1+1);
      MaxEventString=subdump;
    }
    if(dump.find("CATEGORY")!=std::string::npos){
      posspace1=dump.find(" ");
      posspace2=dump.find(" ",posspace1+1);
      subdump=dump.substr(posspace1+1,posspace2-posspace1-1);
      std::cout<<posspace1<<" "<<posspace2<<" "<<posspace2-posspace1<<std::endl;
      thisCatName=subdump;
      subdump=dump.substr(posspace2+1);
      thisCatSelection=subdump;
      CategoryNames.push_back(thisCatName);
      CategorySelections.push_back(thisCatSelection);
    }
    
    if(config.eof())readline=false;

  }
  config.close();
  
  maxEventsPerTree=MaxEventString.Atoi();
  std::cout<<std::endl;
  std::cout<<InName<<std::endl;
  std::cout<<OutName<<std::endl;
  std::cout<<OutputDir<<std::endl;
  std::cout<<MaxEventString<<" "<<maxEventsPerTree<<std::endl;
  

  for(int i=0;i<CategoryNames.size();i++){ std::cout<<CategoryNames.at(i)<<" sss "<<CategorySelections.at(i)<<std::endl;}
//   nCats=CategoryNames.size();
  nCats=1;
  
  TFile* inTreeFile=new TFile(InName);
  inTree = (TTree*) inTreeFile->Get("MVATree");
  std::cout<<inTree<<std::endl;
  inTree->SetBranchAddress("Evt_Run",&Evt_Run);
  inTree->SetBranchAddress("Evt_Lumi",&Evt_Lumi);
  inTree->SetBranchAddress("Evt_ID",&Evt_ID);
  inTree->SetBranchAddress("N_TightElectrons",&N_TightElectrons);
  inTree->SetBranchAddress("N_TightMuons",&N_TightMuons);
  inTree->SetBranchAddress("Muon_E",&Muon_E);
  inTree->SetBranchAddress("Muon_M",&Muon_M);
  inTree->SetBranchAddress("Muon_Pt",&Muon_Pt);
  inTree->SetBranchAddress("Muon_Eta",&Muon_Eta);
  inTree->SetBranchAddress("Muon_Phi",&Muon_Phi);
  inTree->SetBranchAddress("Muon_Charge",&Muon_Charge);
  inTree->SetBranchAddress("Electron_E",&Electron_E);
  inTree->SetBranchAddress("Electron_M",&Electron_M);
  inTree->SetBranchAddress("Electron_Pt",&Electron_Pt);
  inTree->SetBranchAddress("Electron_Eta",&Electron_Eta);
  inTree->SetBranchAddress("Electron_Phi",&Electron_Phi);
  inTree->SetBranchAddress("Electron_Charge",&Electron_Charge);
  inTree->SetBranchAddress("N_Jets",&N_Jets);
  inTree->SetBranchAddress("Jet_E",&Jet_E);
  inTree->SetBranchAddress("Jet_M",&Jet_M);
  inTree->SetBranchAddress("Jet_Pt",&Jet_Pt);
  inTree->SetBranchAddress("Jet_Eta",&Jet_Eta);
  inTree->SetBranchAddress("Jet_Phi",&Jet_Phi);
  inTree->SetBranchAddress("Jet_CSV",&Jet_CSV);
//   inTree->SetBranchAddress("Evt_Run",&Jet_CMVA); //DANGERZONE
  inTree->SetBranchAddress("Evt_Pt_MET",&Evt_Pt_MET);
  inTree->SetBranchAddress("Evt_Phi_MET",&Evt_Phi_MET);

  
//   std::cout<<"setting up Categories"<<std::endl;
//   for(int icat=0;icat<nCats;icat++){
//     TString thisoutname=OutputDir+"/Category_"+CategoryNames.at(icat)+"/"+OutName+"_"+Systematic+".root";
//     TFile* thisevenfile = new TFile(thisoutname,"RECREATE");
//     thisevenfile->cd();
// //     TTree* outevenTree = inTree->CloneTree(0);
//     evenTrees.push_back(inTree->CloneTree(0));
//     outfiles.push_back(thisevenfile);
//     evenTrees.back()->SetAutoFlush(1);
// 
//     std::cout<<thisevenfile<<std::endl;
//     std::cout<<evenTrees.back()->GetDirectory()<<" "<<evenTrees.back()->GetCurrentFile()<<std::endl;

//   }
  std::cout<<"done setting up Categories"<<std::endl;
  std::cout<<"setting up Forumulas"<<std::endl;

  // set up cat formulas
    if (CategoryNames.size()!=1){std::cout<<"WARNING WILL ONLY DO THE FIRST CATEGORY"<<std::endl;}

//   for(int icat=0;icat<1;icat++){
    CatFormulas.push_back(new TTreeFormula(CategoryNames.at(0),CategorySelections.at(0),inTree));
//   }
  
//   weightFormula = new TTreeFormula("weightForm","Weight",inTree);
  std::cout<<"done setting up Forumulas"<<std::endl;
  
}

Splitter::~Splitter(){
    
  delete inTree;  
  for(int iform=0; iform<CatFormulas.size();iform++){
    delete CatFormulas.at(iform);
  }
 
}

void Splitter::PrepareTrees(){
  int nEventsTotal=inTree->GetEntries();
  int eventsWritten=0;
  int nTreesWritten=0;
  TString thisname=OutName;
  thisname+="_";
  thisname+=TString::Itoa(nTreesWritten,10);
  makeNewMEMTree(thisname);
  for(long ievt=0; ievt<nEventsTotal; ievt++){
    loop_initialize();
//     useFlavorSplitting=false;
    if(ievt%100==0)std::cout<<"at event "<<ievt<<std::endl;
    if(ievt%100==0)std::cout<<"array cross check "<<Jet_Pt[0]<<" "<<Jet_CSV[1]<<std::endl;
    
    inTree->GetEntry(ievt);
    //only do selected events
    if(CatFormulas.at(0)->EvalInstance()!=0){        
	event=Evt_ID;
	run=Evt_Run;
	lumi=Evt_Lumi;
	met_phi=Evt_Phi_MET;
	met_pt=Evt_Pt_MET;
	nleps=N_TightElectrons+N_TightMuons;
	njets=N_Jets;
	//DANGERZONE
	hypothesis=0;
	if (Systematic=="nominal"){systematic=0;}		 
	else if (Systematic=="JESUP"){systematic=1;}		 
	else if (Systematic=="JESDOWN"){systematic=2;}	 
	else if (Systematic=="JERUP"){systematic=3;}		 
	else if (Systematic=="JERDOWN"){systematic=4;}		 
	else {std::cout<<"unknown systematic "<<std::endl; systematic=5;}
	numcalls=12; //?
	//DANGERZONE
	
	int rightNJets=TMath::Min(N_Jets,maxNJets);
	for(int ijet=0; ijet<rightNJets; ijet++){
	  jets_phi[ijet]=Jet_Phi[ijet];
	  jets_pt[ijet]=Jet_Pt[ijet];
	  jets_eta[ijet]=Jet_Eta[ijet];
	  jets_mass[ijet]=Jet_M[ijet];
	  jets_csv[ijet]=Jet_CSV[ijet];
	  //DANGERZONE
	  jets_cmva[ijet]=0;
	  jets_type[ijet]=0;
	  //get CMVA 
	  // find out what to do with boosted events
	}
	
	//DANGERZONE 
	// only works for SL
	if(N_TightElectrons+N_TightMuons !=1){std::cout<<"WARNING Not an SL event !!!!!!"<<std::endl; }
	for(int ilep=0;ilep<N_TightElectrons;ilep++){
	  leps_charge[ilep]=Electron_Charge[ilep];
	  leps_pt[ilep]=Electron_Pt[ilep];
	  leps_eta[ilep]=Electron_Eta[ilep];
	  leps_phi[ilep]=Electron_Phi[ilep];
	  leps_mass[ilep]=Electron_M[ilep];
	}
	for(int ilep=0;ilep<N_TightMuons;ilep++){
	  leps_charge[ilep]=Muon_Charge[ilep];
	  leps_pt[ilep]=Muon_Pt[ilep];
	  leps_eta[ilep]=Muon_Eta[ilep];
	  leps_phi[ilep]=Muon_Phi[ilep];
	  leps_mass[ilep]=Muon_M[ilep];
	}
	// fill tree
        currentMEMTree->Fill();
        eventsWritten+=1;
    }//end cat eval
    if(eventsWritten==maxEventsPerTree){
      closeCurrentMEMTree();
      nTreesWritten++;
      thisname=OutName;
      thisname+="_";
      thisname+=TString::Itoa(nTreesWritten,10);
      makeNewMEMTree(thisname);
      eventsWritten=0;      
    }
  }//end event loop
  
  std::cout<<"saving Trees"<<std::endl;
  closeCurrentMEMTree();
 
  std::cout<<"done saving Trees"<<std::endl;
}



# ifndef __CINT__
int main()
{
  Splitter mySplitter=Splitter();
  std::cout<<"done constructor"<<std::endl;

  mySplitter.PrepareTrees();
  std::cout<<"done preparing Trees"<<std::endl;

  return 0;
}
# endif


