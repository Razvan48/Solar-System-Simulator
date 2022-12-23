#pragma once

// INCLUDERE OPENGL

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL2.h>

// INCLUDERE FUNCTIONALITATI DIN LIBRARIA STANDARD

#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <bitset>

// GAME ENGINE

class GameEngine; // CLASA PRINCIPALA

// SISTEMELE ENGINE-ULUI

class WindowManager;
class TimeManager;
class InputManager;
class TextureManager;
class MeshManager;

class SpeedStorage; // DOAR ACUM
class MassStorage; // DOAR ACUM

class SpeedManager; // DOAR ACUM
class MassManager; // DOAR ACUM

// RENDERER

// VOM AVEA VARFURILE, NORMALELE SI APOI TEXTURILE
class RendererWithLighting;
class RendererNoLighting;

// CLASA SINGLETON CAMERA

class Camera;

// ENTITATE

class Entity;

//

class Component;


class Position;
class Scale;
class Rotation;
class Texture;
class Mesh;
class PointLight;
class Render;
class Speed;
class Acceleration;
class Mass;

class TangentSpeed; // DOAR ACUM

// STRUCTURA UNEI TEXTURI

struct TextureStructure;

// ENTITY COMPONENT SYSTEM

const int MAX_ENTITIES = 2048;
const int MAX_COMPONENTS = 64;

using ComponentTypeID = int;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentList = std::array<Component*, MAX_COMPONENTS>;

inline ComponentTypeID InternalGetComponentTypeID()
{
	static ComponentTypeID lastID = 0;

	return lastID++;
}

template<typename T>
inline ComponentTypeID GetComponentTypeID()
{
	static const ComponentTypeID typeID = InternalGetComponentTypeID();

	return typeID;
}

// CLASA SPEED STORAGE (DOAR ACUM)

class SpeedStorage
{
public:

	static SpeedStorage* Get()
	{
		if (SpeedStorage::instance == nullptr)
		{
			SpeedStorage::instance = new SpeedStorage();
		}

		return SpeedStorage::instance;
	}

	void AddEntity(Entity* entity)
	{
		this->entities.emplace_back(entity);
	}

	void RemoveEntity(Entity* entity)
	{
		for (int i = 0; i < this->entities.size(); i++)
		{
			if (this->entities[i] == entity)
			{
				this->entities[i] = this->entities[this->entities.size() - 1];
				this->entities.pop_back();

				return;
			}
		}

		std::cout << "WARNING :: SPEED STORAGE :: COULD NOT REMOVE ENTITY WHICH DID NOT EXIST IN THE FIRST PLACE\n";
	}

	std::vector<Entity*> entities;

private:

	static SpeedStorage* instance;

	SpeedStorage() {};

};

SpeedStorage* SpeedStorage::instance = nullptr;

// CLASA MASS STORAGE (DOAR ACUM)

class MassStorage
{
public:

	static MassStorage* Get()
	{
		if (MassStorage::instance == nullptr)
		{
			MassStorage::instance = new MassStorage();
		}

		return MassStorage::instance;
	}

	void AddEntity(Entity* entity)
	{
		this->entities.emplace_back(entity);
	}

	void RemoveEntity(Entity* entity)
	{
		for (int i = 0; i < this->entities.size(); i++)
		{
			if (this->entities[i] == entity)
			{
				this->entities[i] = this->entities[this->entities.size() - 1];
				this->entities.pop_back();

				return;
			}
		}

		std::cout << "WARNING :: MASS STORAGE :: COULD NOT REMOVE ENTITY WHICH DID NOT EXIST IN THE FIRST PLACE\n";
	}

	std::vector<Entity*> entities;

private:

	static MassStorage* instance;

	MassStorage() {};

};

MassStorage* MassStorage::instance = nullptr;

// CLASA WINDOW MANAGER

class WindowManager
{
public:

	static WindowManager* Get()
	{
		if (WindowManager::instance == nullptr)
		{
			WindowManager::instance = new WindowManager();
		}

		return WindowManager::instance;
	}

	void CreateWindow(int windowWidth, int windowHeight, std::string windowTitle)
	{
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->windowTitle = windowTitle;

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowTitle.c_str(), NULL, NULL);
		//glfwGetPrimaryMonitor();

		glfwMakeContextCurrent(this->window);

		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewInit();

