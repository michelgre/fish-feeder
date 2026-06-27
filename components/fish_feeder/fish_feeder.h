#pragma once

#include "esphome/core/component.h"
#include "esphome/components/servo/servo.h"

namespace esphome {
namespace fish_feeder {

class FishFeeder : public Component {
 public:
  void setup() override;
  void loop() override;

  void feed();
  void reset();

  void set_servo(servo::Servo *servo) { servo_ = servo; }

  void set_open_angle(float v) { open_angle_ = v; }
  void set_close_angle(float v) { close_angle_ = v; }
  void set_open_duration(uint32_t ms) { open_duration_ms_ = ms; }

private:
  float open_angle_{90};
  float close_angle_{0};
  uint32_t open_duration_ms_{300};

 protected:
  servo::Servo *servo_{nullptr};
  bool busy_{false};
  uint32_t feed_count_{0};
};

}  // namespace fish_feeder
}  // namespace esphome