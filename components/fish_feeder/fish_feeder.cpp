#include "fish_feeder.h"
#include "esphome/core/log.h"

namespace esphome {
namespace fish_feeder {

static const char *TAG = "fish_feeder";

void FishFeeder::setup() {
  ESP_LOGI(TAG, "Fish Feeder initialized");
  feed_count_ = 0;
  busy_ = false;
}

void FishFeeder::loop() {
  // nothing yet (will handle timing later)
}

void FishFeeder::feed() {
  if (busy_) {
    ESP_LOGW(TAG, "Feed ignored (busy)");
    return;
  }

  ESP_LOGI(TAG, "Feed triggered");
  busy_ = true;

  // TODO V0.2: move servo + timing + counter
  busy_ = false;
}

void FishFeeder::reset() {
  ESP_LOGI(TAG, "Reset feed counter");
  feed_count_ = 0;
}

}  // namespace fish_feeder
}  // namespace esphome