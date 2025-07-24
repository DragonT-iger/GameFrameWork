#pragma once

struct FrameData
{
	D2D1_RECT_U rect;

	int frameIndex; // ������ �ε���
	float duration; // ������ ���� �ð� (�� ����)

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

//��������Ʈ�� �ִϸ��̼� ������ ������ ����, ������Ʈ �ƴ�

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
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_sheet; // �ִϸ��̼� ��Ʈ ��Ʈ��
	std::vector<FrameData>									m_frames; // ������ ������
	std::string															m_name; // �ִϸ��̼� �̸�
	float											m_totalDuration = 0.0f; // ��ü �ִϸ��̼� ���� �ð� (�� ����)
	bool															isLoop = false;	//���� ����
};
