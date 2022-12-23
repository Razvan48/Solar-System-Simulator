#include "GameEngine3D/GameEngine3D.h"

int main()
{
	GameEngine::Get()->Start(1024, 1024, "3D Solar System");

	// AICI E RENDER-UL

	RendererWithLighting* rendererWithLighting = new RendererWithLighting("GameEngine3D/Shaders/ShaderWithLighting/VertexShaderWithLighting.txt", "GameEngine3D/Shaders/ShaderWithLighting/FragmentShaderWithLighting.txt");
	RendererNoLighting* rendererNoLighting = new RendererNoLighting("GameEngine3D/Shaders/ShaderNoLighting/VertexShaderNoLighting.txt", "GameEngine3D/Shaders/ShaderNoLighting/FragmentShaderNoLighting.txt");

	MeshManager::Get()->AddMesh("Sfera", "GameEngine3D/Meshes/Sfera/Sfera.txt");

	// PLANETELE MAI JOS SI COMPONENTELE ATASATE ACESTORA (PUTEM SCHIMBA VALORI PENTRU A AVEA DIVERSE EFECTE)

	// SOARE
	Entity* Soare = new Entity();

	Soare->AddComponent(new Position());
	Soare->AddComponent(new Scale(10.0, 10.0, 10.0));
	Soare->AddComponent(new Rotation(0.0, 1.0, 0.0, 1.0));
	Soare->AddComponent(new Texture());
	Soare->AddComponent(new Mesh());
	//Soare->AddComponent(new PointLight());
	Soare->AddComponent(new Render());

	TextureManager::Get()->AddTexture("Soare", "GameEngine3D/Textures/Soare/Soare.png");
	Soare->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Soare");

	Soare->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// PAMANT
	Entity* Pamant = new Entity();

	Pamant->AddComponent(new Position());
	Pamant->AddComponent(new Scale(0.91, 0.91, 0.91));
	Pamant->AddComponent(new Rotation(0.0, 1.0, 0.0, 5.0));
	Pamant->AddComponent(new Texture());
	Pamant->AddComponent(new Mesh());
	Pamant->AddComponent(new PointLight());
	Pamant->AddComponent(new Render());
	Pamant->AddComponent(new TangentSpeed(0.1));

	TextureManager::Get()->AddTexture("Pamant", "GameEngine3D/Textures/Pamant/Pamant.png");
	Pamant->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Pamant");

	Pamant->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// LUNA
	Entity* Luna = new Entity();

	Luna->AddComponent(new Position());
	Luna->AddComponent(new Scale(0.25, 0.25, 0.25));
	Luna->AddComponent(new Rotation(0.0, 1.0, 0.0, 5.0));
	Luna->AddComponent(new Texture());
	Luna->AddComponent(new Mesh());
	Luna->AddComponent(new PointLight());
	Luna->AddComponent(new Render());
	Luna->AddComponent(new TangentSpeed(3.431));

	TextureManager::Get()->AddTexture("Luna", "GameEngine3D/Textures/Luna/Luna.png");
	Luna->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Luna");

	Luna->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	// MERCUR
	Entity* Mercur = new Entity();

	Mercur->AddComponent(new Position());
	Mercur->AddComponent(new Scale(0.3825, 0.3825, 0.3825));
	Mercur->AddComponent(new Rotation(0.0, 1.0, 0.0, 7.0));
	Mercur->AddComponent(new Texture());
	Mercur->AddComponent(new Mesh());
	Mercur->AddComponent(new PointLight());
	Mercur->AddComponent(new Render());
	Mercur->AddComponent(new TangentSpeed(0.16));

	TextureManager::Get()->AddTexture("Mercur", "GameEngine3D/Textures/Mercur/Mercur.png");
	Mercur->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Mercur");

	Mercur->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// VENUS
	Entity* Venus = new Entity();

	Venus->AddComponent(new Position());
	Venus->AddComponent(new Scale(0.95, 0.95, 0.95));
	Venus->AddComponent(new Rotation(0.0, 1.0, 0.0, 3.0));
	Venus->AddComponent(new Texture());
	Venus->AddComponent(new Mesh());
	Venus->AddComponent(new PointLight());
	Venus->AddComponent(new Render());
	Venus->AddComponent(new TangentSpeed(0.117));

	TextureManager::Get()->AddTexture("Venus", "GameEngine3D/Textures/Venus/Venus.png");
	Venus->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Venus");

	Venus->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// MARTE
	Entity* Marte = new Entity();

	Marte->AddComponent(new Position());
	Marte->AddComponent(new Scale(0.5, 0.5, 0.5));
	Marte->AddComponent(new Rotation(0.0, 1.0, 0.0, 8.0));
	Marte->AddComponent(new Texture());
	Marte->AddComponent(new Mesh());
	Marte->AddComponent(new PointLight());
	Marte->AddComponent(new Render());
	Marte->AddComponent(new TangentSpeed(0.08));

	TextureManager::Get()->AddTexture("Marte", "GameEngine3D/Textures/Marte/Marte.png");
	Marte->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Marte");

	Marte->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// JUPITER
	Entity* Jupiter = new Entity();

	Jupiter->AddComponent(new Position(45.0, 0.0, 0.0));
	Jupiter->AddComponent(new Scale(10.97, 10.97, 10.97));
	Jupiter->AddComponent(new Rotation(0.0, 1.0, 0.0, 12.0));
	Jupiter->AddComponent(new Texture());
	Jupiter->AddComponent(new Mesh());
	Jupiter->AddComponent(new PointLight());
	Jupiter->AddComponent(new Render());
	Jupiter->AddComponent(new TangentSpeed(0.044));

	TextureManager::Get()->AddTexture("Jupiter", "GameEngine3D/Textures/Jupiter/Jupiter.png");
	Jupiter->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Jupiter");

	Jupiter->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// SATURN
	Entity* Saturn = new Entity();

	Saturn->AddComponent(new Position(55.0, 0.0, 0.0));
	Saturn->AddComponent(new Scale(8.65, 8.65, 8.65));
	Saturn->AddComponent(new Rotation(0.0, 1.0, 0.0, 12.0));
	Saturn->AddComponent(new Texture());
	Saturn->AddComponent(new Mesh());
	Saturn->AddComponent(new PointLight());
	Saturn->AddComponent(new Render());
	Saturn->AddComponent(new TangentSpeed(0.0325));

	TextureManager::Get()->AddTexture("Saturn", "GameEngine3D/Textures/Saturn/Saturn.png");
	Saturn->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Saturn");

	Saturn->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// INEL SATURN
	Entity* Inel = new Entity();

	Inel->AddComponent(new Position());
	Inel->AddComponent(new Scale(8.7, 8.7, 8.7));
	Inel->AddComponent(new Rotation(0.075, 1.0, 0.075, 2.0));
	Inel->AddComponent(new Texture());
	Inel->AddComponent(new Mesh());
	Inel->AddComponent(new PointLight());
	Inel->AddComponent(new Render());

	TextureManager::Get()->AddTexture("Inel", "GameEngine3D/Textures/Inel/Inel.png");
	Inel->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Inel");

	MeshManager::Get()->AddMesh("Inel", "GameEngine3D/Meshes/Inel/Inel.txt");
	Inel->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Inel");

	//

	// URANUS
	Entity* Uranus = new Entity();

	Uranus->AddComponent(new Position(65.0, 0.0, 0.0));
	Uranus->AddComponent(new Scale(3.98, 3.98, 3.98));
	Uranus->AddComponent(new Rotation(0.0, 1.0, 0.0, 12.0));
	Uranus->AddComponent(new Texture());
	Uranus->AddComponent(new Mesh());
	Uranus->AddComponent(new PointLight());
	Uranus->AddComponent(new Render());
	Uranus->AddComponent(new TangentSpeed(0.023));

	TextureManager::Get()->AddTexture("Uranus", "GameEngine3D/Textures/Uranus/Uranus.png");
	Uranus->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Uranus");

	Uranus->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// NEPTUN
	Entity* Neptun = new Entity();

	Neptun->AddComponent(new Position(70.0, 0.0, 0.0));
	Neptun->AddComponent(new Scale(3.85, 3.85, 3.85));
	Neptun->AddComponent(new Rotation(0.0, 1.0, 0.0, 12.0));
	Neptun->AddComponent(new Texture());
	Neptun->AddComponent(new Mesh());
	Neptun->AddComponent(new PointLight());
	Neptun->AddComponent(new Render());
	Neptun->AddComponent(new TangentSpeed(0.018));

	TextureManager::Get()->AddTexture("Neptun", "GameEngine3D/Textures/Neptun/Neptun.png");
	Neptun->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Neptun");

	Neptun->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// PLUTO
	Entity* Pluto = new Entity();

	Pluto->AddComponent(new Position(75.0, 0.0, 0.0));
	Pluto->AddComponent(new Scale(0.186, 0.186, 0.186));
	Pluto->AddComponent(new Rotation(0.0, 1.0, 0.0, 12.0));
	Pluto->AddComponent(new Texture());
	Pluto->AddComponent(new Mesh());
	Pluto->AddComponent(new PointLight());
	Pluto->AddComponent(new Render());
	Pluto->AddComponent(new TangentSpeed(0.016));

	TextureManager::Get()->AddTexture("Pluto", "GameEngine3D/Textures/Pluto/Pluto.png");
	Pluto->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Pluto");

	Pluto->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Sfera");

	//

	// CENTURA ASTEROIZI 1
	Entity* Centura1 = new Entity();

	Centura1->AddComponent(new Position());
	Centura1->AddComponent(new Scale(325.0, 325.0, 325.0));
	Centura1->AddComponent(new Rotation(0.0, 1.0, 0.0, 0.15));
	Centura1->AddComponent(new Texture());
	Centura1->AddComponent(new Mesh());
	Centura1->AddComponent(new PointLight());
	Centura1->AddComponent(new Render());

	TextureManager::Get()->AddTexture("Centura", "GameEngine3D/Textures/Centura/Centura.png");
	Centura1->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Centura");

	MeshManager::Get()->AddMesh("Centura", "GameEngine3D/Meshes/Centura/Centura.txt");
	Centura1->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Centura");

	//

	// CENTURA ASTEROIZI 2
	Entity* Centura2 = new Entity();

	Centura2->AddComponent(new Position());
	Centura2->AddComponent(new Scale(900.0, 900.0, 900.0));
	Centura2->AddComponent(new Rotation(0.0, 1.0, 0.0, 0.25));
	Centura2->AddComponent(new Texture());
	Centura2->AddComponent(new Mesh());
	Centura2->AddComponent(new PointLight());
	Centura2->AddComponent(new Render());

	Centura2->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Centura");

	Centura2->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Centura");

	//

	// FUNDAL FAKE
	Entity* Fundal = new Entity();
	Fundal->AddComponent(new Position());
	Fundal->AddComponent(new Scale(32768.0, 32768.0, 32768.0));
	Fundal->AddComponent(new Rotation());
	Fundal->AddComponent(new Texture());
	Fundal->AddComponent(new Mesh());
	Fundal->AddComponent(new Render());

	TextureManager::Get()->AddTexture("Fundal", "GameEngine3D/Textures/Fundal/Fundal.png");
	Fundal->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetTextureID("Fundal");

	MeshManager::Get()->AddMesh("Fundal", "GameEngine3D/Meshes/Fundal/Fundal.txt");
	Fundal->GetComponent<Mesh>()->currentMesh = MeshManager::Get()->GetMesh("Fundal");

	//

	while (!GameEngine::Get()->ShouldGameEngineStop())
	{
		GameEngine::Get()->Update();

		// CONTROALE PENTRU FOCUS PE PLANETA (DOAR ACUM) (P = PAMANT);
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
		{
			Camera::Get()->position.x = 105.0 * sin(TimeManager::Get()->GetCurrentTime() * Pamant->GetComponent<TangentSpeed>()->speed);
			Camera::Get()->position.z = 105.0 * cos(TimeManager::Get()->GetCurrentTime() * Pamant->GetComponent<TangentSpeed>()->speed);
			//Camera::Get()->viewDir = normalize(Pamant->GetComponent<Position>()->position - Camera::Get()->position);
		}

		//AICI DESENAM PLANETE

		//Fundal->GetComponent<Position>()->position = Camera::Get()->position;
		//Fundal->GetComponent<Render>()->Draw(rendererNoLighting);

		//Soare->GetComponent<Mass>()->mass *= 1.002;

		//Soare->GetComponent<PointLight>()->position = glm::vec3(Camera::Get()->position);
		Soare->GetComponent<Render>()->Draw(rendererNoLighting);

		Pamant->GetComponent<Position>()->position = glm::vec3(90.0 * sin(TimeManager::Get()->GetCurrentTime() * Pamant->GetComponent<TangentSpeed>()->speed), 0.0, 90.0 * cos(TimeManager::Get()->GetCurrentTime() * Pamant->GetComponent<TangentSpeed>()->speed));
		Pamant->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Pamant->GetComponent<Render>()->Draw(rendererWithLighting);

		Luna->GetComponent<Position>()->position = glm::vec3(Pamant->GetComponent<Position>()->position.x + 2.57 * cos(TimeManager::Get()->GetCurrentTime() * Luna->GetComponent<TangentSpeed>()->speed), Pamant->GetComponent<Position>()->position.y, Pamant->GetComponent<Position>()->position.z + 2.57 * sin(TimeManager::Get()->GetCurrentTime() * Luna->GetComponent<TangentSpeed>()->speed));
		Luna->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Luna->GetComponent<Render>()->Draw(rendererWithLighting);

		Mercur->GetComponent<Position>()->position = glm::vec3(38.71 * sin(TimeManager::Get()->GetCurrentTime() * Mercur->GetComponent<TangentSpeed>()->speed), 0.0, 38.71 * cos(TimeManager::Get()->GetCurrentTime() * Mercur->GetComponent<TangentSpeed>()->speed));
		Mercur->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Mercur->GetComponent<Render>()->Draw(rendererWithLighting);

		Venus->GetComponent<Position>()->position = glm::vec3(72.0 * sin(TimeManager::Get()->GetCurrentTime() * Venus->GetComponent<TangentSpeed>()->speed), 0.0, 72.0 * cos(TimeManager::Get()->GetCurrentTime() * Venus->GetComponent<TangentSpeed>()->speed));
		Venus->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Venus->GetComponent<Render>()->Draw(rendererWithLighting);

		Marte->GetComponent<Position>()->position = glm::vec3(152.3 * sin(TimeManager::Get()->GetCurrentTime() * Marte->GetComponent<TangentSpeed>()->speed), 0.0, 152.3 * cos(TimeManager::Get()->GetCurrentTime() * Marte->GetComponent<TangentSpeed>()->speed));
		Marte->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Marte->GetComponent<Render>()->Draw(rendererWithLighting);

		Jupiter->GetComponent<Position>()->position = glm::vec3(520.0 * sin(TimeManager::Get()->GetCurrentTime() * Jupiter->GetComponent<TangentSpeed>()->speed), 0.0, 520.0 * cos(TimeManager::Get()->GetCurrentTime() * Jupiter->GetComponent<TangentSpeed>()->speed));
		Jupiter->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Jupiter->GetComponent<Render>()->Draw(rendererWithLighting);

		Saturn->GetComponent<Position>()->position = glm::vec3(958.0 * sin(TimeManager::Get()->GetCurrentTime() * Saturn->GetComponent<TangentSpeed>()->speed), 0.0, 958.0 * cos(TimeManager::Get()->GetCurrentTime() * Saturn->GetComponent<TangentSpeed>()->speed));
		Saturn->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Saturn->GetComponent<Render>()->Draw(rendererWithLighting);

		Inel->GetComponent<Position>()->position = Saturn->GetComponent<Position>()->position;
		Inel->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Inel->GetComponent<Render>()->Draw(rendererWithLighting);

		Uranus->GetComponent<Position>()->position = glm::vec3(1922.0 * sin(TimeManager::Get()->GetCurrentTime() * Uranus->GetComponent<TangentSpeed>()->speed), 0.0, 1922.0 * cos(TimeManager::Get()->GetCurrentTime() * Uranus->GetComponent<TangentSpeed>()->speed));
		Uranus->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Uranus->GetComponent<Render>()->Draw(rendererWithLighting);

		Neptun->GetComponent<Position>()->position = glm::vec3(3007.0 * sin(TimeManager::Get()->GetCurrentTime() * Neptun->GetComponent<TangentSpeed>()->speed), 0.0, 3007.0 * cos(TimeManager::Get()->GetCurrentTime() * Neptun->GetComponent<TangentSpeed>()->speed));
		Neptun->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Neptun->GetComponent<Render>()->Draw(rendererWithLighting);

		Pluto->GetComponent<Position>()->position = glm::vec3(3948.0 * sin(TimeManager::Get()->GetCurrentTime() * Pluto->GetComponent<TangentSpeed>()->speed), 0.0, 3948.0 * cos(TimeManager::Get()->GetCurrentTime() * Pluto->GetComponent<TangentSpeed>()->speed));
		Pluto->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Pluto->GetComponent<Render>()->Draw(rendererWithLighting);

		Centura1->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Centura1->GetComponent<Render>()->Draw(rendererWithLighting);

		Centura2->GetComponent<PointLight>()->position = glm::vec3(Soare->GetComponent<Position>()->position);
		Centura2->GetComponent<Render>()->Draw(rendererWithLighting);

		std::cout << "FPS :: " << 1.0 / TimeManager::Get()->GetDeltaTime() << '\n';
	}

	GameEngine::Get()->Stop();

	return 0;
}