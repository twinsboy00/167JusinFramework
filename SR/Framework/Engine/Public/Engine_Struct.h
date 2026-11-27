#pragma once

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND		hWnd;
		uint32_t	iNumLevels;
		WINMODE		eWinMode;
		uint32_t	iWinSizeX, iWinSizeY;
	}ENGINE_DESC;
	
	typedef struct tagVertexPosition
	{
		D3DXVECTOR3		vPosition;
	}VTXPOS;


}