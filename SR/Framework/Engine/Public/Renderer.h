#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CRenderer final : public CBase
{
private:
	CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device);
public:
	virtual ~CRenderer() = default;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, class CGameObject* pRenderObject);
	HRESULT Draw();

private:
	LPDIRECT3DDEVICE9						m_pGraphic_Device = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };
	list<class CGameObject*>				m_RenderObjects[ETOUI(RENDERGROUP::END)];

private:
	HRESULT Render_Priority();
	HRESULT Render_NonBlend();
	HRESULT Render_Blend();
	HRESULT Render_UI();


public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

NS_END