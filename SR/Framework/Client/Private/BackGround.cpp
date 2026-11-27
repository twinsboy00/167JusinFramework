#include "BackGround.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device) : CGameObject{ pGraphic_Device }
{
}

CBackGround::CBackGround(const CBackGround& Prototype) : CGameObject{ Prototype }
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	return S_OK;
}

void CBackGround::Update(f32_t fTimeDelta)
{
	int a = 10;
}

HRESULT CBackGround::Render()
{
	return S_OK;
}


CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	auto pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CPrototype* CBackGround::Clone(void* pArg)
{
	auto pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();

}