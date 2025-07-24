#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "JsonParser.h"

struct FrameInfo {
	std::string tag;
	int from;
	int to;
};

AnimationClips JsonParser::Load(const std::filesystem::path& jsonPath)
{
	std::ifstream ifs(jsonPath);

	if (!ifs.is_open())
	{
		std::cerr << "Json ������ �� �� �����ϴ�." << std::endl;
		return {};
	}

	nlohmann::json js;
	ifs >> js;  //������ jsonŸ������ parse

	if (js.is_discarded())
	{
		std::cerr << "JSON �Ľ� ����: ��ȿ���� ���� �����Դϴ�.\n";
		return {};
	}

	std::vector<FrameInfo> frameinfos;

	for (const auto& t : js["meta"]["frameTags"])
	{
		FrameInfo info;
		info.tag = t["name"];
		info.from = t["from"];
		info.to = t["to"];

		frameinfos.push_back(info);
	}

	AnimationClips clips;

	for (const auto& info : frameinfos)
	{
		AnimationClip clip(info.tag);

		for (int i = info.from; i <= info.to; i++)
		{
			auto& frame = js["frames"][i];
			FrameData src;

			src.rect.top = frame["frame"]["y"];
			src.rect.bottom = src.rect.top + frame["frame"]["h"];
			src.rect.left = frame["frame"]["x"];
			src.rect.right = src.rect.left + frame["frame"]["w"];
			src.duration = frame["duration"] / 1000.0f;

			clip.AddFrame(src);
		}
		clips.emplace_back(clip);
	}

	return clips;
}
