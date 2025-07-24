#include "pch.h"
#include "ResourceManager.h"
#include "JsonParser.h"
#include "D2DRenderer.h"

namespace filesys = std::filesystem;


void ResourceManager::LoadPath()
{
	if (!filesys::exists(resourcePath) || !filesys::is_directory(resourcePath))
	{
		std::cerr << "유효하지 않은 디렉토리 경로입니다" << std::endl;
		return;
	}

	for (const auto& it : filesys::recursive_directory_iterator(resourcePath))
	{
		if (it.is_regular_file() && it.path().extension() == ".json")
		{
			auto path = it.path();
			std::string key = path.filename().string();

			std::cout << key << std::endl;

			m_JsonPaths.emplace(std::move(key), std::move(path));
		}
		else if (it.is_regular_file() && it.path().extension() == ".png")
		{
			auto path = it.path();
			std::string key = path.filename().string();

			std::cout << key << std::endl;

			m_PngPaths.emplace(std::move(key), std::move(path));
		}
	}
}

const ComPtr<ID2D1Bitmap1>& ResourceManager::LoadTexture(const std::string& key)
{
	if (m_PngPaths.find(key) == m_PngPaths.end())
	{
		std::cerr << "잘못된 파일 이름 입력 : " + key << std::endl;
		return nullptr;
	}

	auto path = m_PngPaths.at(key);

	if (m_textures.find(key) == m_textures.end()) //새로 등록하는 거면 비트맵 등록
	{
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

		D2DRenderer::Instance().CreateBitmapFromFile(path.wstring().c_str(), *sheet.GetAddressOf());

		if (!sheet)
		{
			std::cerr << "비트맵 생성 오류" << std::endl;
			return nullptr;
		}
		m_textures.emplace(key, sheet);
	}

	return m_textures.at(key);
}

std::shared_ptr<AnimationClip> ResourceManager::LoadAnimationClip(const std::string& key, const std::string& cliptag)
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

	if (m_JsonPaths.find(key) == m_JsonPaths.end())
	{
		std::cerr << "잘못된 파일 이름 입력 : " + key << std::endl;
		return nullptr;
	}

	auto path = m_JsonPaths.at(key);

	if (m_textures.find(key) == m_textures.end()) //없으면 비트맵 새로 등록하고 있으면 있는거 가져오기
	{
		filesys::path texturePath = path;
		texturePath.replace_extension(".png");

		D2DRenderer::Instance().CreateBitmapFromFile(texturePath.wstring().c_str(), *sheet.GetAddressOf());

		if (!sheet)
		{
			std::cerr << "비트맵 생성 오류: " << texturePath.string() << std::endl;
			return nullptr;
		}
		m_textures.emplace(key, sheet);
	}
	else
	{
		sheet = m_textures[key];
	}

	if (m_aniClips.find(key + "_" + cliptag) == m_aniClips.end())	//클립 태그 json정보랑 맞는지 확인 잘할 것
	{
		AnimationClips clips = JsonParser::Load(path);

		for (auto& clip : clips)
		{
			std::shared_ptr<AnimationClip> pclip = std::make_shared<AnimationClip>(clip);
			pclip->SetBitmap(sheet);
			std::string newkey = key + "_" + clip.GetName(); //클립 태그 지정 가능하게 바꿀 수 있으면 좋을듯
			std::cout << "new Key : " << newkey << std::endl;
			m_aniClips[newkey] = pclip;
		}
	}

	return m_aniClips.at(key + "_" + cliptag);
}
