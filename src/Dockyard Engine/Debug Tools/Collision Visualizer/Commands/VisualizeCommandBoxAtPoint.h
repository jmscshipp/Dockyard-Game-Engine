#ifndef _VisualizeCommandBoxAtPoint
#define _VisualizeCommandBoxAtPoint

#include "VisualizeCommandBase.h"
#include "Vect.h"

class VisualizeCommandBoxAtPoint : public VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandBoxAtPoint() = default;
	VisualizeCommandBoxAtPoint(const VisualizeCommandBoxAtPoint&) = delete;
	VisualizeCommandBoxAtPoint& operator = (const VisualizeCommandBoxAtPoint&) = delete;
	~VisualizeCommandBoxAtPoint() = default;

	void Initialize(float _x, float _y, float _z, const Vect& _color);
	void Execute(VisualizeCommandPool* pool) override;

private:
	float x, y, z;
	const Vect* color;
};

#endif