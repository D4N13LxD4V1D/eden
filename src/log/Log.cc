module;

#include <print>

export module eden:log;

namespace eden {

export void log() { std::println(); }

export template <class... Args>
void log(std::format_string<Args...> fmt, Args &&...args) {
  std::println(fmt, std::forward<Args>(args)...);
}

export template <class... Args>
void log(FILE *stream, std::format_string<Args...> fmt, Args &&...args) {
  std::println(stream, fmt, std::forward<Args>(args)...);
}

export void log(FILE *stream) { std::println(stream); }

} // namespace eden