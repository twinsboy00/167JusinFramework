#pragma once

#include "Base.h"

/*
1. 그래픽카드라는 하드웨어 장치를 초기화하고 기능을 이용하기 위한 객체를 생성한다.
(IDirect3DDevice9) 

*/

NS_BEGIN(Engine)

class CGraphic_Device final :  public CBase
{
private:
	CGraphic_Device();
	virtual~CGraphic_Device();

public:
	HRESULT		Initialize(HWND hWnd,
		WINMODE eMode, 
		const uint32_t iSizeX,
		const uint32_t iSizeY,
		LPDIRECT3DDEVICE9* ppOut);

	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End(HWND hWnd = 0);

private:
	// 1. 성능 조사를 하기 위한 컴객체 생성
	// 2. 그래픽 카드 성능 조사
	// 3. 그래픽 카드에서 제공되는 기능을 사용할 컴객체 생성

	LPDIRECT3D9			m_pSDK = { nullptr };			// 1
	LPDIRECT3DDEVICE9	m_pGraphicDev = { nullptr };	// 3
public:
	static CGraphic_Device* Create(HWND hWnd, WINMODE eMode, const uint32_t iSizeX, const uint32_t iSizeY, LPDIRECT3DDEVICE9* ppOut);
	virtual void Free();
};

NS_END



