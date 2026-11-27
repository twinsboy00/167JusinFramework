#pragma once

#define NS_BEGIN(_namespace)		namespace _namespace {
#define NS_END						}


#define NS_USING(_namespace)		using namespace _namespace;

#define MSG_BOX(_message)			MessageBox(0, TEXT(_message), nullptr, MB_OK);

#define ETOI(_enum)					static_cast<signed int>(_enum)
#define ETOUI(_enum)				static_cast<unsigned int>(_enum)

#define DECLARE_SINGLETON(_classtype)						\
	public: _classtype(const _classtype& rhs) = delete;		\
	static _classtype* m_pInstance;							\
	public: static _classtype* Get_Instance();				\
	public: unsigned int Destroy_Instance();				

#define IMPLEMENT_SINGLETON(_classtype)						\
	_classtype* _classtype::m_pInstance = { nullptr };		\
	_classtype* _classtype::Get_Instance() {				\
		if(nullptr == m_pInstance)							\
			m_pInstance = new _classtype;					\
		return m_pInstance;									\
	}														\
	unsigned int _classtype::Destroy_Instance() {			\
		unsigned int iRefCnt = {};							\
		iRefCnt = m_pInstance->Release();					\
		if (0 == iRefCnt)									\
			m_pInstance = nullptr;							\
		return iRefCnt;										\
	}


#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif