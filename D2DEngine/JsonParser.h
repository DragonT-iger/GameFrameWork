#pragma once

#include <filesystem>
#include "AnimationClip.h"

using AnimationClips = std::vector<AnimationClip>;
class JsonParser
{
public:
	JsonParser() = default;
	~JsonParser() = default;

	static AnimationClips Load(const std::filesystem::path& jsonPath);
};