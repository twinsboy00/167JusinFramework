#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CObject_Manager final : public CBase
{
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Initialize(uint32_t iNumLevels);
	HRESULT Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLevelIndex, const wstring_t& strLayerTag, void* pArg);
	void Update(f32_t fTimeDelta);
	void Clear(uint32_t iClearLevelIndex);

private:
	class CGameInstance* m_pGameInstance = { nullptr };
	uint32_t m_iNumLevels = {};
	map<const wstring_t, class CLayer*>* m_pLayers = { nullptr };

private:
	class CLayer* Find_Layer(uint32_t iLevelIndex, const wstring_t& strLayerTag);

public:
	static CObject_Manager* Create(uint32_t iNumLevels);
	virtual void Free() override;
};

NS_END
