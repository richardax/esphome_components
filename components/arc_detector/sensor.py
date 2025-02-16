import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_PIN, UNIT_VOLT, ICON_FLASH

DEPENDENCIES = ['esp32']

arc_detector_ns = cg.esphome_ns.namespace('arc_detector')
ArcDetector = arc_detector_ns.class_('ArcDetector', cg.Component, sensor.Sensor)

CONF_THRESHOLD = 'threshold'

CONFIG_SCHEMA = sensor.sensor_schema(
    ArcDetector,
    unit_of_measurement=UNIT_VOLT,
    icon=ICON_FLASH,
    accuracy_decimals=2
).extend({
    cv.Required(CONF_PIN): cv.int_,
    cv.Optional(CONF_THRESHOLD, default=500): cv.uint32_t,
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    cg.add(var.set_pin(config[CONF_PIN]))
    cg.add(var.set_threshold(config[CONF_THRESHOLD]))

