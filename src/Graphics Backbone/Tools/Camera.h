#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"

class Camera  
{
public:
	enum class Type
	{
		PERSPECTIVE_3D,
		ORTHOGRAPHIC_2D
	};

	// Default constructor
	Camera() = delete;
	Camera(Type cameraType);
	~Camera() = default;

	// Setup on single camera
	void SetPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
	void SetOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);
	void SetOrientAndPosition(const Vect &Up_vect, const Vect &inLookAt_pt, const Vect &pos_pt);

	// update camera system
	void UpdateCamera();

	// Get the matrices for rendering
	Matrix& getViewMatrix();
	Matrix& getProjMatrix();

	// accessors
	void getPos(Vect &outPos) const;
	void getDir(Vect &outDir) const;
	void getUp(Vect &outUp) const;
	void getLookAt(Vect &outLookAt) const;
	void getRight(Vect &outRight) const;

	void TranslateLeftRight(float delta);
	void TranslateFwdBack(float delta);
	void TiltUpDown(float ang);
	void TurnLeftRight(float ang);

	// Why no SETS for Pos, Dir, Up, LookAt and Right?
	//   They have to be adjusted _together_ in setOrientAndPosition()
	
	void PrintMatrix(const Matrix& mat);
private:  // methods should never be public


	void privUpdateProjectionMatrixPersp(void);
	void privUpdateProjectionMatrixOrtho(void);
	void privUpdateViewMatrix(void);

	// Projection Matrix
	Matrix	projMatrix;
	Matrix	viewMatrix;

	// camera unit vectors (up, dir, right)
	Vect vUp;
	Vect vDir;
	Vect vRight;  // derived by up and dir
	Vect vPos;
	Vect vLookAt;

	Camera::Type type;

	// Define the frustum inputs
	float nearDist;
	float farDist;
	float fovy;  // aka view angle along y axis
	float aspectRatio;

	// ortho stuff
	float xMin;
	float yMin;
	float zMin;
	float xMax;
	float yMax;
	float zMax;
};

#endif