		glfwSwapInterval(1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	void UpdateWindow()
	{
		glfwSwapBuffers(this->window);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void DestroyWindow()
	{
		glfwSetWindowShouldClose(this->window, true);

		glfwDestroyWindow(this->window);

		this->window = nullptr;
	}

	void SetWindowShouldClose(bool state)
	{
		glfwSetWindowShouldClose(this->window, state);
	}

	void SetClearColor(double red, double green, double blue)
	{
		glClearColor(red, green, blue, 1.0);
	}

	void SetClearColor(double red, double green, double blue, double alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	bool ShouldWindowClose()
	{
		return glfwWindowShouldClose(this->window);
	}

	GLFWwindow* GetWindow()
	{
		return this->window;
	}

	int GetWindowWidth()
	{
		return this->windowWidth;
	}

	int GetWindowHeight()
	{
		return this->windowHeight;
	}

private:

	static WindowManager* instance;

	int windowWidth = 1024;
	int windowHeight = 768;

	std::string windowTitle;

	GLFWwindow* window = nullptr;

	WindowManager() {};
};

WindowManager* WindowManager::instance = nullptr;

// CLASA TIME MANAGER

class TimeManager
{
public:

	static TimeManager* Get()
	{
		if (TimeManager::instance == nullptr)
		{
			TimeManager::instance = new TimeManager();
		}

		return TimeManager::instance;
	}

	void UpdateDeltaTime()
	{
		this->previousTime = this->currentTime;
		this->currentTime = glfwGetTime();
		this->deltaTime = this->currentTime - this->previousTime;
	}

	double GetDeltaTime()
	{
		return this->deltaTime;
	}

	double GetCurrentTime()
	{
		return this->currentTime;
	}

private:

	double deltaTime = 0.0;

	double currentTime = 0.0;
	double previousTime = 0.0;

	static TimeManager* instance;

	TimeManager()
	{
		glfwSetTime(0.0);
	}
};

TimeManager* TimeManager::instance = nullptr;

// CLASA CAMERA

class Camera
{
public:

	static Camera* Get()
	{
		if (Camera::instance == nullptr)
		{
			Camera::instance = new Camera();
		}

		return Camera::instance;
	}

	glm::vec3 position;
	glm::vec3 viewDir;
	glm::vec3 normal;

	double fiewOfView;

	double nearClipPlane;
	double farClipPlane;

	double movementSpeed;

	double mouseSpeed;

	double xMouse;
	double yMouse;

	double xAngle;
	double yAngle;

	const double CAMERA_MAX_VIEW_ANGLE = 89.0;

private:

	static Camera* instance;

	Camera()
	{
		this->position = glm::vec3(0.0, 0.0, 90.0);

		this->viewDir = glm::vec3(0.0, 0.0, -1.0);

		this->normal = glm::vec3(0.0, 1.0, 0.0);

		this->fiewOfView = 45.0;

		this->nearClipPlane = 0.1;
		this->farClipPlane = 65536.0;

		this->movementSpeed = 70.0;
		this->mouseSpeed = 10.0;

		this->xMouse = 0.0;
		this->yMouse = 0.0;

		this->xAngle = 0.0;
		this->yAngle = 0.0;
	}
};

Camera* Camera::instance = nullptr;

// CLASA INPUT MANAGER

class InputManager
{
public:

	static InputManager* Get()
	{
		if (InputManager::instance == nullptr)
		{
			InputManager::instance = new InputManager();
		}

		return InputManager::instance;
	}

	void ListenForInput()
	{
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			this->gameEngineShouldStop = true;
		}

		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			Camera::Get()->position += Camera::Get()->viewDir * (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			Camera::Get()->position -= Camera::Get()->viewDir * (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			Camera::Get()->position -= glm::normalize(glm::cross(Camera::Get()->viewDir, Camera::Get()->normal)) * (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			Camera::Get()->position += glm::normalize(glm::cross(Camera::Get()->viewDir, Camera::Get()->normal)) * (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}

		// POT DISPAREA ASTA DOUA
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
		{
			Camera::Get()->position.y -= (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}
		if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
		{
			Camera::Get()->position.y += (float)Camera::Get()->movementSpeed * (float)TimeManager::Get()->GetDeltaTime();
		}

		// LUCRURI LEGATE DE MOUSE AICI

		double newXMouse;
		double newYMouse;

		glfwGetCursorPos(WindowManager::Get()->GetWindow(), &newXMouse, &newYMouse);

		double deltaXMouse = newXMouse - Camera::Get()->xMouse;
		double deltaYMouse = newYMouse - Camera::Get()->yMouse;

		Camera::Get()->xMouse = newXMouse;
		Camera::Get()->yMouse = newYMouse;

		deltaXMouse *= Camera::Get()->mouseSpeed * TimeManager::Get()->GetDeltaTime();
		deltaYMouse *= Camera::Get()->mouseSpeed * TimeManager::Get()->GetDeltaTime();

		Camera::Get()->xAngle += deltaXMouse;
		Camera::Get()->yAngle -= deltaYMouse;

		if (Camera::Get()->yAngle > Camera::Get()->CAMERA_MAX_VIEW_ANGLE)
		{
			Camera::Get()->yAngle = Camera::Get()->CAMERA_MAX_VIEW_ANGLE;
		}
		if (Camera::Get()->yAngle < -Camera::Get()->CAMERA_MAX_VIEW_ANGLE)
		{
			Camera::Get()->yAngle = -Camera::Get()->CAMERA_MAX_VIEW_ANGLE;
		}

		Camera::Get()->viewDir = glm::vec3(cos(glm::radians(Camera::Get()->xAngle)) * cos(glm::radians(Camera::Get()->yAngle)),
										   sin(glm::radians(Camera::Get()->yAngle)),
										   sin(glm::radians(Camera::Get()->xAngle)) * cos(glm::radians(Camera::Get()->yAngle)));

		// SFARSIT MOUSE
	}

	bool ShouldGameEngineStop()
	{
		return this->gameEngineShouldStop;
	}

private:

	static InputManager* instance;

	bool gameEngineShouldStop;

	InputManager()
	{
		this->gameEngineShouldStop = false;
	}
};

InputManager* InputManager::instance = nullptr;

// STRUCTURA TEXTURA

struct TextureStructure
{
	unsigned int ID = 0;

	int width = 0;
	int height = 0;

	int nrChannels = 0;
};

// CLASA TEXTURE MANAGER

class TextureManager
{
public:

	static TextureManager* Get()
	{
		if (TextureManager::instance == nullptr)
		{
			TextureManager::instance = new TextureManager();
		}

		return TextureManager::instance;
	}

	void AddTexture(std::string name, std::string address)
	{
		TextureStructure texture;

		glGenTextures(1, &texture.ID);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = SOIL_load_image(address.c_str(), &texture.width, &texture.height, &texture.nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			this->textures.insert({ name, texture });
		}
		else
		{
			std::cout << "ERROR :: TEXTURE MANAGER :: ADDTEXTURE :: COULD NOT FIND THE TEXTURED NAMED \"" << name << "\" AT THE ADDRESS \"" << address << "\"\n";
		}

		SOIL_free_image_data(data);
	}

	unsigned int GetTextureID(std::string name)
	{
		if (this->textures.find(name) == this->textures.end())
		{
			std::cout << "ERROR :: TEXTURE MANAGER :: GETTEXTUREID :: COULD NOT FIND THE TEXTURE NAMED \"" << name << "\". RETURNING ERROR TEXTURE ID INSTEAD...\n";

			return this->errorTexture.ID;
		}

		return this->textures[name].ID;

	}

	unsigned int GetErrorTextureID()
	{
		return this->errorTexture.ID;
	}

private:

	static TextureManager* instance;

	TextureStructure errorTexture;
	std::unordered_map<std::string, TextureStructure> textures;

	std::string errorTextureAddress = "GameEngine3D/Textures/ErrorTexture/ErrorTexture.png";

	TextureManager()
	{
		glGenTextures(1, &this->errorTexture.ID);
		glBindTexture(GL_TEXTURE_2D, this->errorTexture.ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		unsigned char* data = SOIL_load_image(this->errorTextureAddress.c_str(), &this->errorTexture.width, &this->errorTexture.height, &this->errorTexture.nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->errorTexture.width, this->errorTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR :: TEXTURE MANAGER :: COULD NOT FIND THE ERROR TEXTURE AT THE ADDRESS \"" << this->errorTextureAddress << "\"\n";
		}

		SOIL_free_image_data(data);
	};
};

TextureManager* TextureManager::instance = nullptr;

// CLASA MESH MANAGER

class MeshManager
{
public:

	static MeshManager* Get()
	{
		if (MeshManager::instance == nullptr)
		{
			MeshManager::instance = new MeshManager();
		}

		return MeshManager::instance;
	}

	void ClearMeshData()
	{
		this->meshes.clear();
	}

	void AddMesh(std::string name, std::string address)
	{
		this->auxVertexCoord.clear();
		this->auxNormalCoord.clear();
		this->auxTextureCoord.clear();

		this->aux.clear();

		std::ifstream fileInput;

		fileInput.open(address);

		if (fileInput)
		{
			while (!fileInput.eof())
			{
				char line[258];

				fileInput.getline(line, 257);

				std::strstream input;
				input << line;

				char junk;

				if (line[0] == 'v')
				{
					if (line[1] == 'n')
					{
						input >> junk;
						input >> junk;

						double value;

						input >> value;
						this->auxNormalCoord.push_back(value);
						input >> value;
						this->auxNormalCoord.push_back(value);
						input >> value;
						this->auxNormalCoord.push_back(value);
					}
					else if (line[1] == 't')
					{
						input >> junk;
						input >> junk;

						double value;

						input >> value;
						this->auxTextureCoord.push_back(value);
						input >> value;
						this->auxTextureCoord.push_back(value);
					}
					else if (line[1] == ' ')
					{
						input >> junk;

						double value;

						input >> value;
						this->auxVertexCoord.push_back(value);
						input >> value;
						this->auxVertexCoord.push_back(value);
						input >> value;
						this->auxVertexCoord.push_back(value);
					}
				}
				else if (line[0] == 'f')
				{
					input >> junk;

					int vertexIndex;
					int textureIndex;
					int normalIndex;

					for (int i = 0; i < 3; i++)
					{
						input >> vertexIndex;
						input >> junk;
						input >> textureIndex;
						input >> junk;
						input >> normalIndex;

						vertexIndex--;
						textureIndex--;
						normalIndex--;

						// VERTEX
						this->aux.push_back(this->auxVertexCoord[3 * vertexIndex]);
						this->aux.push_back(this->auxVertexCoord[3 * vertexIndex + 1]);
						this->aux.push_back(this->auxVertexCoord[3 * vertexIndex + 2]);

						// NORMAL
						this->aux.push_back(this->auxNormalCoord[3 * normalIndex]);
						this->aux.push_back(this->auxNormalCoord[3 * normalIndex + 1]);
						this->aux.push_back(this->auxNormalCoord[3 * normalIndex + 2]);

						// TEXTURE
						this->aux.push_back(this->auxTextureCoord[2 * textureIndex]);
						this->aux.push_back(this->auxTextureCoord[2 * textureIndex + 1]);
					}
				}
			}
		}
		else
		{
			std::cout << "ERROR :: MESH MANAGER :: ADDMESH :: COULD NOT FIND MESH AT THE ADDRESS \"" << address << "\"\n";

			fileInput.close();

			return;
		}

		fileInput.close();

		this->meshes.insert({ name, this->aux });
	}

	void RemoveMesh(std::string name)
	{
		this->meshes.erase(name);
	}

	std::vector<double>* GetMesh(std::string name)
	{
		if (this->meshes.find(name) == this->meshes.end())
		{
			std::cout << "ERROR :: MESH MANAGER :: GETMESH :: COULD NOT FIND THE MESH NAMED \"" << name << "\". RETURNING NULL POINTER INSTEAD...\n";

			return nullptr;
		}

		return &this->meshes[name];

	}

private:

	static MeshManager* instance;

	std::unordered_map<std::string, std::vector<double>> meshes;

	std::vector<double> auxVertexCoord;
	std::vector<double> auxNormalCoord;
	std::vector<double> auxTextureCoord;

	std::vector<double> aux;

	MeshManager() {};
};

MeshManager* MeshManager::instance = nullptr;

// CLASA RENDERER WITH LIGHTING

class RendererWithLighting
{
public:

	RendererWithLighting(std::string vertexShaderAddress, std::string fragmentShaderAddress)
	{

		std::ifstream fileInput;
		std::string line;

		fileInput.open(vertexShaderAddress);

		if (fileInput)
		{
			while (!fileInput.eof())
			{
				getline(fileInput, line);

				this->vertexShaderCode += line;
				this->vertexShaderCode += "\n";
			}

			this->vertexShaderCode += "\0";
		}
		else
		{
			std::cout << "ERROR :: RENDERER WITH LIGHTING :: COULD NOT FIND ANY FILE AT THE ADDRESS \"" << vertexShaderAddress << "\" WHICH CONTAINS THE VERTEX SHADER CODE\n";
		}

		fileInput.close();

		fileInput.open(fragmentShaderAddress);

		if (fileInput)
		{
			while (!fileInput.eof())
			{
				getline(fileInput, line);

				this->fragmentShaderCode += line;
				this->fragmentShaderCode += "\n";
			}

			this->fragmentShaderCode += "\0";
		}
		else
		{
			std::cout << "ERROR :: RENDERER WITH LIGHTING :: COULD NOT FIND ANY FILE AT THE ADDRESS \"" << fragmentShaderAddress << "\" WHICH CONTAINS THE FRAGMENT SHADER CODE\n";
		}

		fileInput.close();

		const char* vertexCstr = (this->vertexShaderCode).c_str();
		const char* fragmentCstr = (this->fragmentShaderCode).c_str();

		this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(this->vertexShaderID, 1, &vertexCstr, 0);
		glShaderSource(this->fragmentShaderID, 1, &fragmentCstr, 0);

		glCompileShader(this->vertexShaderID);
		glCompileShader(this->fragmentShaderID);

		this->programID = glCreateProgram();
		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);

		glLinkProgram(this->programID);

		//glValidateProgram(this->programID);

		glUseProgram(this->programID);

		//AICI MATRICI
		this->modelMatrixPath = glGetUniformLocation(this->programID, "modelMatrix");
		this->viewMatrixPath = glGetUniformLocation(this->programID, "viewMatrix");
		this->projectionMatrixPath = glGetUniformLocation(this->programID, "projectionMatrix");
		//

		this->cameraPosPath = glGetUniformLocation(this->programID, "cameraPos");
		this->lightPosPath = glGetUniformLocation(this->programID, "lightPos");

		this->texturePath = glGetUniformLocation(this->programID, "texture0");
		glUniform1i(this->texturePath, 0);

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(0);
	}

	~RendererWithLighting()
	{
		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);

		glDeleteProgram(this->programID);
	}

	inline void StartUsing()
	{
		glUseProgram(this->programID);
	}

	inline void StopUsing()
	{
		glUseProgram(0);
	}

	int modelMatrixPath;
	int viewMatrixPath;
	int projectionMatrixPath;

	int cameraPosPath;
	int lightPosPath;

private:

	int programID;

	int vertexShaderID;
	int fragmentShaderID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	int texturePath;
};

// CLASA RENDERER NO LIGHTING

class RendererNoLighting
{
public:

	RendererNoLighting(std::string vertexShaderAddress, std::string fragmentShaderAddress)
	{

		std::ifstream fileInput;
		std::string line;

		fileInput.open(vertexShaderAddress);

		if (fileInput)
		{
			while (!fileInput.eof())
			{
				getline(fileInput, line);

				this->vertexShaderCode += line;
				this->vertexShaderCode += "\n";
			}

			this->vertexShaderCode += "\0";
		}
		else
		{
			std::cout << "ERROR :: RENDERER NO LIGHTING :: COULD NOT FIND ANY FILE AT THE ADDRESS \"" << vertexShaderAddress << "\" WHICH CONTAINS THE VERTEX SHADER CODE\n";
		}

		fileInput.close();

		fileInput.open(fragmentShaderAddress);

		if (fileInput)
		{
			while (!fileInput.eof())
			{
				getline(fileInput, line);

				this->fragmentShaderCode += line;
				this->fragmentShaderCode += "\n";
			}

			this->fragmentShaderCode += "\0";
		}
		else
		{
			std::cout << "ERROR :: RENDERER NO LIGHTING :: COULD NOT FIND ANY FILE AT THE ADDRESS \"" << fragmentShaderAddress << "\" WHICH CONTAINS THE FRAGMENT SHADER CODE\n";
		}

		fileInput.close();

		const char* vertexCstr = (this->vertexShaderCode).c_str();
		const char* fragmentCstr = (this->fragmentShaderCode).c_str();

		this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(this->vertexShaderID, 1, &vertexCstr, 0);
		glShaderSource(this->fragmentShaderID, 1, &fragmentCstr, 0);

		glCompileShader(this->vertexShaderID);
		glCompileShader(this->fragmentShaderID);

		this->programID = glCreateProgram();
		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);

		glLinkProgram(this->programID);

		//glValidateProgram(this->programID);

		glUseProgram(this->programID);

		//AICI MATRICI
		this->modelMatrixPath = glGetUniformLocation(this->programID, "modelMatrix");
		this->viewMatrixPath = glGetUniformLocation(this->programID, "viewMatrix");
		this->projectionMatrixPath = glGetUniformLocation(this->programID, "projectionMatrix");
		//

		this->texturePath = glGetUniformLocation(this->programID, "texture0");
		glUniform1i(this->texturePath, 0);

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(0);
	}

	~RendererNoLighting()
	{
		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);

		glDeleteProgram(this->programID);
	}

	inline void StartUsing()
	{
		glUseProgram(this->programID);
	}

	inline void StopUsing()
	{
		glUseProgram(0);
	}

	int modelMatrixPath;
	int viewMatrixPath;
	int projectionMatrixPath;

private:

	int programID;

	int vertexShaderID;
	int fragmentShaderID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	int texturePath;

};

// CLASA ENTITY

class Entity
{
public:

	Entity()
	{
		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			this->componentBitset[i] = false;
			this->componentList[i] = nullptr;
		}
	}

	virtual ~Entity()
	{
		if (this->HasComponent<Speed>()) // DOAR ACUM
		{
			SpeedStorage::Get()->RemoveEntity(this);
		}
		if (this->HasComponent<Mass>()) // DOAR ACUM
		{
			MassStorage::Get()->RemoveEntity(this);
		}

		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			if (this->componentBitset[i])
			{
				delete this->componentList[i];

				this->componentBitset[i] = false;
			}
		}
	}

	template<typename T>
	inline void AddComponent(T* component)
	{
		this->componentBitset[GetComponentTypeID<T>()] = true;
		this->componentList[GetComponentTypeID<T>()] = component;

		component->entity = this;

		// ASTA DOAR ACUM CA AVEM APLICATIE CU PLANETE
		if (GetComponentTypeID<T>() == GetComponentTypeID<Speed>())
		{
			SpeedStorage::Get()->AddEntity(this);
		}
		// ASTA DOAR ACUM CA AVEM APLICATIE CU PLANETE
		if (GetComponentTypeID<T>() == GetComponentTypeID<Mass>())
		{
			MassStorage::Get()->AddEntity(this);
		}
	}

	template<typename T>
	inline void DeleteComponent()
	{

		if (this->componentBitset[GetComponentTypeID<T>()])
		{
			delete this->componentList[GetComponentTypeID<T>()];

			this->componentBitset[GetComponentTypeID<T>()] = false;
			this->componentList[GetComponentTypeID<T>()] = nullptr;

			if (GetComponentTypeID<T>() == GetComponentTypeID<Speed>) // DOAR ACUM
			{
				SpeedStorage::Get()->RemoveEntity(this);
			}
			if (GetComponentTypeID<T>() == GetComponentTypeID<Mass>) // DOAR ACUM
			{
				MassStorage::Get()->RemoveEntity(this);
			}
		}
		else
		{
			std::cout << "WARNING :: ENTITY :: DELETECOMPONENT :: COULD NOT DELETE A COMPONENT WHICH DID NOT EXIST IN THE FIRST PLACE\n";
		}
	}

	template<typename T>
	inline T* GetComponent() const
	{
		if (!this->componentBitset[GetComponentTypeID<T>()])
		{
			std::cout << "WARNING :: ENTITY :: GETCOMPONENT :: UNCREATED COMPONENT WAS DEMANDED. RETURNING NULL POINTER...\n";

			return nullptr;
		}

		return static_cast<T*>(this->componentList[GetComponentTypeID<T>()]);
	}

	template<typename T>
	inline bool HasComponent() const
	{
		return this->componentBitset[GetComponentTypeID<T>()];
	}

private:

	ComponentBitset componentBitset;
	ComponentList componentList;
};

// CLASA COMPONENT

class Component
{
public:

