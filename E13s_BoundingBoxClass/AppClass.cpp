#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);
	m_v3O3 = vector3(1.0f, 1.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Zombie.obj", "Zombie");

	//Init the Bounding Object Manager and pass in the Mesh Manager 
	m_pBOMngr = BoundingObjectMngr::Instance();
	m_pBOMngr->InitMeshManager(m_pMeshMngr);

	//Add Bounding Objects to the models
	//**Must use the same names as when you load the models**
	m_pBOMngr->AddBoundingObject("Steve");
	m_pBOMngr->AddBoundingObject("Creeper");
	m_pBOMngr->AddBoundingObject("Zombie");

	//Set the visibility of the creeper's bounding box **used as a test for the method**
	m_pBOMngr->SetBOVisibility("Creeper", false);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O3), "Zombie");
	
	//set the matricies of the BO's 
	m_pBOMngr->SetBOMatrix("Steve", m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBOMngr->SetBOMatrix("Creeper", m_pMeshMngr->GetModelMatrix("Creeper"));
	m_pBOMngr->SetBOMatrix("Zombie", m_pMeshMngr->GetModelMatrix("Zombie"));

	//Check the Collisions of all of the Bounding Objects
	m_pBOMngr->CheckCollisions();

	//Render Bounding Objects
	// **Like with the Mesh Manager, use the keyword "ALL" to render all stored BO's,
	// or use the name of a model to only render that one.**
	m_pBOMngr->RenderBoundingObjects("ALL");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	SafeDelete(m_pBO1);
	SafeDelete(m_pBO2);
}