//#include "ScreenLogMessagePool.h"
//#include "SpriteString.h"
//
//ScreenLogMessagePool::ScreenLogMessagePool()
//{
//	recycledMessages = {};
//}
//
//ScreenLogMessagePool::~ScreenLogMessagePool()
//{
//	while (!recycledMessages.empty())
//	{
//		delete recycledMessages.top();
//		recycledMessages.pop();
//	}
//}
//
//SpriteString* ScreenLogMessagePool::GetAMessage()
//{
//	SpriteString* msgInstance;
//
//	if (recycledMessages.empty())
//		msgInstance = new SpriteString();
//	else
//	{
//		msgInstance = recycledMessages.top();
//		recycledMessages.pop();
//	}
//	return msgInstance;
//}
//
//void ScreenLogMessagePool::ReturnMessage(SpriteString* msg)
//{
//	recycledMessages.push(msg);
//}