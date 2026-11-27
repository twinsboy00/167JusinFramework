#pragma once


#include <d3d9.h>
#include <d3dx9.h>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <stdint.h>
#include <string>
using namespace std;

#include "Engine_Typedef.h"
#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Enum.h"
#include "Engine_Struct.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__, __LINE__ )
#define new DBG_NEW

#endif
#endif

using namespace Engine;