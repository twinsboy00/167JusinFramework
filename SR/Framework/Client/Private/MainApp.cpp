#include "MainApp.h"


#include "Level_Loading.h"

#include "GameInstance.h"

CMainApp::CMainApp() : m_pGameInstance { CGameInstance::Get_Instance() }
{
    Safe_AddRef(m_pGameInstance);
}


HRESULT CMainApp::Initialize()
{
    ENGINE_DESC     EngineDesc{
        .hWnd = g_hWnd,
        .iNumLevels = ETOUI(LEVEL::END),
        .eWinMode = WINMODE::WIN,
        .iWinSizeX = g_iWinSizeX,
        .iWinSizeY = g_iWinSizeY,
    };

    /* 내 게임에 필요한 기타 초기화작업을 수행한다. */
    if (FAILED(m_pGameInstance->Initialize_Engine(EngineDesc, &m_pGraphic_Device)))
        return E_FAIL;

    if (FAILED(Start_Level(LEVEL::LOGO)))
        return E_FAIL;

    return S_OK;
}

void CMainApp::Update(float fTimeDelta)
{
    m_pGameInstance->Update_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
    m_pGameInstance->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

    if (FAILED(m_pGameInstance->Draw()))
        return E_FAIL;

    //  빨간색 출력

    // 노란색 출력
    //  주황색 출력


    m_pGameInstance->Render_End();
    
    return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eStartLevel)
{
    if(FAILED(m_pGameInstance->Change_Level(ETOUI(LEVEL::LOADING), CLevel_Loading::Create(m_pGraphic_Device, eStartLevel))))
        return E_FAIL;
    
    return S_OK;
}

CMainApp* CMainApp::Create()
{
    auto pInstance = new CMainApp();

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CMainApp")
        Safe_Release(pInstance);
    }

    return pInstance;
}


void CMainApp::Free()
{
    __super::Free();

    Safe_Release(m_pGraphic_Device);

    m_pGameInstance->Release_Engine();

    Safe_Release(m_pGameInstance);
}