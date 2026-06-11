#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<SparkFun_BMP581_Arduino_Library.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "BMP580Sensor.h"
#include "TelemetrySensor.h"
#include <SparkFun_BMP581_Arduino_Library.h>

// The BMP580 is not (yet) in the protobuf TelemetrySensorType enum, so we report it as BMP3XX
// (the closest Bosch high-accuracy pressure/temperature sensor) to avoid regenerating the
// protobufs submodule. Do not enable a real BMP3XX on the same board or they collide in
// nodeTelemetrySensorsMap.
BMP580Sensor::BMP580Sensor() : TelemetrySensor(meshtastic_TelemetrySensorType_BMP3XX, "BMP580") {}

bool BMP580Sensor::initDevice(TwoWire *bus, ScanI2C::FoundDevice *dev)
{
    LOG_INFO("Init sensor: %s", sensorName);

    int8_t rc = bmp580.beginI2C(dev->address.address, *bus);
    status = (rc == BMP5_OK);
    if (!status) {
        LOG_WARN("BMP580 beginI2C failed rc=%d", rc);
        return status;
    }

    initI2CSensor();
    return status;
}

bool BMP580Sensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_temperature = true;
    measurement->variant.environment_metrics.has_barometric_pressure = true;

    LOG_DEBUG("BMP580 getMetrics");
    bmp5_sensor_data data = {0, 0};
    int8_t rc = bmp580.getSensorData(&data);
    if (rc != BMP5_OK) {
        LOG_WARN("BMP580 getSensorData failed rc=%d", rc);
        return false;
    }

    measurement->variant.environment_metrics.temperature = data.temperature;               // already °C
    measurement->variant.environment_metrics.barometric_pressure = data.pressure / 100.0F; // Pa -> hPa

    return true;
}

#endif
