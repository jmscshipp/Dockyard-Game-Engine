#ifndef _Rect
#define _Rect

struct Rect
{
public:
	// big four
	Rect() = delete;
	Rect(float x, float y, float width, float height);
	Rect(const Rect&) = default;
	Rect& operator=(const Rect&) = default;
	~Rect() = default;;

	// Clear method
	//void clear();
	// what is this suppose to do

	// Structure data, public
	float x;
	float y;
	float width;
	float height;
};


#endif