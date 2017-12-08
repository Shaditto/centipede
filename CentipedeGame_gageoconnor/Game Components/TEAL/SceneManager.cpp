// SceneManager.h
// Andre Berthiaume, June 2012
//
// Controls which scene is active and (in the future) deals with storage/retrieval of past scenes

#include "SceneManager.h"
#include "Scene.h"

using namespace std;

SceneManager* SceneManager::mgrInstance = NULL;


SceneManager::SceneManager()
{
	currentScene = NULL;
	nextScene = NULL;
}

void SceneManager::SetStartScene(Scene* sc)
{ 
	Instance().currentScene = NULL; 
	Instance().nextScene = sc;
}

void SceneManager::Terminate()
{
	// Test for the possibility of terminating right at a scene change
	if ( Instance().currentScene != Instance().nextScene)
	{
		Instance().nextScene->FinalCleanUp();
		delete Instance().nextScene;  
	}

	Instance().currentScene->FinalCleanUp();
	delete Instance().currentScene;
}

void SceneManager::InternalProcessOneFrame()
{
	// first check if there a scene change request.
	if ( currentScene != nextScene)
	{
	 	if (currentScene != nullptr) currentScene->FinalCleanUp();
		delete currentScene;
		currentScene = nextScene;
		currentScene->Initialize();
	}

	currentScene->ProcessOneFrame();
}

void SceneManager::ProcessOneFrame()
{
	Instance().InternalProcessOneFrame();
}

void SceneManager::ChangeScene( Scene* sc)
{
	Instance().nextScene = sc;
}

Scene* SceneManager::GetCurrentScene(){ return Instance().currentScene;}
