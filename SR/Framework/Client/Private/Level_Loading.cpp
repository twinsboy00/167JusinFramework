#include "Level_Loading.h"
#include "Loader.h"

#include "Level_Logo.h"
#include "Level_GamePlay.h"

#include "GameInstance.h"

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device) : CLevel{ pGraphic_Device }
{

}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevelID)
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_eNextLevelID = eNextLevelID;

	m_pLoader = CLoader::Create(m_pGraphic_Device, m_eNextLevelID);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);

	if (GetKeyState(VK_SPACE) & 0x8000 && true == m_pLoader->isFinished())
	{
		CLevel* pNextLevel = { nullptr };

		switch (m_eNextLevelID)
		{
		case LEVEL::LOGO:
			pNextLevel = CLevel_Logo::Create(m_pGraphic_Device);
			break;
		case LEVEL::GAMEPLAY:
			pNextLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
			break;
		}

		if (nullptr == pNextLevel)
			return;

		if (FAILED(m_pGameInstance->Change_Level(ETOUI(m_eNextLevelID), pNextLevel)))
			return;


		return;
	}

}


HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

#ifdef _DEBUG
	m_pLoader->Print_Text();
#endif 

	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID)
{
	auto pInstance = new CLevel_Loading(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);
}
