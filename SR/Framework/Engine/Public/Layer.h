#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CLayer final : public CBase
{
private:
	CLayer();
public:
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObject(class CGameObject* pGameObejct);
	void Update(f32_t fTimeDelta);

private:
	list<class CGameObject*>				m_GameObjects;

public:
	static CLayer* Create();
	virtual void Free() override;
};

NS_END