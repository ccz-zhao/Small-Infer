#include "utils/logger.h"

#include <gtest/gtest.h>
#include <unistd.h>

auto logger = LOGGER_INSTANCE();

// Demonstrate some basic assertions.
TEST(LOGGER, Basic) {
    LOG_TRACE("console", "test {}", 1);
    LOG_TRACE("console", "test {}", 1);
    LOG_TRACE("console", "test {}", 1);
    LOG_TRACE("console", "Welcome to spdlog!");
    LOG_DEBUG("console","Some error message with arg: {}", 1);
    
    LOG_INFO("console","Easy padding in numbers like {:08d}", 12);
    LOG_WARN("console","Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    LOG_ERROR("console","Support for floats {:03.2f}", 1.23456);
    LOG_CRITI("console","Positional args are {1} {0}..", "too", "supported");
    LOG_TRACE("console","{:<30}", "left aligned");
    
    LOG_TRACE("rotating_file", "test {}", 1);
    LOG_TRACE("rotating_file", "test {}", 1);
    LOG_TRACE("rotating_file", "test {}", 1);
    LOG_TRACE("rotating_file", "Welcome to spdlog!");
    LOG_DEBUG("rotating_file","Some error message with arg: {}", 1);
    
    LOG_INFO("rotating_file","Easy padding in numbers like {:08d}", 12);
    LOG_WARN("rotating_file","Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    LOG_ERROR("rotating_file","Support for floats {:03.2f}", 1.23456);
    LOG_CRITI("rotating_file","Positional args are {1} {0}..", "too", "supported");
    LOG_TRACE("rotating_file","{:<30}", "left aligned");

}

TEST(LOGGER, Basic2) {
    SLOG_T("Basic2 test {}", 1);
    SLOG_T("Basic2 test {}", 1);
    SLOG_T("Basic2 test {}", 1);
    SLOG_T("Basic2 Welcome to spdlog!");
    SLOG_D("Basic2 Some error message with arg: {}", 1);
    
    SLOG_I("Basic2 Easy padding in numbers like {:08d}", 12);
    SLOG_W("Basic2 Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    SLOG_E("Basic2 Support for floats {:03.2f}", 1.23456);
    SLOG_C("Basic2 Positional args are {1} {0}..", "too", "supported");
    SLOG_T("Basic2 {:<30}", "left aligned");
}