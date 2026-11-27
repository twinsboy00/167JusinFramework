#include "Layer.h"

#include "GameObject.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* pGameObejct)
{
	if (nullptr == pGameObejct)
		return E_FAIL;

	m_GameObjects.push_back(pGameObejct);

	return S_OK;
}

void CLayer::Update(f32_t fTimeDelta)
{
	for (auto pGameObject : m_GameObjects)
	{
		if (nullptr != pGameObject)
			pGameObject->Update(fTimeDelta);
	}
}


CLayer* CLayer::Create()
{
	return new CLayer();
}

void CLayer::Free()
{
	__super::Free();

	for (auto& pGameObject : m_GameObjects)
		Safe_Release(pGameObject);

	m_GameObjects.clear();
}
