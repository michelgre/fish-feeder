import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import servo
from esphome.const import CONF_ID
from esphome import pins

DEPENDENCIES = ["servo"]

fish_feeder_ns = cg.esphome_ns.namespace("fish_feeder")
FishFeeder = fish_feeder_ns.class_("FishFeeder", cg.Component)

CONF_SERVO = "servo"
CONF_OPEN_ANGLE = "open_angle"
CONF_CLOSE_ANGLE = "close_angle"
CONF_OPEN_DURATION = "open_duration"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(FishFeeder),

        cv.Required(CONF_SERVO): cv.use_id(servo.Servo),

        cv.Optional(CONF_OPEN_ANGLE, default=90): cv.float_range(min=0.0, max=180.0),
        cv.Optional(CONF_CLOSE_ANGLE, default=0): cv.float_range(min=0.0, max=180.0),

        cv.Optional(CONF_OPEN_DURATION, default="300ms"): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    servo_var = await cg.get_variable(config[CONF_SERVO])
    cg.add(var.set_servo(servo_var))

    cg.add(var.set_open_angle(config[CONF_OPEN_ANGLE]))
    cg.add(var.set_close_angle(config[CONF_CLOSE_ANGLE]))
    cg.add(var.set_open_duration(config[CONF_OPEN_DURATION].total_milliseconds))