	Component() {};
	virtual ~Component() {};

	Entity* entity = nullptr;

private:

};

// CLASELE COMPONENTELOR CE SE MOSTENESC DIN COMPONENTA DE BAZA, VIRTUALA

class Position : public Component
{
public:

	Position(double x = 0.0, double y = 0.0, double z = 0.0)
	{
		this->position = glm::vec3(x, y, z);
	}

	glm::vec3 position;

private:

};

class Scale : public Component
{
public:

	Scale(double scaleX = 1.0, double scaleY = 1.0, double scaleZ = 1.0)
	{
		this->scale = glm::vec3(scaleX, scaleY, scaleZ);
	}

	glm::vec3 scale;

private:

};

class Rotation : public Component
{
public:

	Rotation(double rotationX = 1.0, double rotationY = 1.0, double rotationZ = 1.0, double rotationSpeed = 0.0, double startRotationX = 1.0, double startRotationY = 1.0, double startRotationZ = 1.0, double startAngle = 0.0)
	{
		this->rotation = glm::vec3(rotationX, rotationY, rotationZ);
		this->startRotation = glm::vec3(startRotationX, startRotationY, startRotationZ);

		this->startAngle = startAngle;

		this->rotationSpeed = rotationSpeed;
	}

	glm::vec3 rotation;
	glm::vec3 startRotation;

