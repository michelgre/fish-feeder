namespace esphome {
namespace fish_feeder {

enum State {
  IDLE,
  OPENING,
  WAITING,
  CLOSING,
};

namespace FishFeederState {

static inline const char* to_string(State state) {
  switch (state) {
    case IDLE: return "IDLE";
    case OPENING: return "OPENING";
    case WAITING: return "WAITING";
    case CLOSING: return "CLOSING";
    default: return "UNKNOWN";
  }
}

}
}  // namespace fish_feeder
}  // namespace esphome