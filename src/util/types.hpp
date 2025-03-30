#pragma once
#include <bitset>
#include <cstdint>

constexpr int MAX_COMPONENTS = 32;
constexpr int MAX_ENTITIES   = 1000;
using EntityID               = uint32_t;
using ComponentID            = uint32_t;
using ComponentMask          = std::bitset<MAX_COMPONENTS>;
