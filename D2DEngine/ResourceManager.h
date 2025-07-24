#pragma once
//2025-07-10

///</summary>
// ResourceManager
///</summary>
// ����, �ؽ���, �ִϸ��̼� Ŭ�� ���� �� ���� ����
#include <unordered_map>
#include <filesystem>
#include "AnimationClip.h"

using namespace Microsoft::WRL;

class D2DRenderer; //������ ���漱��, ��Ʈ�� ������ �ٸ� �� ����

class ResourceManager
{
	ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
public:
	//~ResourceManager() = default;
	~ResourceManager() {}

	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	void Uninitialize() {
		m_textures.clear();
		m_aniClips.clear();
		m_JsonPaths.clear();
		m_PngPaths.clear();
	}

	void LoadPath();

	const ComPtr<ID2D1Bitmap1>& LoadTexture(const std::string& key);
	std::shared_ptr<AnimationClip> LoadAnimationClip(const std::string& key, const std::string& cliptag);

	void SetResourcePath(const std::filesystem::path& path)
	{
		resourcePath = path;
	}

private:
	std::filesystem::path															resourcePath;//���ҽ� ���

	std::unordered_map<std::string, std::filesystem::path> m_JsonPaths;
	std::unordered_map<std::string, std::filesystem::path> m_PngPaths;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_aniClips;
	//std::unordered_map<std::wstring, ���� Ŭ����> m_sounds;	//���� ��
};
