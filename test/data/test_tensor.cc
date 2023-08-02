#include <gtest/gtest.h>
#include <vector>
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "tensor.hpp"

auto max_size = 1048576 * 5;
auto max_files = 3;
auto logger = spdlog::rotating_logger_mt("test_tensor", "logs/test_tensor.txt", max_size, max_files);

TEST(TensorTest, BasicOperation) {
    using namespace sinfer;
    logger->info("creating 3D Tensor(1, 2, 3)");
    Tensor<float> t1(1, 2, 3);
    auto dims =  t1.get_dimensions();
    logger->info("dims.size = {}", dims.size());
    logger->info("dims is {}", spdlog::fmt_lib::join(dims, ","));
    logger->info("set[0, 0, 1] = 1");
}