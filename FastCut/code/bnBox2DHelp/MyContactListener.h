#ifndef  _MyContactListener_H_
#define  _MyContactListener_H_
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class MyContactListener : public b2ContactListener
{
  public:
	b2Vec2 vB;
	b2Vec2 vA;
	void BeginContact(b2Contact* contact)
	{//碰撞开始时的回调方法
		b2Body* bodyA = contact->GetFixtureA()->GetBody();//const
		b2Body* bodyB = contact->GetFixtureB()->GetBody();//const

		std::string* aid=(std::string*)bodyA->GetUserData();
		std::string* bid=(std::string*)bodyB->GetUserData();

		char preFixA = aid->at(0);
		char preFixB = bid->at(0);

//		if((preFixB=='C'&&preFixA=='E'))
//		{
//			b2Vec2 v = bodyB->GetLinearVelocity();
//			bodyB->SetLinearVelocity(b2Vec2(20,10));//-v.x,-v.y
//		}
//		else if(preFixB=='E'&&preFixA=='C')
//		{
//			b2Vec2 v = bodyA->GetLinearVelocity();
//			bodyA->SetLinearVelocity(b2Vec2(-20,-10));//-v.x,-v.y
//		}

    }
	void EndContact(b2Contact* contact)
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();//const
		b2Body* bodyB = contact->GetFixtureB()->GetBody();//const

		std::string* aid=(std::string*)bodyA->GetUserData();
		std::string* bid=(std::string*)bodyB->GetUserData();

		char preFixA = aid->at(0);
		char preFixB = bid->at(0);

		if((preFixB=='C'&&preFixA=='E'))
		{
			b2Vec2 v = bodyB->GetLinearVelocity();
			bodyB->SetLinearVelocity(b2Vec2(v.x * 1.111, v.y * 1.111));//-v.x,-v.y
		}
		else if(preFixB=='E'&&preFixA=='C')
		{
			b2Vec2 v = bodyA->GetLinearVelocity();
			bodyA->SetLinearVelocity(b2Vec2(v.x * 1.111, v.y * 1.111));//-v.x,-v.y
		}

	}
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
};


#endif
