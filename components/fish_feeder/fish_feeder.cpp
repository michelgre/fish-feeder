#include "fish_feeder.h"
#include "esphome/core/log.h"

namespace esphome {
namespace fish_feeder {

static const char *TAG = "fish_feeder";
static constexpr uint32_t BOOT_SERVO_SETTLE_MS = 200;

void FishFeeder::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Fish Feeder");

  if (servo_ == nullptr) {
    ESP_LOGE(TAG, "No servo configured");
    mark_failed();
    return;
  }

  feed_count_ = 0;
  state_ = State::IDLE;
  close_servo_();
  delay(BOOT_SERVO_SETTLE_MS); // Wait enough to get it closed

  ESP_LOGI(TAG, "setup()");
  ESP_LOGI(TAG, "servo = %p", servo_);
  ESP_LOGI(TAG, "feed_count = %u", feed_count_);
  ESP_LOGI(TAG, "State: %s", FishFeederState::to_string(state_));
  ESP_LOGI(TAG, "Fish Feeder initialized");
}

void FishFeeder::loop() {
  // nothing - actions will trigger timers to continue.
}

void FishFeeder::feed() {
  if (state_ != State::IDLE)
    return;

  state_ = State::OPENING;
  open_servo_();
  state_ = State::WAITING;

  set_timeout("close-servo", open_duration_ms_, [this]() {
    close_servo_();

    state_ = State::IDLE;

    feed_count_++;
    ESP_LOGI(TAG, "Feed done (count=%u)", feed_count_);
  });
}

void FishFeeder::reset() {
  ESP_LOGI(TAG, "Reset feed counter");
  feed_count_ = 0;
}

void FishFeeder::dump_config() {
  ESP_LOGCONFIG(TAG, "Fish Feeder");
  ESP_LOGCONFIG(TAG, "  Open angle: %.1f°", open_angle_);
  ESP_LOGCONFIG(TAG, "  Close angle: %.1f°", close_angle_);
  ESP_LOGCONFIG(TAG, "  Open duration: %u ms", open_duration_ms_);
  ESP_LOGCONFIG(TAG, "Fish Feeder");
  ESP_LOGCONFIG(TAG, "  Servo configured: %s", servo_ != nullptr ? "yes" : "no");
  ESP_LOGCONFIG(TAG, "  Open angle: %.1f", open_angle_);
  ESP_LOGCONFIG(TAG, "  Close angle: %.1f", close_angle_);
  ESP_LOGCONFIG(TAG, "  Open duration: %u ms", open_duration_ms_);
}

}  // namespace fish_feeder
}  // namespace esphome