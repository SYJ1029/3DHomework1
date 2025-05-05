#pragma once

#include "Camera.h"
#include "GameObject.h"
#include "Player.h"



class CBaseScene
{
public:
	CBaseScene();
	virtual ~CBaseScene();
private:
	int							m_nObjects = 0;
	CGameObject**				m_ppObjects = NULL;

	CWallsObject*				m_pWallsObject = NULL;
protected:
	int							level = 0;
	CPlayer*					m_pPlayer = NULL;
public:
	BOOL						levelFlag = false;

	void Setlevel(int newLevel);
	CBaseScene* SetScene();
	int GetLevel();

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void CheckObjectByObjectCollisions();
	virtual void CheckObjectByWallCollisions();
	virtual void CheckPlayerByWallCollision();
	virtual void CheckObjectByBulletCollisions();

	virtual void SetPlayer(CPlayer* pPlayer);

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CStartScene : public CBaseScene
{
public:
	CStartScene();
	virtual ~CStartScene();
private:
	int							m_nObjects = 0;
	CGameObject**				m_ppObjects = NULL;
	CExplosiveObject*			pExplosiveObject = NULL;

public:
	BOOL						levelFlag = false;

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);


	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMenuScene : public CBaseScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();
private:
	int							m_nObjects = 0;
	CGameObject**				m_ppObjects = NULL;
public:
	BOOL						levelFlag = false;

	void CheckLevel(CGameObject*);

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

/// //////////////////////////////////////////////////////////////////////////////////////////////////////////

class CLevel1Scene : public CBaseScene
{
public:
	CLevel1Scene();
	virtual ~CLevel1Scene();
private:
	int							m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;

	CWallsObject* m_pWallsObject = NULL;

	CPlayer* m_pPlayer = NULL;

#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif
protected:
	std::list<std::pair<CVertex*, CVertex*>> lines;

public:
	BOOL						levelFlag = false;


	void MoveByLine(std::list<std::pair<CVertex*, CVertex*>>&);

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();

	virtual void SetPlayer(CPlayer* pPlayer);

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CTankScene : public CBaseScene
{
public:
	CTankScene();
	virtual ~CTankScene();

private:
	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;

	CWallsObject*				m_pWallsObject = NULL;

	CPlayer*					m_pPlayer = NULL;

	CGameObject* m_pLockedObject = NULL;

#ifdef _WITH_DRAW_AXIS
	CGameObject*				m_pWorldAxis = NULL;
#endif

public:
	BOOL						levelFlag = false;

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();

	virtual void SetPlayer(CPlayer* pPlayer);

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};



///////////////////////////////////////////

