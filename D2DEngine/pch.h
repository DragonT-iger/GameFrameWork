// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.



#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#endif //PCH_H


#include <vector>
#include <unordered_map>
#include <memory>
#include <type_traits>
#include <string>


#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <cassert>
#include <math.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")   
#pragma comment(lib, "dwrite.lib")  
#pragma comment(lib, "dxgi.lib") 
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_2.h>
#include <d2d1_3.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <d2d1helper.h>
#include <wrl/client.h>
#include <wincodec.h>
#include <dwrite.h>

namespace WRL = Microsoft::WRL;
inline std::wostream& cwout = std::wcout;

#include "MonoBehaviour.h"
#include "Behaviour.h"
#include "GameTimer.h"
#include "Vector2.h"
#include "NzWndBase.h"
#include "Transform.h"
#include "KeyCode.h"
#include "Collider.h"
#include "GameObject.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "RenderInfo.h"
#include "D2DRenderer.h"
#include "PhysicsManager.h"
#include "ResourceManager.h"
#include "InputManager.h"



namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        const char* what() const noexcept override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X",
                static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}

