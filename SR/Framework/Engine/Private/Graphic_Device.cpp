#include "Graphic_Device.h"
#include "GameInstance.h"

CGraphic_Device::CGraphic_Device()
	: m_pSDK(nullptr), m_pGraphicDev(nullptr)
{
}

CGraphic_Device::~CGraphic_Device()
{

}

HRESULT CGraphic_Device::Initialize(HWND hWnd, WINMODE eMode, const uint32_t iSizeX, const uint32_t iSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	// 1. 성능 조사를 하기 위한 컴객체 생성

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);


	if (nullptr == m_pSDK)
		return E_FAIL;

	// 2. 그래픽 카드 성능 조사

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// D3DADAPTER_DEFAULT : 네 컴퓨터에 설치된 그래픽 카드(기본 그래픽 카드)

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
		return E_FAIL;

	uint32_t		iFlag = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) // 하드웨어(그래픽카드)가 정점의 변환(Transform)과 조명(Light)을 하드웨어에서 직접 처리할 수 있는지 체크
		iFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED; // 참일시 하드웨어(그래픽 카드)가 연산 하도록 설정

	else
		iFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED; // 거짓일시 소프트웨어(CPU)가 연산하도록 설정


	D3DPRESENT_PARAMETERS		d3dpp;		//백버퍼 구조체
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = iSizeX;
	d3dpp.BackBufferHeight = iSizeY;			// 백버퍼 크기
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// 백버퍼 색깔
	d3dpp.BackBufferCount = 1;					// 백버퍼 갯수		
	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;		// 안티 앨리어싱 종류, 사용X
	d3dpp.MultiSampleQuality = 0;						// 안티앨리어싱 품질

	// D3DSWAPEFFECT_FLIP : 버퍼를 하나만 사용
	// D3DSWAPEFFECT_COPY : 더블 버퍼링과 유사
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 스왑 체인

	d3dpp.hDeviceWindow = hWnd;					// 어디에서 출력할것인지

	d3dpp.Windowed = static_cast<bool>(eMode);	// 창모드인지 전체화면 모드인지

	d3dpp.EnableAutoDepthStencil = TRUE;		// 자동으로 깊이와 스텐실을 생성하고 관리할것인지에 대해 결정
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 깊이와 스텐실값
	
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 3. 그래픽 카드에서 제공되는 기능을 사용할 컴객체 생성

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, iFlag, &d3dpp, &m_pGraphicDev)))
		return E_FAIL;

	*ppOut = m_pGraphicDev;

	Safe_AddRef(m_pGraphicDev);

	return S_OK;
}

// 후면 버퍼 동작 원리
void CGraphic_Device::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0,		// 렉트의 개수
						nullptr,	// 여러 개의 렉트 중 첫 번째 렉트의 주소
						D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
						Color,	// 후면 버퍼 색상
						1.f,	// 깊이 버퍼 초기화
						0);		// 스텐실 버퍼 초기화

	m_pGraphicDev->BeginScene();

}

void CGraphic_Device::Render_End(HWND g_hWnd)
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, g_hWnd, nullptr);

	// 1, 2 : 렉트의 주소 // SWAPEFFECT가 COPY일 때 동작
	// 4 : 옵션			// SWAPEFFECT가 COPY일 때 동작
}

CGraphic_Device* CGraphic_Device::Create(HWND hWnd, WINMODE eMode, const uint32_t iSizeX, const uint32_t iSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	auto pInstance = new CGraphic_Device();

	if (FAILED(pInstance->Initialize(hWnd, eMode, iSizeX, iSizeY, ppOut)))
	{
		MSG_BOX("Failed to Created : CGraphic_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGraphic_Device::Free()
{
	__super::Free();

	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}


/*
깊이 값 (Depth)

카메라 시점으로부터 물체까지의 거리를 나타내는 값
0.0 ~ 1.0의 값을 씀

API때는 뒤에있는것을 먼저그리고 그 위 에 나타낼 것들을 그 위에 다시 그리는 방식으로 Depth를 표현했지만,
다이렉트에선 깊이값에 따라 전에 그린것보다 더 낮은값의 물체를 그림.
따라서 배경을 나중에 그려도 물체만 그려짐.


*/