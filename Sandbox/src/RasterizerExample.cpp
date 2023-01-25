#include "RasterizerExample.h"
#include <Utils/Logger.h>
#include <core/Application.h>
#include <input/Input.h>
#include <Math/Maths.h>

#include <Event/ApplicationEvent.h>
#include <Event/KeyEvent.h>
#include <Event/MouseEvent.h>

Dindi::Model* model = nullptr;

void RasterizerExample::OnAttach()
{
	//FROM HERE TO BELOW IS ALL DEBUG STUFF
	Dindi::Application& app = Dindi::Application::GetInstance();

	m_DefaultEditorCamera = new Dindi::Camera(app.GetWindow()->GetAspectRatio(), Dindi::vec3(0.0f, 0.0f, 5.0f));
	m_DefaultEditorCameraSpeed = 10.0f;
	m_DefaultEditorCamera->SetCameraLag(true);
	m_DefaultEditorCamera->SetCameraLagValue(0.15f);

	SceneOne = new Dindi::Scene();
	SceneOne->SetActiveCamera(m_DefaultEditorCamera);

	//DEBUG
	m_DefaultEditorCamera->SetCameraYaw(0.0f);
	m_DefaultEditorCamera->SetCameraPitch(0.0f);
	model = new Dindi::Model(RESOURCES_PATH "Resources\\Models\\cube.obj", Dindi::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	SceneOne->AddPointLight({Dindi::vec4(0.0f), Dindi::vec4(1.0f)});
	SceneOne->AddEntity(model);

	app.SetActiveScene(SceneOne);
}

void RasterizerExample::OnDetach()
{
	//#TODO: Unload stuff (like scene Models etc...)
}

void RasterizerExample::OnUIRender()
{
}

void RasterizerExample::OnUpdate(const Dindi::DeltaTime& dt)
{
	LookAround();
	MoveCamera(dt);
}

void RasterizerExample::OnEvent(Dindi::Event& event)
{
	DND_LOG_TRACE(event);
}

void RasterizerExample::MoveCamera(const Dindi::DeltaTime& dt)
{
	Dindi::vec3 IntendedCameraPosition;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_W))
		IntendedCameraPosition.z = -m_DefaultEditorCameraSpeed;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_S))
		IntendedCameraPosition.z = m_DefaultEditorCameraSpeed;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_D))
		IntendedCameraPosition.x = m_DefaultEditorCameraSpeed;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_A))
		IntendedCameraPosition.x = -m_DefaultEditorCameraSpeed;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_SPACE))
		IntendedCameraPosition.y = m_DefaultEditorCameraSpeed;

	if (Dindi::Input::IsKeyPressed(Dindi::EKeyCode::DND_KEY_LEFT_CONTROL))
		IntendedCameraPosition.y = -m_DefaultEditorCameraSpeed;

	//Add this vector on the Target Position, this is, where we are looking at, thus making a free camera style
	SceneOne->GetActiveCamera()->AddCameraTargetPosition(IntendedCameraPosition, dt);
}

void RasterizerExample::LookAround()
{
	Dindi::vec2 MousePosition = Dindi::Input::GetMousePosition();
	Dindi::Camera* sceneCamera = SceneOne->GetActiveCamera();

	sceneCamera->SetCameraYaw(Dindi::toRadians(MousePosition.x));
	sceneCamera->SetCameraPitch(Dindi::toRadians(MousePosition.y));
}

