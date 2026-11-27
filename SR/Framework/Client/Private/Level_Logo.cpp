#include "Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device) : CLevel{ pGraphic_Device }
{

}

HRESULT CLevel_Logo::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);

	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		if (FAILED(m_pGameInstance->Change_Level(ETOUI(LEVEL::LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::GAMEPLAY))))
			return;

		return;
	}
}


HRESULT CLevel_Logo::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

#ifdef _DEBUG
	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));
#endif 

	return S_OK;
}

CLevel_Logo* CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	auto pInstance = new CLevel_Logo(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_Logo");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}