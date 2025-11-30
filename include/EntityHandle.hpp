#pragma once
#include <random>


namespace secs
{

/**
 * @brief A randomly assigned 64-bit integer ID.
 */
class Handle
{
public:
    Handle() = default;
    Handle(const Handle&) = default;
    Handle& operator=(const Handle&) = default;

    /// Sets the seed
    static void setSeed(const uint64_t seed)
    {
        random().seed(seed);
    }

    /// Constructs and returns a valid UUID
    static Handle create()
    {
        return Handle{ random()() };
    }

    /// Constructs and returns an invalid UUID
    static Handle invalid()
    {
        return Handle{};
    }

    /// Invalidates this UUID
    void invalidate()
    {
        m_handle = 0;
    }

    /// Returns the underlying UUID value
    uint64_t id() const { return m_handle; }

    bool operator==(const Handle& other) const { return m_handle == other.m_handle; }
    bool operator<(const Handle& other) const { return m_handle < other.m_handle; }

    explicit operator bool() const { return m_handle != 0; }
    explicit operator uint64_t() const { return m_handle; }

private:
    explicit Handle(const uint64_t uuid) : m_handle(uuid) { }

    uint64_t m_handle = 0;

    static std::mt19937_64& random()
    {
        static std::mt19937_64 r(std::chrono::system_clock::now().time_since_epoch().count());
        return r;
    }

    friend struct std::hash<Handle>;
    friend struct std::formatter<Handle>;
};


/// @brief A Handle representing an entity
using EntityHandle = Handle;

} // namespace siren::ecs
// Hash support
template <>
struct std::hash<secs::Handle>
{
    size_t operator()(const secs::Handle& handle) const noexcept
    {
        return std::hash<uint64_t>{}(handle.m_handle);
    }
};

// std::formatter support
template <>
struct std::formatter<secs::Handle> : std::formatter<uint64_t>
{
    auto format(const secs::Handle& handle, std::format_context& ctx) const
    {
        return std::formatter<uint64_t>::format(handle.m_handle, ctx);
    }
};