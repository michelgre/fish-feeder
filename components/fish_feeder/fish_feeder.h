#pragma once

#include "esphome/core/component.h"
#include "esphome/components/servo/servo.h"
#include "esphome/core/preferences.h"
#include "State.h"
#include "PersistentData.h"

namespace esphome {
namespace fish_feeder {

class FishFeeder : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void feed();
  void reset();

  void set_servo(servo::Servo *servo) { servo_ = servo; }

  void set_open_angle(float v) { open_angle_ = v; }
  void set_close_angle(float v) { close_angle_ = v; }
  void set_open_duration(uint32_t ms) {
    open_duration_ms_ = ms;
  }

  float get_setup_priority() const override {
    return esphome::setup_priority::BEFORE_CONNECTION;
  }

 private:
  float open_angle_{90};
  float close_angle_{0};
  uint32_t open_duration_ms_{300};
  void open_servo_();
  void close_servo_();
  void set_state_(State state);
  void publish_state_();

  // Persistant status
  void load_persistent_data_();
  void save_persistent_data_();
  void reset_counter();

 protected:
  servo::Servo *servo_{nullptr};
  State  state_{State ::IDLE};
  ESPPreferenceObject pref_;
  PersistentData persistent_;
};

}  // namespace fish_feeder
}  // namespace esphome