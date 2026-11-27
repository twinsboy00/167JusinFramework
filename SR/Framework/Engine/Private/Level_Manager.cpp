#include "Level_Manager.h"
#include "Level.h"

#include "GameInstance.h"
CLevel_Manager::CLevel_Manager()
{
}

HRESULT CLevel_Manager::Change_Level(uint32_t iCurrentLevelIndex, CLevel* pNewLevel)
{
	/* 이전 레벨용 자원을 정리해준다. */
	if(nullptr != m_pCurrentLevel)
	{
		if (0 != Safe_Release(m_pCurrentLevel))
			return E_FAIL;

		CGameInstance::Get_Instance()->Clear_Resources(m_iCurrentLevelIndex);
	}
	
	m_pCurrentLevel = pNewLevel;

	m_iCurrentLevelIndex = iCurrentLevelIndex;

	return S_OK;
}

void CLevel_Manager::Update(f32_t fTimeDelta)
{
	m_pCurrentLevel->Update(fTimeDelta);
}

HRESULT CLevel_Manager::Render()
{
	return m_pCurrentLevel->Render();
}

CLevel_Manager* CLevel_Manager::Create()
{
	return new CLevel_Manager();
}

void CLevel_Manager::Free()
{
	__super::Free();

	Safe_Release(m_pCurrentLevel);
}