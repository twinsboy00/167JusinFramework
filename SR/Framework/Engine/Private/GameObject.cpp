#include "GameObject.h"

#include "GameInstance.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device) : CPrototype{ pGraphic_Device }, m_pGameInstance{CGameInstance::Get_Instance()}
{
	Safe_AddRef(m_pGameInstance);
}

CGameObject::CGameObject(const CGameObject& Prototype) : CPrototype{ Prototype }, m_pGameInstance{Prototype.m_pGameInstance}
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
	return S_OK;
}

void CGameObject::Update(f32_t fTimeDelta)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

void CGameObject::Free()
{
	__super::Free();

	Safe_Release(m_pGameInstance); 
}