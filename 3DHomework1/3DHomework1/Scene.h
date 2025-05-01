#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"



class CBaseScene
{
public:
	CBaseScene();
	virtual ~CBaseScene();
private:
	int							m_nObjects = 0;
	int							level{ 2 };
	CGameObject** m_ppObjects = NULL;

	CWallsObject* m_pWallsObject = NULL;

	CPlayer* m_pPlayer = NULL;
public:
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
	CGameObject** m_ppObjects = NULL;

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();

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

#ifdef _WITH_DRAW_AXIS
	CGameObject*				m_pWorldAxis = NULL;
#endif

public:
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

