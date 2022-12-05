//#include "ScreenLog.h"
//#include "SpriteString.h"
//#include "ScreenLogMessagePool.h"
//#include "SpriteFontManager.h"
//
//ScreenLog* ScreenLog::instance = nullptr;
//char ScreenLog::debugBuffer[] = { 0 };
//
//ScreenLog::ScreenLog()
//	: msgPool(new ScreenLogMessagePool()),
//	anchorX(0),
//	anchorY(0),
//	originalAnchorY(0),
//	font(SpriteFontManager::GetSpriteFont("DefaultFont"))
//{
//}
//
//ScreenLog::~ScreenLog()
//{
//	delete msgPool;
//	for (Message m : messages)
//		delete m;
//}
//
//
//void ScreenLog::PrivSetAnchor(int x, int y)
//{
//	anchorX = x;
//	anchorY = y;
//	originalAnchorY = y;
//}
//
//void ScreenLog::PrivSetFont(SpriteFont* newFont)
//{
//	font = newFont;
//}
//
//void ScreenLog::NonstaticRender()
//{
//	for (Message m : messages)
//	{
//		m->Render();
//		msgPool->ReturnMessage(m);
//	}
//	messages.clear();
//	anchorY = originalAnchorY;
//}
//
//void ScreenLog::AddToCollection(const std::string& s)
//{
//	SpriteString* newStr = msgPool->GetAMessage();
//	newStr->Set(font, s, anchorX, anchorY);
//	messages.push_back(newStr);
//	anchorY -= newStr->GetHeight();
//}
//
//void ScreenLog::Add(char* A, ...)
//{
//	va_list args;
//	va_start(args, A);
//	vsprintf_s(debugBuffer, A, args);
//	va_end(args);
//
//	std::string s(debugBuffer);
//	Instance().AddToCollection(s);
//}
//
//void ScreenLog::NonstaticDelete()
//{
//	delete instance;
//	instance = nullptr;
//}