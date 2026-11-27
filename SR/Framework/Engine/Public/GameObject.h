#pragma once

#include "Prototype.h"

NS_BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CPrototype
{
	protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Update(f32_t fTimeDelta);
	virtual HRESULT Render();

protected:
	class CGameInstance* m_pGameInstance = { nullptr };

public:
	virtual CPrototype* Clone(void* pArg) = 0;
	virtual void Free() override;
};

NS_END