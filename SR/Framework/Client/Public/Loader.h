#pragma once

#include "Client_Defines.h"
#include "Base.h"

NS_BEGIN(Engine)
class CGameInstance;
NS_END

NS_BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	bool_t isFinished() const { return m_isFinished; }
	HRESULT	Loading();

#ifdef _DEBUG
public:
	void Print_Text();
#endif

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = { nullptr };
	LEVEL				m_eNextLevelID = { LEVEL::END };
	tchar_t				m_szLoadingText[MAX_PATH] = {};
	bool_t				m_isFinished = { true };
	CGameInstance* m_pGameInstance = { nullptr };

private:
	HANDLE				m_hThread = { };
	CRITICAL_SECTION	m_CriticalSection = { };

private:
	HRESULT Loading_For_LogoLV();
	HRESULT Loading_For_GamePlayLV();

public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID);
	virtual void Free();

};

NS_END