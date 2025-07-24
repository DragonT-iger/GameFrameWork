#pragma once

struct FrameData
{
	D2D1_RECT_U rect;

	int frameIndex; // 프레임 인덱스
	float duration; // 프레임 지속 시간 (초 단위)

	float GetWidth() const { return rect.right - rect.left; }
	float GetHeight() const { return rect.bottom - rect.top; }

	D2D1_RECT_F ToRectF() const
	{
		return D2D1::RectF(
			static_cast<float>(rect.left),
			static_cast<float>(rect.top),
			static_cast<float>(rect.right),
			static_cast<float>(rect.bottom));
	}
};

//스프라이트의 애니메이션 정보를 가지고 있음, 컴포넌트 아님

class AnimationClip
{
public:
	AnimationClip() = default;
	AnimationClip(const std::string& name) : m_name(name) {}
	~AnimationClip() {
		if (m_sheet)
		{
			ULONG refCount = m_sheet->AddRef();
			refCount = m_sheet->Release();
			std::cout << "refCount : " << refCount << std::endl;
		}
	}

	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1>& sheet) { m_sheet = sheet; }

	void AddFrame(const FrameData& frame)
	{
		m_frames.emplace_back(frame);
		m_totalDuration += frame.duration;
	}

	void SetLooping(bool looping) { isLoop = looping; }
	bool IsLooping() const { return isLoop; }	

	std::string GetName() const { return m_name; }	
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetBitmap() const { return m_sheet; }
	std::vector<FrameData>& GetFrames() { return m_frames; }

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_sheet; // 애니메이션 시트 비트맵
	std::vector<FrameData>									m_frames; // 프레임 데이터
	std::string															m_name; // 애니메이션 이름
	float											m_totalDuration = 0.0f; // 전체 애니메이션 지속 시간 (초 단위)
	bool															isLoop = false;	//루프 여부
};
