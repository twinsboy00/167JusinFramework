#include "GameInstance.h"
#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Prototype_Manager.h"
#include "Prototype.h"
#include "Object_Manager.h"
#include "Renderer.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{

}

CGameInstance::~CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut)
{
	m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, ppOut);
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
	if (nullptr == m_pPrototype_Manager)
		return E_FAIL;

	m_pObject_Manager = CObject_Manager::Create(EngineDesc.iNumLevels);
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	m_pRenderer = CRenderer::Create(*ppOut);
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Update_Engine(f32_t fTimeDelta)
{
	m_pObject_Manager->Update(fTimeDelta);

	m_pLevel_Manager->Update(fTimeDelta);
}

HRESULT CGameInstance::Draw()
{
	m_pRenderer->Draw();

	m_pLevel_Manager->Render();

	return S_OK;
}

void CGameInstance::Clear_Resources(uint32_t iClearLevelIndex)
{
	m_pObject_Manager->Clear(iClearLevelIndex);

	m_pPrototype_Manager->Clear(iClearLevelIndex);
}

#pragma region GRAPHIC_DEVICE
void CGameInstance::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphic_Device->Render_Begin(Color);
}

void CGameInstance::Render_End(HWND hWnd)
{
	m_pGraphic_Device->Render_End(hWnd);
}

#pragma endregion

#pragma region LEVEL_MANAGER
HRESULT CGameInstance::Change_Level(uint32_t iCurrentLevelIndex, CLevel* pNewLevel)
{
	return m_pLevel_Manager->Change_Level(iCurrentLevelIndex, pNewLevel);
}

#pragma endregion

#pragma region PROTOTYPE_MANAGER
HRESULT CGameInstance::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, class CPrototype* pPrototype)
{
	return m_pPrototype_Manager->Add_Prototype(iLevelIndex, strPrototypeTag, pPrototype);
}

CPrototype* CGameInstance::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
	return m_pPrototype_Manager->Clone_Prototype(iLevelIndex, strPrototypeTag, pArg);
}

#pragma endregion

#pragma region OBJECT_MANAGER

HRESULT CGameInstance::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLevelIndex, const wstring_t& strLayerTag, void* pArg)
{
	return m_pObject_Manager->Add_GameObject(iPrototypeLevelIndex, strPrototypeTag, iLevelIndex, strLayerTag, pArg);
}

#pragma endregion


void CGameInstance::Release_Engine()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pPrototype_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pGraphic_Device);

	CGameInstance::Get_Instance()->Destroy_Instance();
}

void CGameInstance::Free()
{

}