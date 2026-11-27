#include "Prototype.h"

CPrototype::CPrototype(LPDIRECT3DDEVICE9 pGraphic_Device) : m_pGraphic_Device {pGraphic_Device}
{
	Safe_AddRef(m_pGraphic_Device);
}

CPrototype::CPrototype(const CPrototype& Prototype) : m_pGraphic_Device{ Prototype.m_pGraphic_Device}
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CPrototype::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPrototype::Initialize(void* pArg)
{
	return S_OK;
}

void CPrototype::Free()
{
	__super::Free();

	Safe_Release(m_pGraphic_Device);
}
