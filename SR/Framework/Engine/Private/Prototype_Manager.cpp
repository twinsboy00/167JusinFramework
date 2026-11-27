#include "Prototype_Manager.h"
#include "Prototype.h"

CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(uint32_t iNumLevels)
{
    m_iNumLevels = iNumLevels;

    m_pPrototypes = new map<const wstring_t, class CPrototype*>[iNumLevels];

    return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, CPrototype* pPrototype)
{
    if (nullptr != Find_Prototype(iLevelIndex, strPrototypeTag))
        return E_FAIL;

    m_pPrototypes[iLevelIndex].emplace(strPrototypeTag, pPrototype);

    return S_OK;
}

CPrototype* CPrototype_Manager::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
    auto pPrototype = Find_Prototype(iLevelIndex, strPrototypeTag);
    if (nullptr == pPrototype)
        return nullptr;

    auto pInstance = pPrototype->Clone(pArg);
    if (nullptr == pInstance)
        return nullptr;

    return pInstance;

}

void CPrototype_Manager::Clear(uint32_t iClearLevelIndex)
{
    for (auto& Pair : m_pPrototypes[iClearLevelIndex])
        Safe_Release(Pair.second);

    m_pPrototypes[iClearLevelIndex].clear();
}

CPrototype* CPrototype_Manager::Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag)
{
    if (iLevelIndex >= m_iNumLevels)
        return nullptr;

    auto iter = m_pPrototypes[iLevelIndex].find(strPrototypeTag);

    if (iter == m_pPrototypes[iLevelIndex].end())
        return nullptr;

    return iter->second;
}

CPrototype_Manager* CPrototype_Manager::Create(uint32_t iNumLevels)
{
    auto pInstance = new CPrototype_Manager();

    if (FAILED(pInstance->Initialize(iNumLevels)))
    {
        MSG_BOX("Failed to Created : CPrototype_Manager");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CPrototype_Manager::Free()
{
    __super::Free();

    for (uint32_t i = 0; i < m_iNumLevels; ++i)
    {
        for (auto& Pair : m_pPrototypes[i])
        {
            Safe_Release(Pair.second);
        }
        m_pPrototypes[i].clear();
    }

    Safe_Delete_Array(m_pPrototypes);
}