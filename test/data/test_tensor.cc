#include "tensor.hpp"
#include "utils/logger.h"

#include <gtest/gtest.h>
#include <vector>

auto logger = LOGGER_INSTANCE();

TEST(TensorTest, BasicOperation) {
    using namespace sinfer;
    SLOG_I("creating 3D Tensor(1, 2, 3)");
    Tensor<float> t1(1, 2, 3);
    auto dims =  t1.get_dimensions();
    SLOG_I("dims.size = {}", dims.size());
    SLOG_I("dims is {}", spdlog::fmt_lib::join(dims, ","));
    auto a = t1[0, 0, 1];
    SLOG_I("current [0, 0, 1] = {}", a);
    SLOG_I("set [0, 0, 1] to 99.99");
    t1[0, 0, 1] = 99.99;
    a = t1[0, 0, 1];
    SLOG_I("current [0, 0, 1] = {}", a);

    SLOG_I("creating 2D Tensor(2, 3)");
    Tensor<int> t2 (2, 3);
    dims =  t2.get_dimensions();
    SLOG_I("dims.size = {}", dims.size());
    SLOG_I("dims is {}", spdlog::fmt_lib::join(dims, ","));
    auto b = t2[1, 1];
    SLOG_I("current [1, 1] = {}", b);
    SLOG_I("set [1, 1] to 99");
    t2[1, 1] = 99;
    b = t2[1, 1];
    SLOG_I("current [1, 1] = {}", b);
}