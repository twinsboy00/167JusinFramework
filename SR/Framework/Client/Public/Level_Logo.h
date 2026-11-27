#pragma once

#include "Client_Defines.h"
#include "Level.h"


NS_BEGIN(Client)

class CLevel_Logo final : public CLevel
{
private:
	CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Deveice);
	virtual ~CLevel_Logo() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	static CLevel_Logo* Create(LPDIRECT3DDEVICE9 pGraphic_Devicem);
	virtual void Free();

};

NS_END