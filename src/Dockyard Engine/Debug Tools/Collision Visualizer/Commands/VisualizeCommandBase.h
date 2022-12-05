#ifndef _VisualizeCommandBase
#define _VisualizeCommandBase

// forward declaration
class VisualizeCommandPool;

class VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandBase() = default;
	VisualizeCommandBase(const VisualizeCommandBase&) = delete;
	VisualizeCommandBase& operator = (const VisualizeCommandBase&) = delete;
	virtual ~VisualizeCommandBase() = default;

	virtual void Execute(VisualizeCommandPool* pool) = 0;
};

#endif