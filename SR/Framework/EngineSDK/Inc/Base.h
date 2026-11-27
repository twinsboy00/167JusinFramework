#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)

/* 1. 레퍼런스 카운트를 관리한다 */
/* 2. 관리	하는 기능을 자식 클래스에게 보여준다 */

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	/* RefCnt 증가 시킨다*/
	uint32_t AddRef();

	/* RefCnt 감소시킨다. or 삭제한다 */
	uint32_t Release();

protected:
	uint32_t		m_iRefCnt = {};

public:
	virtual void Free();
};

NS_END