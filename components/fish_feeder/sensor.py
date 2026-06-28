import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import STATE_CLASS_TOTAL_INCREASING

from . import FishFeeder, fish_feeder_ns

DEPENDENCIES = ["fish_feeder"]

FeedCountSensor = fish_feeder_ns.class_("FeedCountSensor", sensor.Sensor)

FEED_COUNT_SCHEMA = sensor.sensor_schema(
    unit_of_measurement="feeds",
    accuracy_decimals=0,
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(FishFeeder),
        cv.Required("fish_feeder_id"): cv.use_id(FishFeeder),

        cv.Optional("feed_count"): FEED_COUNT_SCHEMA,
    }
)

async def to_code(config):
    feeder = await cg.get_variable(config["fish_feeder_id"])

    if "feed_count" in config:
        sens = await sensor.new_sensor(config["feed_count"])
        cg.add(feeder.set_feed_count_sensor(sens))
        