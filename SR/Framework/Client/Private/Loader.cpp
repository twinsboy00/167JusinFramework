#include "Loader.h"
#include "GameInstance.h"

#include "BackGround.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device) : m_pGraphic_Device(pGraphic_Device), m_pGameInstance{ CGameInstance::Get_Instance() }
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pGraphic_Device);
}

unsigned int APIENTRY ThreadMain(void* pArg)
{
	auto pLoader = static_cast<CLoader*>(pArg);

	if (FAILED(pLoader->Loading()))
		return 0;


	return 1;
}


HRESULT CLoader::Initialize(LEVEL eNextLevelID)
{
	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain, this, 0, nullptr);

	if (0 == m_hThread)
		return E_FAIL;
		
	return S_OK;
}

HRESULT CLoader::Loading()
{
	EnterCriticalSection(&m_CriticalSection);

	HRESULT hr = {};

	switch (m_eNextLevelID)
	{
	case LEVEL::LOGO:
		hr = Loading_For_LogoLV();
		break;
	case LEVEL::GAMEPLAY:
		hr = Loading_For_GamePlayLV();
		break;
	}

	LeaveCriticalSection(&m_CriticalSection);

	if (FAILED(hr))
		return E_FAIL;

	return S_OK;
}


#ifdef _DEBUG

void CLoader::Print_Text()
{
	SetWindowText(g_hWnd, m_szLoadingText);
}

#endif

HRESULT CLoader::Loading_For_LogoLV()
{
	lstrcpy(m_szLoadingText, TEXT("텍스처를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("모델를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("셰이더를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("객체원형 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_For_GamePlayLV()
{
	lstrcpy(m_szLoadingText, TEXT("텍스처를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("모델를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("셰이더를 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("객체원형 로딩 중입입니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));
	for (uint32_t i = 0; i < 99999999; i++)
		int a = 10;

	m_isFinished = true;

	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID)
{
	auto pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	__super::Free();

	WaitForSingleObject(m_hThread, INFINITE);

	CloseHandle(m_hThread);

	DeleteCriticalSection(&m_CriticalSection);

	Safe_Release(m_pGraphic_Device);

	Safe_Release(m_pGameInstance);
}