#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CPrototype_Manager final : public CBase
{
private:
	CPrototype_Manager();
	virtual ~CPrototype_Manager() = default;

public:
	HRESULT Initialize(uint32_t iNumLevels);
	HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, class CPrototype* pPrototype);
	class CPrototype* Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg);
	void Clear(uint32_t iClearLevelIndex);

private:
	uint32_t				m_iNumLevels = {};
	map<const wstring_t, class CPrototype*>* m_pPrototypes = { nullptr };

private:
	class CPrototype* Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);
public:
	static CPrototype_Manager* Create(uint32_t iNumLevels);
	virtual void Free() override;
};

NS_END		