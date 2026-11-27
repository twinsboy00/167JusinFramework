#include "Object_Manager.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "Layer.h"

CObject_Manager::CObject_Manager()
    : m_pGameInstance{ CGameInstance::Get_Instance() }
{
    Safe_AddRef(m_pGameInstance);
}

HRESULT CObject_Manager::Initialize(uint32_t iNumLevels)
{
    m_iNumLevels = iNumLevels;

    m_pLayers = new map<const wstring_t, class CLayer*>[iNumLevels];

    return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLevelIndex, const wstring_t& strLayerTag, void* pArg)
{
    auto    pGameObject = dynamic_cast<CGameObject*>(m_pGameInstance->Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
    if (nullptr == pGameObject)
        return E_FAIL;

    auto    pLayer = Find_Layer(iLevelIndex, strLayerTag);

    if (nullptr == pLayer)
    {
        pLayer = CLayer::Create();

        if (FAILED(pLayer->Add_GameObject(pGameObject)))
            return E_FAIL;

        m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
    }
    else
        pLayer->Add_GameObject(pGameObject);

    return S_OK;
}

void CObject_Manager::Update(f32_t fTimeDelta)
{
    for (uint32_t i = 0; i < m_iNumLevels; ++i)
    {
        for (auto& Pair : m_pLayers[i])
        {
            Pair.second->Update(fTimeDelta);
        }
    }
}

void CObject_Manager::Clear(uint32_t iClearLevelIndex)
{
    for (auto& Pair : m_pLayers[iClearLevelIndex])
        Safe_Release(Pair.second);

    m_pLayers[iClearLevelIndex].clear();
}

CLayer* CObject_Manager::Find_Layer(uint32_t iLevelIndex, const wstring_t& strLayerTag)
{
    if (iLevelIndex >= m_iNumLevels)
        return nullptr;

    auto    iter = m_pLayers[iLevelIndex].find(strLayerTag);
    if (iter == m_pLayers[iLevelIndex].end())
        return nullptr;

    return iter->second;
}

CObject_Manager* CObject_Manager::Create(uint32_t iNumLevels)
{
    auto pInstance = new CObject_Manager();

    if (FAILED(pInstance->Initialize(iNumLevels)))
    {
        MSG_BOX("Failed to Created : CObject_Manager");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CObject_Manager::Free()
{
    __super::Free();

    for (uint32_t i = 0; i < m_iNumLevels; ++i)
    {
        for (auto& Pair : m_pLayers[i])
        {
            Safe_Release(Pair.second);
        }
        m_pLayers[i].clear();
    }

    Safe_Delete_Array(m_pLayers);

    Safe_Release(m_pGameInstance);
}
