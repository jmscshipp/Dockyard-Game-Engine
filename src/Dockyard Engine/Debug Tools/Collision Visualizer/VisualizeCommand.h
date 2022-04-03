#ifndef _VisualizeCommand
#define _VisualizeCommand

// forward declaration
class CollisionVolumeBSphere;
class Vect;

class VisualizeCommand
{
public:
	// big four
	VisualizeCommand() = delete;
	VisualizeCommand(const CollisionVolumeBSphere& sphere, const Vect& color);
	VisualizeCommand(const VisualizeCommand&) = delete;
	VisualizeCommand& operator = (const VisualizeCommand&) = delete;
	~VisualizeCommand() = default;

	void Execute();

private:
	const CollisionVolumeBSphere& colSphere;
	const Vect& displayColor;
};

#endif