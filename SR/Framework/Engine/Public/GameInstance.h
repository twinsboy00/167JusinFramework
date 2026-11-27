#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance();

public:
	HRESULT	Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut);
	void Update_Engine(f32_t fTimeDelta);
	HRESULT Draw();
	void Clear_Resources(uint32_t iClearLevelIndex);

#pragma region GRAPHIC_DEVICE
public: /* For. Graphic_Device */
	void Render_Begin(D3DXCOLOR Color = D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
	void Render_End(HWND hWnd = 0);
#pragma endregion

#pragma region LEVEL_MANAGER
	HRESULT Change_Level(uint32_t iCurrentLevelIndx, class CLevel* pNewLevel);
#pragma endregion

#pragma region PROTOTYPE_MANAGER
	HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, class CPrototype* pPrototype);
	class CPrototype* Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg);
#pragma endregion

#pragma region OBJECT_MANAGER
	HRESULT Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLevelIndex, const wstring_t& strLayerTag, void* pArg = nullptr);
#pragma endregion

private:
	class CGraphic_Device* m_pGraphic_Device = { nullptr };
	class CLevel_Manager* m_pLevel_Manager = { nullptr };
	class CPrototype_Manager* m_pPrototype_Manager = { nullptr };
	class CObject_Manager* m_pObject_Manager = { nullptr };
	class CRenderer* m_pRenderer = { nullptr };


public:
	void Release_Engine();
	virtual void Free() override;

};

NS_END