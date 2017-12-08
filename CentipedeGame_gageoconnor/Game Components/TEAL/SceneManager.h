// SceneManager.h
// Andre Berthiaume, June 2012
//
// Controls which scene is active and deals with storage/retrieval of past scenes

#ifndef _SceneManager
#define _SceneManager

// Forward declarations
class Scene;

class SceneManager
{
private:
	static SceneManager* mgrInstance;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager() = default;

	static SceneManager& Instance()
	{
		if ( ! mgrInstance)
			mgrInstance = new SceneManager;

		return *mgrInstance;
	}

	Scene* currentScene;
	Scene* nextScene;

	void InternalProcessOneFrame();

public:
	static void SetStartScene(Scene* sc);
	static void Terminate();

	static void ProcessOneFrame();

	static Scene* GetCurrentScene();
	static void ChangeScene( Scene* sc);
};

#endif _SceneManager