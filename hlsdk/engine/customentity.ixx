export module customentity;

import <cstdint>;
import <concepts>;

// Custom Entities

// Start/End Entity is encoded as 12 bits of entity index, and 4 bits of attachment (4:12)
export inline constexpr auto BEAMENT_ENTITY(std::integral auto x) noexcept { return x & 0xFFF; }
export inline constexpr auto BEAMENT_ATTACHMENT(std::integral auto x) noexcept { return (x >> 12) & 0xF; }

// Beam types, encoded as a byte
export enum EBeamTypes : std::uint8_t
{
	BEAM_POINTS = 0,
	BEAM_ENTPOINT,
	BEAM_ENTS,
	BEAM_HOSE,
};

export inline constexpr auto BEAM_FSINE = 0x10;
export inline constexpr auto BEAM_FSOLID = 0x20;
export inline constexpr auto BEAM_FSHADEIN = 0x40;
export inline constexpr auto BEAM_FSHADEOUT = 0x80;