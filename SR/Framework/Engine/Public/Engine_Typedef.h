#pragma once

/* 자주 사용하는 타입들을 내가 원하는 이름으로 재정의한다. */

namespace Engine
{
	typedef char				char_t;
	typedef wchar_t				tchar_t;
	typedef wstring				wstring_t;

	typedef float				f32_t;
	typedef double				f64_t;

	typedef bool				bool_t;

	typedef D3DXVECTOR2			float2_t;
	typedef D3DXVECTOR3			float3_t;
	typedef D3DXVECTOR4			float4_t;

	typedef D3DXMATRIX			float4x4_t;


}

// char, signed char, unsigned char 다 다른 타입이다.