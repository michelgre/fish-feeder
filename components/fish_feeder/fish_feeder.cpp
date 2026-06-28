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

  close_servo_();
  delay(BOOT_SERVO_SETTLE_MS); // Wait enough to get it closed
  set_state_(State::IDLE);
  pref_ = global_preferences->make_preference<PersistentData>(fnv1_hash("fish_feeder"));
  load_persistent_data_();

  ESP_LOGI(TAG, "setup()");
  ESP_LOGI(TAG, "servo = %p", servo_);
  ESP_LOGI(TAG, "feed_count = %u", persistent_.feed_count);
  ESP_LOGI(TAG, "State: %s", FishFeederState::to_string(state_));
  ESP_LOGI(TAG, "Fish Feeder ready");
}

void FishFeeder::loop() {
  // nothing - actions will trigger timers to continue.
}

void FishFeeder::feed() {
  if (state_ != State::IDLE) {
    ESP_LOGW(TAG, "Feed ignored (state=%s)",
             FishFeederState::to_string(state_));
    return;
  }

  open_servo_();
  set_state_(State::WAITING);

  set_timeout("close-servo", open_duration_ms_, [this]() {
    close_servo_();

    state_ = State::IDLE;

    persistent_.feed_count++;
    save_persistent_data_();
    ESP_LOGI(TAG, "Feed done (count=%u)", persistent_.feed_count);
    set_state_(State::IDLE);
  });
}

void FishFeeder::dump_config() {
  ESP_LOGCONFIG(TAG, "Fish Feeder");
  ESP_LOGCONFIG(TAG, "  Servo configured: %s", servo_ != nullptr ? "yes" : "no");
  ESP_LOGCONFIG(TAG, "  Open angle: %.1f", open_angle_);
  ESP_LOGCONFIG(TAG, "  Close angle: %.1f", close_angle_);
  ESP_LOGCONFIG(TAG, "  Open duration: %u ms", open_duration_ms_);
  ESP_LOGCONFIG(TAG, "  Feed count: %u", persistent_.feed_count);
}

void FishFeeder::set_state_(State state) {
  state_ = state;
  ESP_LOGD(TAG, "State -> %s", FishFeederState::to_string(state_));
}

// Servo control
void FishFeeder::open_servo_() {
  ESP_LOGD(TAG, "Opening servo");
  set_state_(State::OPENING);
  servo_->write(open_angle_);
}

void FishFeeder::close_servo_() {
  ESP_LOGD(TAG, "Closing servo");
  set_state_(State::CLOSING);
  servo_->write(close_angle_);
}

void FishFeeder::reset_counter() {
    persistent_.feed_count = 0;
    save_persistent_data_();

  ESP_LOGI(TAG, "Feed counter reset");
}

void FishFeeder::load_persistent_data_() {
    if (!pref_.load(&persistent_)) {
        ESP_LOGI(TAG, "No persistent data found");

        persistent_.version = 1;
        persistent_.feed_count = 0;

        save_persistent_data_();
    }

    ESP_LOGI(TAG, "Feed count restored: %u", persistent_.feed_count);
}

void FishFeeder::save_persistent_data_() {
    pref_.save(&persistent_);
}

}  // namespace fish_feeder
}  // namespace esphome