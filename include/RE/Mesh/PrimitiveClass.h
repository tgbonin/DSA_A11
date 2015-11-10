/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVECLASS_H_
#define __PRIMITIVECLASS_H_

#include "RE\Mesh\MeshClass.h"

namespace ReEng
{

class ReEngDLL PrimitiveClass : public MeshClass
{
	typedef MeshClass super;

public:
	/*
	Method: PrimitiveClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	PrimitiveClass();
	/* Copy Constructor */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	PrimitiveClass(const PrimitiveClass& other);
	/* Copy Assignment Operator */
	/*
	Method: Usage:
	Arguments:
	Output:
	*/
	virtual PrimitiveClass& operator=(const PrimitiveClass& other);

	/* Destructor */
	/*
	Method: Usage:
	Arguments: ---
	Output: ---
	*/
	~PrimitiveClass(void);

	/* Generates a cube shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateCube(float a_fSize, vector3 a_v3Color);
	/* Generates a cone shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a cylinder shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a tube shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a torus shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeigh, int a_nSubdivisionAxis, vector3 a_v3Color);
	/* Generates a Sphere shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a plane shape */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void GeneratePlane(float a_fSize, vector3 a_v3Color);
	
	///* Renders the primitive asking for its rendering mode (default is GL_TRIANGLES)*/
	//virtual void Render(void);
	///* Renders the primitive asking for the model matrix and the color */
	//virtual void Render(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);
	///* Renders the primitive in wireframe mode asking for the model matrix and the color */
	//virtual void RenderWire(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);

private:
	/* Compiles the object with an specific color and name */
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void CompileObject(vector3 a_v3Color, String a_sName);
	/* Adds a quad to the list points in the buffer to be compiled*/
	/*
	Method: Usage:
	Arguments:
	Output: ---
	*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveClass*>;

}

#endif //_POLYGONCLASS_H