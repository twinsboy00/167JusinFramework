#pragma once

/*		클래스 정의 방식		*/

/*
class C클래스 이름 final(자식이 없는 객체 클래스) or abstract(자식이 있을 추상화 클래스) 추상화
{
private: or protected:
	생성자,
public:
	소멸자,




}


*/


#include "Client_Defines.h"
#include "Base.h"

NS_BEGIN(Engine)
class CGameInstance;
NS_END

NS_BEGIN(Client)

class CMainApp final : public CBase
{
private:
	CMainApp();
	~CMainApp() = default;

public:
	HRESULT Initialize();
	void Update(float fTimeDelta);
	HRESULT Render();
	
private:
	CGameInstance*		m_pGameInstance = { nullptr };
	LPDIRECT3DDEVICE9	m_pGraphic_Device = { nullptr };

private:
	HRESULT Start_Level(LEVEL eStartLevel);

public:
	static CMainApp* Create();
	virtual void Free() override;
};

NS_END
