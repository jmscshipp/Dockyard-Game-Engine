#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

class CollisionTestCommandBase
{
public:
	// big four
	CollisionTestCommandBase() = default;
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	CollisionTestCommandBase& operator = (const CollisionTestCommandBase&) = delete;
	virtual ~CollisionTestCommandBase() = default;

	virtual void Execute() = 0;

private:

};

#endif