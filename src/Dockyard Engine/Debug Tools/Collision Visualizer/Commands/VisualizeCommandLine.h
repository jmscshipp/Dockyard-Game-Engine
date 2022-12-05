#ifndef _VisualizeCommandLine
#define _VisualizeCommandLine

#include "VisualizeCommandBase.h"
#include "Vect.h"

class VisualizeCommandLine : public VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandLine() = default;
	VisualizeCommandLine(const VisualizeCommandLine&) = delete;
	VisualizeCommandLine& operator = (const VisualizeCommandLine&) = delete;
	~VisualizeCommandLine() = default;

	void Initialize(const Vect& pos, const Vect& rotDir, const Vect& _color);
	void Execute(VisualizeCommandPool* pool) override;

private:
	 Vect pos;
	 Vect rotDir;
	 Vect color;
};

#endif