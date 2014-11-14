#ifndef DCFTIME_RCP_COMMON_H_
#define DCFTIME_RCP_COMMON_H_

enum class service_ids : std::int8_t {
  dcfTimeUnix
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif // DCFTIME_RCP_COMMON_H_