	double startAngle;

	double rotationSpeed;

private:

};

class Texture : public Component
{
public:

	Texture()
	{
		this->currentTextureID = 0;
	}

	unsigned int currentTextureID;
		
private:

};

class Mesh : public Component
{
public:

	Mesh()
	{
		this->currentMesh = nullptr;
	}

	std::vector<double>* currentMesh;

private:

};

class PointLight : public Component
{
public:

	PointLight(double x = 0.0, double y = 0.0, double z = 0.0)
	{
		this->position = glm::vec3(x, y, z);
	}

	glm::vec3 position;

private:

};

class Render : public Component
{
public:

	Render()
	{
		glGenVertexArrays(1, &this->VAOID);
		glGenBuffers(1, &this->VBOID);

		glBindVertexArray(this->VAOID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOID);

		// VARFURI, NORMALE, TEXTURI

		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double)));
		glEnableVertexAttribArray(2);
	}

	void Draw(RendererWithLighting* renderer)
	{
		bool ok = true;

		if (!this->entity->HasComponent<Position>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO POSITION COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		if (!this->entity->HasComponent<Scale>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO SCALE COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		if (!this->entity->HasComponent<Rotation>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO ROTATION COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}

		if (!this->entity->HasComponent<Texture>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO TEXTURE COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		else if(this->entity->GetComponent<Texture>()->currentTextureID == 0)
		{
			std::cout << "WARNING :: RENDER COMPONENT :: DRAW :: THERE IS NO TEXTURE TO USE FOR DRAWING. SELECTING THE ERROR TEXTURE INSTEAD AND ATTEMPTING DRAWING...\n";

			entity->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetErrorTextureID();
		}

		if (!this->entity->HasComponent<Mesh>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO MESH COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		else if (this->entity->GetComponent<Mesh>()->currentMesh == nullptr)
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO MESH ATTACHED TO THE MESH COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}

		if (!ok) return;

		renderer->StartUsing();

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(Camera::Get()->fiewOfView), (double)WindowManager::Get()->GetWindowWidth() / WindowManager::Get()->GetWindowHeight(), Camera::Get()->nearClipPlane, Camera::Get()->farClipPlane);
		glm::mat4 viewMatrix = glm::lookAt(Camera::Get()->position, Camera::Get()->position + Camera::Get()->viewDir, Camera::Get()->normal);

		glm::mat4 modelMatrix = glm::mat4(1.0);

		modelMatrix = glm::translate(modelMatrix, this->entity->GetComponent<Position>()->position);
		modelMatrix = glm::rotate(modelMatrix, (float)this->entity->GetComponent<Rotation>()->startAngle, this->entity->GetComponent<Rotation>()->startRotation);
		modelMatrix = glm::rotate(modelMatrix, (float)this->entity->GetComponent<Rotation>()->rotationSpeed * (float)TimeManager::Get()->GetCurrentTime(), this->entity->GetComponent<Rotation>()->rotation);
		modelMatrix = glm::scale(modelMatrix, this->entity->GetComponent<Scale>()->scale);

		glUniformMatrix4fv(renderer->projectionMatrixPath, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(renderer->viewMatrixPath, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(renderer->modelMatrixPath, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		//glUniform3fv(renderer->cameraPosPath, sizeof(Camera::Get()->position), glm::value_ptr(Camera::Get()->position));
		glUniform3f(renderer->cameraPosPath, Camera::Get()->position.x, Camera::Get()->position.y, Camera::Get()->position.z);

		if (this->entity->HasComponent<PointLight>())
		{
			//glUniform3fv(renderer->lightPosPath, sizeof(this->entity->GetComponent<PointLight>()->position), glm::value_ptr(this->entity->GetComponent<PointLight>()->position));
			glUniform3f(renderer->lightPosPath, this->entity->GetComponent<PointLight>()->position.x, this->entity->GetComponent<PointLight>()->position.y, this->entity->GetComponent<PointLight>()->position.z);
		}
		else
		{
			//glUniform3fv(renderer->lightPosPath, sizeof(this->entity->GetComponent<Position>()->position), glm::value_ptr(this->entity->GetComponent<Position>()->position));
			glUniform3f(renderer->lightPosPath, this->entity->GetComponent<Position>()->position.x, this->entity->GetComponent<Position>()->position.y, this->entity->GetComponent<Position>()->position.z);
		}

		glBindVertexArray(this->VAOID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->entity->GetComponent<Mesh>()->currentMesh->size(), &(this->entity->GetComponent<Mesh>()->currentMesh->front()), GL_STATIC_DRAW);// HABAR NU AM CE FAC

		glBindTexture(GL_TEXTURE_2D, this->entity->GetComponent<Texture>()->currentTextureID);

		glDrawArrays(GL_TRIANGLES, 0, this->entity->GetComponent<Mesh>()->currentMesh->size() / 8);
	}

	void Draw(RendererNoLighting* renderer)
	{
		bool ok = true;

		if (!this->entity->HasComponent<Position>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO POSITION COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		if (!this->entity->HasComponent<Scale>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO SCALE COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		if (!this->entity->HasComponent<Rotation>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO ROTATION COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}

		if (!this->entity->HasComponent<Texture>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO TEXTURE COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		else if (this->entity->GetComponent<Texture>()->currentTextureID == 0)
		{
			std::cout << "WARNING :: RENDER COMPONENT :: DRAW :: THERE IS NO TEXTURE TO USE FOR DRAWING. SELECTING THE ERROR TEXTURE INSTEAD AND ATTEMPTING DRAWING...\n";

			entity->GetComponent<Texture>()->currentTextureID = TextureManager::Get()->GetErrorTextureID();
		}

		if (!this->entity->HasComponent<Mesh>())
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO MESH COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}
		else if (this->entity->GetComponent<Mesh>()->currentMesh == nullptr)
		{
			std::cout << "ERROR :: RENDER COMPONENT :: DRAW :: ENTITY HAS NO MESH ATTACHED TO THE MESH COMPONENT. RETURNING WITHOUT DRAWING...\n";

			ok = false;
		}

		if (!ok) return;

		renderer->StartUsing();

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(Camera::Get()->fiewOfView), (double)WindowManager::Get()->GetWindowWidth() / WindowManager::Get()->GetWindowHeight(), Camera::Get()->nearClipPlane, Camera::Get()->farClipPlane);
		glm::mat4 viewMatrix = glm::lookAt(Camera::Get()->position, Camera::Get()->position + Camera::Get()->viewDir, Camera::Get()->normal);

		glm::mat4 modelMatrix = glm::mat4(1.0);

		modelMatrix = glm::translate(modelMatrix, this->entity->GetComponent<Position>()->position);
		modelMatrix = glm::rotate(modelMatrix, (float)(this->entity->GetComponent<Rotation>()->startAngle + this->entity->GetComponent<Rotation>()->rotationSpeed * TimeManager::Get()->GetCurrentTime()), this->entity->GetComponent<Rotation>()->rotation);
		modelMatrix = glm::scale(modelMatrix, this->entity->GetComponent<Scale>()->scale);

		glUniformMatrix4fv(renderer->projectionMatrixPath, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(renderer->viewMatrixPath, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(renderer->modelMatrixPath, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glBindVertexArray(this->VAOID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->entity->GetComponent<Mesh>()->currentMesh->size(), &(this->entity->GetComponent<Mesh>()->currentMesh->front()), GL_STATIC_DRAW);// HABAR NU AM CE FAC

		glBindTexture(GL_TEXTURE_2D, this->entity->GetComponent<Texture>()->currentTextureID);

		glDrawArrays(GL_TRIANGLES, 0, this->entity->GetComponent<Mesh>()->currentMesh->size() / 8);
	}

	unsigned int VAOID;
	unsigned int VBOID;

private:

};

class Speed : public Component
{
public:

	Speed(double speedX = 0.0, double speedY = 0.0, double speedZ = 0.0)
	{
		this->speed = glm::vec3(speedX, speedY, speedZ);
	}

	glm::vec3 speed;

private:

};

class Acceleration : public Component
{
public:

	Acceleration(double accelerationX = 0.0, double accelerationY = 0.0, double accelerationZ = 0.0)
	{
		this->acceleration = glm::vec3(accelerationX, accelerationY, accelerationZ);
	}

	glm::vec3 acceleration;

private:

};

class Mass : public Component
{
public:

	Mass(double mass = 0.0)
	{
		this->mass = mass;
	}

	double mass;

private:

};

class TangentSpeed : public Component // DOAR ACUM
{
public:

	TangentSpeed(double speed = 0.0)
	{
		this->speed = speed;
	}

	double speed;

private:

};

// CLASA SPEED MANAGER (CE VA DISPAREA, E DOAR ACUM)

class SpeedManager
{
public:

	static SpeedManager* Get()
	{
		if (SpeedManager::instance == nullptr)
		{
			SpeedManager::instance = new SpeedManager();
		}

		return SpeedManager::instance;
	}

	void UpdateSpeed()
	{
		for (int i = 0; i < SpeedStorage::Get()->entities.size(); i++)
		{
			if (SpeedStorage::Get()->entities[i]->HasComponent<Position>())
			{
				SpeedStorage::Get()->entities[i]->GetComponent<Position>()->position += SpeedStorage::Get()->entities[i]->GetComponent<Speed>()->speed * (float)TimeManager::Get()->GetDeltaTime();
			}

			if (SpeedStorage::Get()->entities[i]->HasComponent<Acceleration>())
			{
				SpeedStorage::Get()->entities[i]->GetComponent<Speed>()->speed += SpeedStorage::Get()->entities[i]->GetComponent<Acceleration>()->acceleration * (float)TimeManager::Get()->GetDeltaTime();
			}
		}
	}

private:

	static SpeedManager* instance;

	SpeedManager() {};
};

SpeedManager* SpeedManager::instance = nullptr;

// CLASA MASS MANAGER (CE VA DISPAREA, E DOAR ACUM)

class MassManager
{
public:

	static MassManager* Get()
	{
		if (MassManager::instance == nullptr)
		{
			MassManager::instance = new MassManager();
		}

		return MassManager::instance;
	}

	void UpdateMass()
	{
		for (int i = 0; i < MassStorage::Get()->entities.size(); i++)
		{
			if (!MassStorage::Get()->entities[i]->HasComponent<Acceleration>()) continue;

			MassStorage::Get()->entities[i]->GetComponent<Acceleration>()->acceleration = glm::vec3(0.0, 0.0, 0.0);
		}

		for (int i = 0; i < MassStorage::Get()->entities.size(); i++)
		{
			if (!MassStorage::Get()->entities[i]->HasComponent<Position>()) continue;
			if (!MassStorage::Get()->entities[i]->HasComponent<Acceleration>()) continue;

			for (int j = i + 1; j < MassStorage::Get()->entities.size(); j++)
			{
				if (!MassStorage::Get()->entities[j]->HasComponent<Position>()) continue;
				if (!MassStorage::Get()->entities[j]->HasComponent<Acceleration>()) continue;

				// AICI E ATRACTIA GRAVITATIONALA (O APROXIMAM RAU DE TOT DOAR SA MEARGA PENTRU CE VREM)

				glm::vec3 distance = MassStorage::Get()->entities[i]->GetComponent<Position>()->position - MassStorage::Get()->entities[j]->GetComponent<Position>()->position;

				if (length(distance) <= this->EPSILON) continue;

				glm::vec3 normDistance = normalize(distance);

				double force = (MassStorage::Get()->entities[i]->GetComponent<Mass>()->mass * MassStorage::Get()->entities[j]->GetComponent<Mass>()->mass) / (1.0 * length(distance) * length(distance));

				MassStorage::Get()->entities[i]->GetComponent<Acceleration>()->acceleration -= (float)force * normDistance / (float)MassStorage::Get()->entities[i]->GetComponent<Mass>()->mass * (float)TimeManager::Get()->GetDeltaTime();
				MassStorage::Get()->entities[j]->GetComponent<Acceleration>()->acceleration += (float)force * normDistance / (float)MassStorage::Get()->entities[j]->GetComponent<Mass>()->mass * (float)TimeManager::Get()->GetDeltaTime();
			}
		}
	}

private:

	static MassManager* instance;

	const double EPSILON = 1.0;

	MassManager() {};

};

MassManager* MassManager::instance = nullptr;

// CLASA GAME ENGINE

class GameEngine
{
public:

	static GameEngine* Get()
	{
		if (GameEngine::instance == nullptr)
		{
			GameEngine::instance = new GameEngine();
		}

		return GameEngine::instance;
	}

	void Start(int windowWidth, int windowHeight, std::string gameTitle)
	{
		WindowManager::Get()->CreateWindow(windowWidth, windowHeight, gameTitle);

		TimeManager::Get();
	}

	void Update()
	{
		WindowManager::Get()->UpdateWindow();

		TimeManager::Get()->UpdateDeltaTime();

		InputManager::Get()->ListenForInput();

		SpeedManager::Get()->UpdateSpeed(); // DOAR ACUM

		MassManager::Get()->UpdateMass(); // DOAR ACUM

		if (InputManager::Get()->ShouldGameEngineStop())
		{
			this->isRunning = false;
		}
	}

	void Stop()
	{
		WindowManager::Get()->SetWindowShouldClose(true);
		WindowManager::Get()->DestroyWindow();

		this->isRunning = false;
	}

	bool ShouldGameEngineStop()
	{
		return !isRunning;
	}

private:

	static GameEngine* instance;

	bool isRunning;

	GameEngine()
	{
		this->isRunning = true;
	}

	GameEngine(const GameEngine&) = delete;
};

GameEngine* GameEngine::instance = nullptr;