import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import servo
from esphome.const import CONF_ID

DEPENDENCIES = ["servo"]

fish_feeder_ns = cg.esphome_ns.namespace("fish_feeder")
FishFeeder = fish_feeder_ns.class_("FishFeeder", cg.Component)

CONF_SERVO = "servo"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(FishFeeder),
        cv.Required(CONF_SERVO): cv.use_id(servo.Servo),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    servo_var = await cg.get_variable(config[CONF_SERVO])
    cg.add(var.set_servo(servo_var))