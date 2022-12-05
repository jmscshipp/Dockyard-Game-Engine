#ifndef _VisualizeCommandPool
#define _VisualizeCommandPool

#include <stack>

// forward declaration
class VisualizeCommandAABB;
class VisualizeCommandOBB;
class VisualizeCommandBSphere;
class VisualizeCommandBoxAtPoint;
class VisualizeCommandLine;

class VisualizeCommandPool
{
public:
	VisualizeCommandPool(); // big four
	VisualizeCommandPool(const VisualizeCommandPool&) = delete;
	VisualizeCommandPool& operator=(const VisualizeCommandPool&) = delete;
	~VisualizeCommandPool();

	VisualizeCommandAABB* GetAABBCommand();
	VisualizeCommandOBB* GetOBBCommand();
	VisualizeCommandBSphere* GetBSphereCommand();
	VisualizeCommandBoxAtPoint* GetBoxAtPointCommand();
	VisualizeCommandLine* GetLineCommand();

	void ReturnVisualizeCommand(VisualizeCommandAABB* cmd);
	void ReturnVisualizeCommand(VisualizeCommandOBB* cmd);
	void ReturnVisualizeCommand(VisualizeCommandBSphere* cmd);
	void ReturnVisualizeCommand(VisualizeCommandBoxAtPoint* cmd);
	void ReturnVisualizeCommand(VisualizeCommandLine* cmd);

private:
	std::stack<VisualizeCommandAABB*> recycledAABBCommands;
	std::stack<VisualizeCommandOBB*> recycledOBBCommands;
	std::stack<VisualizeCommandBSphere*> recycledBSphereCommands;
	std::stack<VisualizeCommandBoxAtPoint*> recycledBoxAtPointCommands;
	std::stack<VisualizeCommandLine*> recycledLineCommands;
};

#endif