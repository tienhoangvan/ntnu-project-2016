//
// Created by christopher on 05.02.16.
//

#ifndef ROBOROBO2_PORTPOSITION_H
#define ROBOROBO2_PORTPOSITION_H

#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"

class PortPosition {
    private:
        int _posX;
        int _posY;
        int _collisionPositionOffset;
        int _collisionOrientationOffset;

        GroupRobotWorldModel* _wm;

        bool isOrientationalSound(int sourceOrientation, int targetOrientation);
        bool isSpatiallySound(PortPosition* target);

    public:
        PortPosition(GroupRobotWorldModel* sourceRobotModel);

        PortPosition* getPortPosition(int orientation);

        bool isGeometricValidConnection(int sourceOrientation, PortPosition* target, int targetOrientation);

        void updatePosition(int orientation);

        int getPosX() { return _posX; };
        int getPosY() { return _posY; };


};


#endif //ROBOROBO2_PORTPOSITION_H
