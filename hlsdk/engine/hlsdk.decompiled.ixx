export module hlsdk:decompiled;

import std.compat;

#pragma region sizebuf.h

export struct sizebuf_t
{
	const char* buffername{};
	uint32_t flags{};
	std::byte* data{};
	uint32_t maxsize{};
	uint32_t cursize{};
};

#pragma endregion sizebuf.h
