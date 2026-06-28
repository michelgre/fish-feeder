import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome import automation

from . import FishFeeder, fish_feeder_ns

FeedAction = fish_feeder_ns.class_("FeedAction", automation.Action)
ResetAction = fish_feeder_ns.class_("ResetAction", automation.Action)

@automation.register_action(
    "fish_feeder.feed",
    FeedAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(FishFeeder),
        }
    ),
    synchronous=True,
)
async def fish_feeder_feed_to_code(config, action_id, template_arg, args):
    feeder = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, feeder)
print(">>> feed action registered")


@automation.register_action(
    "fish_feeder.reset",
    ResetAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(FishFeeder),
        }
    ),
    synchronous=True,
)
async def fish_feeder_reset_to_code(config, action_id, template_arg, args):
    feeder = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, feeder)
print(">>> reset action registered")
