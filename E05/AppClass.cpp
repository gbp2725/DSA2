#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_BROWN);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	static float timer = 0;
	static uint uClock = m_pSystem->GenClock(); 
	timer += static_cast<float>(m_pSystem->GetDeltaTime(uClock));

	static vector3 changePosition(-20.0f, 0.0f, 0.0f);

	changePosition.x += timer / 500;
	matrix4 position = glm::translate(vector3(-5.0f, -3.0f, -15.0f)) * glm::translate(changePosition);
	
	//Draw all the boxes in the positions that draw the face thingy
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(3.0f, 0.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(4.0f, 0.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(6.0f, 0.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(7.0f, 0.0f, 0.0f))); 

	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(0.0f, 1.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(2.0f, 1.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(8.0f, 1.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(10.0f, 1.0f, 0.0f)));

	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(0.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(2.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(3.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(4.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(5.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(6.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(7.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(8.0f, 2.0f, 0.0f))); 
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(10.0f, 2.0f, 0.0f)));

	for (uint count = 0; count < 11; ++count)
	{
		m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(count, 3.0f, 0.0f)));
	}

	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(1.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(2.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(4.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(5.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(6.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(8.0f, 4.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(9.0f, 4.0f, 0.0f)));

	for (uint count = 2; count < 9; ++count)
	{
		m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(count, 5.0f, 0.0f)));
	}

	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(3, 6.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(7, 6.0f, 0.0f)));

	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(2, 7.0f, 0.0f)));
	m_pMesh1->Render(m4Projection, m4View, glm::translate(position, vector3(8, 7.0f, 0.0f)));

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}