
#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsSharedData.h"



int SelfAssemblyMechanismsSharedData::gEvolutionaryGenerationIterations = 100;
int SelfAssemblyMechanismsSharedData::gPopulationSize = 10;
int SelfAssemblyMechanismsSharedData::gMaxGenerations = 10;
int SelfAssemblyMechanismsSharedData::gElitism = 1;
int SelfAssemblyMechanismsSharedData::gCrossover = 1;
double SelfAssemblyMechanismsSharedData::gMutation = 0.05;
int SelfAssemblyMechanismsSharedData::gNHiddenLayers = 0;
std::vector<unsigned> SelfAssemblyMechanismsSharedData::gHiddenLayers = std::vector<unsigned >();
double SelfAssemblyMechanismsSharedData::gTargetFitness = 1.0;
int SelfAssemblyMechanismsSharedData::gNNFactory = 0;
std::string SelfAssemblyMechanismsSharedData::gEAResultsOutputFilename;
std::string SelfAssemblyMechanismsSharedData::gGenomeFileName;
bool SelfAssemblyMechanismsSharedData::gDisplayBestGenome;

