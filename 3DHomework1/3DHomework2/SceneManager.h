#pragma once

#include "stdafx.h"



template<class Scene>
class CSceneManager
{
public:
	CSceneManager() { sceneList.reserve(4); }
	~CSceneManager() {}
private:
	std::vector<std::shared_ptr<Scene>> sceneList;
public:
	std::shared_ptr<Scene> m_pScene;

	void push_back(std::shared_ptr<Scene>& newScene) { sceneList.push_back(newScene); }
	void emplace_back(std::shared_ptr<Scene>&& newScene) { sceneList.emplace_back(newScene); }

	void ChangeScene(UINT id) {
		switch (id) {
		case S_TITLE:
		case S_MENU:
		case S_ROLLERCOSTER:
		case S_TANK:
			m_pScene = sceneList[id - S_TITLE];
			break;
		}
	}

	void ReleaseScene() { sceneList.clear(); }


};

