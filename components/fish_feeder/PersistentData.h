#pragma once
#include <cstdint>

namespace esphome {
namespace fish_feeder {
struct PersistentData {
    uint32_t version{1};
    uint32_t feed_count{0};
    uint32_t reserved{0};
};
}  // namespace fish_feeder
}  // namespace esphome