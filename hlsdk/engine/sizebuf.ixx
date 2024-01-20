export module sizebuf;

import <cstdint>;
import <cstddef>;

export struct sizebuf_t
{
	const char* buffername{};
	uint32_t flags{};
	std::byte* data{};
	uint32_t maxsize{};
	uint32_t cursize{};
};
