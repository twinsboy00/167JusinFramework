#pragma once

#include "Client_Defines.h"
#include "Level.h"


NS_BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Deveice);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevelID);
	virtual void Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL			m_eNextLevelID = { LEVEL::END };
	class CLoader* m_pLoader = { nullptr };

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Devicem, LEVEL eNextLevelID);
	virtual void Free();

};

NS_END