#include "VisualizeCommandPool.h"
#include "VisualizeCommandAABB.h"
#include "VisualizeCommandOBB.h"
#include "VisualizeCommandBSphere.h"
#include "VisualizeCommandBoxAtPoint.h"
#include "VisualizeCommandLine.h"

VisualizeCommandPool::VisualizeCommandPool()
{
	recycledAABBCommands = {};
	recycledOBBCommands = {};
	recycledBSphereCommands = {};
	recycledBoxAtPointCommands = {};
	recycledLineCommands = {};
}

VisualizeCommandPool::~VisualizeCommandPool()
{
	Trace::out("closing VisualizeCommandPool");
	while (!recycledAABBCommands.empty())
	{
		delete recycledAABBCommands.top();
		recycledAABBCommands.pop();
	}
	while (!recycledOBBCommands.empty())
	{
		delete recycledOBBCommands.top();
		recycledOBBCommands.pop();
	}
	while (!recycledBSphereCommands.empty())
	{
		delete recycledBSphereCommands.top();
		recycledBSphereCommands.pop();
	}
	while (!recycledBoxAtPointCommands.empty())
	{
		delete recycledBoxAtPointCommands.top();
		recycledBoxAtPointCommands.pop();
	}
	while (!recycledLineCommands.empty())
	{
		delete recycledLineCommands.top();
		recycledLineCommands.pop();
	}
}

VisualizeCommandAABB* VisualizeCommandPool::GetAABBCommand()
{
	VisualizeCommandAABB* cmdInstance;

	if (recycledAABBCommands.empty())
		cmdInstance = new VisualizeCommandAABB();
	else
	{
		cmdInstance = recycledAABBCommands.top();
		recycledAABBCommands.pop();
	}
	return cmdInstance;
}

VisualizeCommandOBB* VisualizeCommandPool::GetOBBCommand()
{
	VisualizeCommandOBB* cmdInstance;

	if (recycledOBBCommands.empty())
		cmdInstance = new VisualizeCommandOBB();
	else
	{
		cmdInstance = recycledOBBCommands.top();
		recycledOBBCommands.pop();
	}
	return cmdInstance;
}

VisualizeCommandBSphere* VisualizeCommandPool::GetBSphereCommand()
{
	VisualizeCommandBSphere* cmdInstance;

	if (recycledBSphereCommands.empty())
		cmdInstance = new VisualizeCommandBSphere();
	else
	{
		cmdInstance = recycledBSphereCommands.top();
		recycledBSphereCommands.pop();
	}
	return cmdInstance;
}

VisualizeCommandBoxAtPoint* VisualizeCommandPool::GetBoxAtPointCommand()
{
	VisualizeCommandBoxAtPoint* cmdInstance;

	if (recycledBoxAtPointCommands.empty())
		cmdInstance = new VisualizeCommandBoxAtPoint();
	else
	{
		cmdInstance = recycledBoxAtPointCommands.top();
		recycledBoxAtPointCommands.pop();
	}
	return cmdInstance;
}

VisualizeCommandLine* VisualizeCommandPool::GetLineCommand()
{
	VisualizeCommandLine* cmdInstance;

	if (recycledLineCommands.empty())
		cmdInstance = new VisualizeCommandLine();
	else
	{
		cmdInstance = recycledLineCommands.top();
		recycledLineCommands.pop();
	}
	return cmdInstance;
}

void VisualizeCommandPool::ReturnVisualizeCommand(VisualizeCommandAABB* cmd)
{
	recycledAABBCommands.push(cmd);
}

void VisualizeCommandPool::ReturnVisualizeCommand(VisualizeCommandOBB* cmd)
{
	recycledOBBCommands.push(cmd);
}

void VisualizeCommandPool::ReturnVisualizeCommand(VisualizeCommandBSphere* cmd)
{
	recycledBSphereCommands.push(cmd);
}

void VisualizeCommandPool::ReturnVisualizeCommand(VisualizeCommandBoxAtPoint* cmd)
{
	recycledBoxAtPointCommands.push(cmd);
}

void VisualizeCommandPool::ReturnVisualizeCommand(VisualizeCommandLine* cmd)
{
	recycledLineCommands.push(cmd);
}