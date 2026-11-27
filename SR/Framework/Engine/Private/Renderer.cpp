#include "Renderer.h"

#include "GameInstance.h"
#include "GameObject.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
    : m_pGraphic_Device{ pGraphic_Device }
    , m_pGameInstance{ CGameInstance::Get_Instance() }
{
    Safe_AddRef(m_pGraphic_Device);
    Safe_AddRef(m_pGameInstance);
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pRenderObject)
{
    m_RenderObjects[ETOUI(eGroup)].push_back(pRenderObject);

    Safe_AddRef(pRenderObject);

    return S_OK;
}

HRESULT CRenderer::Draw()
{
    if (FAILED(Render_Priority()))
        return E_FAIL;

    if (FAILED(Render_NonBlend()))
        return E_FAIL;

    if (FAILED(Render_Blend()))
        return E_FAIL;

    if (FAILED(Render_UI()))
        return E_FAIL;

    return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
    m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);  // D3DRS_ZENABLE: 깊이 버퍼 활성화 여부
    m_pGraphic_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // D3DRS_ZWRITEENABLE : Z 버퍼 값 저장 여부 

    for (auto& pRenderObject : m_RenderObjects[ETOUI(RENDERGROUP::PRIORITY)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }
    m_RenderObjects[ETOUI(RENDERGROUP::PRIORITY)].clear();

    m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pGraphic_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    return S_OK;
}

HRESULT CRenderer::Render_NonBlend()
{
    for (auto& pRenderObject : m_RenderObjects[ETOUI(RENDERGROUP::NONBLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }
    m_RenderObjects[ETOUI(RENDERGROUP::NONBLEND)].clear();

    return S_OK;
}

HRESULT CRenderer::Render_Blend()
{
    /* 깊이 값에 따라서 결정한다. */

    m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // D3DRS_ALPHABLENDENABLE: 알파블렌딩 여부
    m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // D3DRS_BLENDOP : 그릴색과 기존배경색(데스티네이션)을 더하기 연산(D3DBLENDOP_ADD)으로 합치도록 설정
    m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // D3DRS_SRCBLEND : 새로 그릴 픽셀의 색상 값에 자신의 알파값을 곱함
    m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // D3DRS_DESTBLEND: 데스티네이션에 역 알파 값을 곱함

    for (auto& pRenderObject : m_RenderObjects[ETOUI(RENDERGROUP::BLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }
    m_RenderObjects[ETOUI(RENDERGROUP::BLEND)].clear();

    m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    return S_OK;
}

HRESULT CRenderer::Render_UI()
{
    for (auto& pRenderObject : m_RenderObjects[ETOUI(RENDERGROUP::UI)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }
    m_RenderObjects[ETOUI(RENDERGROUP::UI)].clear();

    return S_OK;
}

CRenderer* CRenderer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    return new CRenderer(pGraphic_Device);
}

void CRenderer::Free()
{
    __super::Free();

    Safe_Release(m_pGraphic_Device);
    Safe_Release(m_pGameInstance);
}
