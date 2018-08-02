#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class SceneObject;
	class Scene : public std::enable_shared_from_this<Scene>
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		//Scene(const std::string& name);
		void Add(const std::shared_ptr<GameObject>& object);
		void Update(const float deltaTime);
		void Render() const;
		std::vector < std::shared_ptr<GameObject>> GetObjects() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name{};
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int idCounter; 
	};

}
