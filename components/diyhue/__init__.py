import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect, LightEffect
from esphome.components.light.effects import (
    register_addressable_effect,
    register_rgb_effect,
)
from esphome.const import CONF_ID, CONF_NAME

DEPENDENCIES = ["network"]

diyhue_ns = cg.esphome_ns.namespace("diyhue")
DiyHueLightEffect = diyhue_ns.class_("DiyHueLightEffect", LightEffect)
DiyHueAddressableLightEffect = diyhue_ns.class_(
    "DiyHueAddressableLightEffect", AddressableLightEffect
)
DiyHueComponent = diyhue_ns.class_("DiyHueComponent", cg.Component)

DIYHUE_SCALING = {
    "PIXEL":    diyhue_ns.DIYHUE_SCALE_PIXEL,
    "STRIP":    diyhue_ns.DIYHUE_SCALE_STRIP,
    "PACKET":   diyhue_ns.DIYHUE_SCALE_PACKET,
    "MULTIPLY": diyhue_ns.DIYHUE_SCALE_MULTIPLY,
    "NONE":     diyhue_ns.DIYHUE_NO_SCALING}

CONF_DIYHUE_ID = "diyhue_id"
CONF_DIYHUE_TIMEOUT = "timeout"
CONF_DIYHUE_DIS_GAMMA = "disable_gamma"
CONF_DIYHUE_SCALING = "brightness_scaling"

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DiyHueComponent),
        }
    ),
    cv.only_with_arduino,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)


@register_rgb_effect(
    "diyhue",
    DiyHueLightEffect,
    "DiyHue",
    {
        cv.GenerateID(CONF_DIYHUE_ID): cv.use_id(DiyHueComponent),
        cv.Optional(CONF_DIYHUE_TIMEOUT): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_DIYHUE_DIS_GAMMA): cv.boolean,
        cv.Optional(CONF_DIYHUE_SCALING): cv.one_of(*DIYHUE_SCALING, upper=True),
    },
)
@register_addressable_effect(
    "addressable_diyhue",
    DiyHueAddressableLightEffect,
    "Addressable DiyHue",
    {
        cv.GenerateID(CONF_DIYHUE_ID): cv.use_id(DiyHueComponent),
        cv.Optional(CONF_DIYHUE_TIMEOUT): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_DIYHUE_DIS_GAMMA): cv.boolean,
        cv.Optional(CONF_DIYHUE_SCALING): cv.one_of(*DIYHUE_SCALING, upper=True),
    },
)
async def diyhue_light_effect_to_code(config, effect_id):
    parent = await cg.get_variable(config[CONF_DIYHUE_ID])

    effect = cg.new_Pvariable(effect_id, config[CONF_NAME])

    cg.add(effect.set_diyhue(parent))

    if CONF_DIYHUE_TIMEOUT in config:
        cg.add(effect.set_timeout(config[CONF_DIYHUE_TIMEOUT]))

    if CONF_DIYHUE_DIS_GAMMA in config:
        cg.add(effect.set_disable_gamma(config[CONF_DIYHUE_DIS_GAMMA]))

    if CONF_DIYHUE_SCALING in config:
        cg.add(effect.set_scaling_mode(DIYHUE_SCALING[config[CONF_DIYHUE_SCALING]]))

    return effect
