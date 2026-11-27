#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Update(f32_t fTimeDelta);
	virtual HRESULT	Render();

protected : 
	LPDIRECT3DDEVICE9		m_pGraphic_Device = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };


public:
	virtual void Free();
};

NS_END
