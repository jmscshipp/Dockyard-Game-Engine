//#ifndef _ScreenLogMessagePool
//#define _ScreenLogMessagePool
//
//#include <stack>
//
//// forward declaration
//class SpriteString;
//
//class ScreenLogMessagePool
//{
//public:
//	ScreenLogMessagePool(); // big four
//	ScreenLogMessagePool(const ScreenLogMessagePool&) = delete;
//	ScreenLogMessagePool& operator=(const ScreenLogMessagePool&) = delete;
//	~ScreenLogMessagePool();
//
//	SpriteString* GetAMessage();
//	void ReturnMessage(SpriteString* cmd);
//
//private:
//	std::stack<SpriteString*> recycledMessages;
//};
//
//#endif
//