#pragma once

#include "esphome/core/component.h"
#include "esphome/components/servo/servo.h"

namespace esphome {
namespace fish_feeder {

class FishFeeder : public Component {
 public:
  void set_servo(servo::Servo *servo) { servo_ = servo; }

  void setup() override;
  void loop() override;

  void feed();
  void reset();

 protected:
  servo::Servo *servo_{nullptr};
  bool busy_{false};
  uint32_t feed_count_{0};
};

}  // namespace fish_feeder
}  // namespace esphome