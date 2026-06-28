#pragma once

#include "esphome/core/automation.h"
#include "fish_feeder.h"

namespace esphome {
namespace fish_feeder {

template<typename... Ts>
class FeedAction : public Action<Ts...> {
 public:
  explicit FeedAction(FishFeeder *parent) : parent_(parent) {}

  void play(Ts... x) override {
    this->parent_->feed();
  }

 protected:
  FishFeeder *parent_;
};

template<typename... Ts>
class ResetAction : public Action<Ts...> {
 public:
  explicit ResetAction(FishFeeder *parent) : parent_(parent) {}

  void play(Ts... x) override {
    this->parent_->reset();
  }

 protected:
  FishFeeder *parent_;
};

}  // namespace fish_feeder
}  // namespace esphome