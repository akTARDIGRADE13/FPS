#include <cstdint>

namespace akTARDIGRADE13 {

template <std::uint_fast64_t Modulus> struct modint {
  using u64 = std::uint_fast64_t;

public:
  constexpr modint(const u64 _val = 0) : val(_val % Modulus){};

private:
  u64 val;
};

} // namespace akTARDIGRADE13