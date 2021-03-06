#include "SelfAssemblyMechanisms/include/NetworkFactories/NetworkFactory.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/MLPFactory.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/ElmanFactory.h"
#include "SelfAssemblyMechanisms/include/NetworkFactories/CTRNNFactory.h"

ANNType NetworkFactory::factoryType = ANNType::MLP;
std::vector<unsigned> NetworkFactory::hiddenLayers = std::vector<unsigned>();

std::shared_ptr<NetworkFactory> NetworkFactory::createFactory(int nInputNodes, int nOutputNodes)
{
    switch(NetworkFactory::factoryType){
        case ANNType::MLP: return std::shared_ptr<NetworkFactory>(new MLPFactory(nInputNodes, nOutputNodes));
        case ANNType::Elman: return std::shared_ptr<NetworkFactory>(new ElmanFactory(nInputNodes, nOutputNodes));
        case ANNType::CTRNN: return std::shared_ptr<NetworkFactory>(new CTRNNFactory(nInputNodes, nOutputNodes));
    }
    throw "Invalid factory type";

}