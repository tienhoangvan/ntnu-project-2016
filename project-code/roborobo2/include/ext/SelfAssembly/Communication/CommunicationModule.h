#ifndef ROBOROBO2_COMMUNICATIONMODULE_H
#define ROBOROBO2_COMMUNICATIONMODULE_H

#include <vector>
#include <initializer_list>
#include <iostream>
struct RobotMessage{
    private:
        std::vector<double> message;
    private:
    public:
    RobotMessage(){};

    RobotMessage(std::vector<double> contents){
            message = contents;
        };

    const std::vector<double>& get() const{
        return message;
    }

    RobotMessage operator+(const RobotMessage& other){
        if(other.message.size() != message.size()){
            throw std::runtime_error("Incompatible message format");
        }

        RobotMessage combined = RobotMessage();
        for(unsigned int i = 0; i < message.size(); i++){
            combined.message.push_back(message[i] + other.message[i]);
        }
        return combined;

    }


};

class GroupRobotWorldModel;
class CommunicationModule {
public:
    CommunicationModule();

    CommunicationModule(GroupRobotWorldModel *owner);

    RobotMessage read(int width);

    void broadcast(RobotMessage message);

private:
    RobotMessage outgoingMessage;
    GroupRobotWorldModel *owner;

};
#endif //ROBOROBO2_COMMUNICATIONMODULE_H
