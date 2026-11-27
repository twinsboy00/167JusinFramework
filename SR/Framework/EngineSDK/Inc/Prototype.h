#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class ENGINE_DLL CPrototype abstract : public CBase
{
protected:
	CPrototype(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPrototype(const CPrototype& Prototype);
	virtual ~CPrototype() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

protected:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = { nullptr };

public:
	virtual CPrototype* Clone(void* add_pointer) = 0;
	virtual void Free() override;

};

NS_END;