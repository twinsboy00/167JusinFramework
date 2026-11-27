#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CLevel_Manager final : public CBase
{
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default; 

public:
	HRESULT	Change_Level(uint32_t iCurrentLevelIndex, class CLevel* pNewLevel);
	void Update(f32_t fTimeDelta);
	HRESULT Render();

private:
	class CLevel* m_pCurrentLevel = { nullptr };
	uint32_t		m_iCurrentLevelIndex = {};

public:
	static CLevel_Manager* Create();
	virtual void Free()	override;
};

NS_END