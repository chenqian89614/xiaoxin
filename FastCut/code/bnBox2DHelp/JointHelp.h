#ifndef _JointHelp_H_
#define _JointHelp_H_

#include "Box2d/Box2d.h"

class JointHelp
{
public :
	JointHelp(b2Body* bodyA, b2Body* bodyB, b2World* world)
	{
		b2RopeJointDef bjd;
		bjd.maxLength = 960.0f;
		bjd.bodyA = bodyA;
		bjd.bodyB = bodyB;
		bjd.collideConnected = false;
		world->CreateJoint(&bjd);
	}
};


#endif
