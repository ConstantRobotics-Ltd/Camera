#include "Camera.h"
#include "CameraVersion.h"



/// Get camera controller version.
std::string cr::camera::Camera::getVersion()
{
    return CAMERA_VERSION;
}



/// Copy operator.
cr::camera::CameraParams &cr::camera::CameraParams::operator= (const cr::camera::CameraParams &src)
{
    // Check yourself.
    if (this == &src)
        return *this;

    // Copy params.
    initString = src.initString;
    width = src.width;
    height = src.height;
    displayMode = src.displayMode;
    videoOutput = src.videoOutput;
    logMode = src.logMode;
    exposureMode = src.exposureMode;
    exposureTime = src.exposureTime;
    whiteBalanceMode = src.whiteBalanceMode;
    whiteBalanceArea = src.whiteBalanceArea;
    wideDynamicRangeMode = src.wideDynamicRangeMode;
    stabilisationMode = src.stabilisationMode;
    isoSensetivity = src.isoSensetivity;
    sceneMode = src.sceneMode;
    fps = src.fps;
    brightnessMode = src.brightnessMode;
    brightness = src.brightness;
    contrast = src.contrast;
    gainMode = src.gainMode;
    gain = src.gain;
    sharpeningMode = src.sharpeningMode;
    sharpening = src.sharpening;
    palette = src.palette;
    agcMode = src.agcMode;
    shutterMode = src.shutterMode;
    shutterPos = src.shutterPos;
    shutterSpeed = src.shutterSpeed;
    digitalZoomMode = src.digitalZoomMode;
    digitalZoom = src.digitalZoom;
    exposureCompensationMode = src.exposureCompensationMode;
    exposureCompensationPosition = src.exposureCompensationPosition;
    defogMode = src.defogMode;
    dehazeMode = src.dehazeMode;
    noiseReductionMode = src.noiseReductionMode;
    blackAndWhiteFilterMode = src.blackAndWhiteFilterMode;
    filterMode = src.filterMode;
    nucMode = src.nucMode;
    autoNucIntervalMsec = src.autoNucIntervalMsec;
    imageFlip = src.imageFlip;
    ddeMode = src.ddeMode;
    ddeLevel = src.ddeLevel;
    roiX0 = src.roiX0;
    roiY0 = src.roiY0;
    roiX1 = src.roiX1;
    roiY1 = src.roiY1;
    temperature = src.temperature;
    alcGate = src.alcGate;
    sensitivity = src.sensitivity;
    changingMode = src.changingMode;
    changingLevel = src.changingLevel;
    chromeLevel = src.chromeLevel;
    detail = src.detail;
    profile = src.profile;
    isConnected = src.isConnected;
    isOpen = src.isOpen;
    type = src.type;
    custom1 = src.custom1;
    custom2 = src.custom2;
    custom3 = src.custom3;

    return *this;
}



/// Encode params.
void cr::camera::CameraParams::encode(uint8_t* data, int& size)
{
    // Encode version.
    int pos = 0;
    data[pos] = 0x02; pos += 1;
    data[pos] = CAMERA_MAJOR_VERSION; pos += 1;
    data[pos] = CAMERA_MINOR_VERSION; pos += 1;

    // Encode data.
    memcpy(&data[pos], &width, 4); pos += 4;
    memcpy(&data[pos], &height, 4); pos += 4;
    memcpy(&data[pos], &displayMode, 4); pos += 4;
    memcpy(&data[pos], &videoOutput, 4); pos += 4;
    memcpy(&data[pos], &logMode, 4); pos += 4;
    memcpy(&data[pos], &exposureMode, 4); pos += 4;
    memcpy(&data[pos], &exposureTime, 4); pos += 4;
    memcpy(&data[pos], &whiteBalanceMode, 4); pos += 4;
    memcpy(&data[pos], &whiteBalanceArea, 4); pos += 4;
    memcpy(&data[pos], &wideDynamicRangeMode, 4); pos += 4;
    memcpy(&data[pos], &stabilisationMode, 4); pos += 4;
    memcpy(&data[pos], &isoSensetivity, 4); pos += 4;
    memcpy(&data[pos], &sceneMode, 4); pos += 4;
    memcpy(&data[pos], &fps, 4); pos += 4;
    memcpy(&data[pos], &brightnessMode, 4); pos += 4;
    memcpy(&data[pos], &brightness, 4); pos += 4;
    memcpy(&data[pos], &contrast, 4); pos += 4;
    memcpy(&data[pos], &gainMode, 4); pos += 4;
    memcpy(&data[pos], &gain, 4); pos += 4;
    memcpy(&data[pos], &sharpeningMode, 4); pos += 4;
    memcpy(&data[pos], &sharpening, 4); pos += 4;
    memcpy(&data[pos], &palette, 4); pos += 4;
    memcpy(&data[pos], &agcMode, 4); pos += 4;
    memcpy(&data[pos], &shutterMode, 4); pos += 4;
    memcpy(&data[pos], &shutterPos, 4); pos += 4;
    memcpy(&data[pos], &shutterSpeed, 4); pos += 4;
    memcpy(&data[pos], &digitalZoomMode, 4); pos += 4;
    memcpy(&data[pos], &digitalZoom, 4); pos += 4;
    memcpy(&data[pos], &exposureCompensationMode, 4); pos += 4;
    memcpy(&data[pos], &exposureCompensationPosition, 4); pos += 4;
    memcpy(&data[pos], &defogMode, 4); pos += 4;
    memcpy(&data[pos], &dehazeMode, 4); pos += 4;
    memcpy(&data[pos], &noiseReductionMode, 4); pos += 4;
    memcpy(&data[pos], &blackAndWhiteFilterMode, 4); pos += 4;
    memcpy(&data[pos], &filterMode, 4); pos += 4;
    memcpy(&data[pos], &nucMode, 4); pos += 4;
    memcpy(&data[pos], &autoNucIntervalMsec, 4); pos += 4;
    memcpy(&data[pos], &imageFlip, 4); pos += 4;
    memcpy(&data[pos], &ddeMode, 4); pos += 4;
    memcpy(&data[pos], &ddeLevel, 4); pos += 4;
    memcpy(&data[pos], &roiX0, 4); pos += 4;
    memcpy(&data[pos], &roiY0, 4); pos += 4;
    memcpy(&data[pos], &roiX1, 4); pos += 4;
    memcpy(&data[pos], &roiY1, 4); pos += 4;
    memcpy(&data[pos], &temperature, 4); pos += 4;
    memcpy(&data[pos], &alcGate, 4); pos += 4;
    memcpy(&data[pos], &sensitivity, 4); pos += 4;
    memcpy(&data[pos], &changingMode, 4); pos += 4;
    memcpy(&data[pos], &changingLevel, 4); pos += 4;
    memcpy(&data[pos], &chromeLevel, 4); pos += 4;
    memcpy(&data[pos], &detail, 4); pos += 4;
    memcpy(&data[pos], &profile, 4); pos += 4;
    data[pos] = isConnected == true ? 0x01 : 0x00; pos += 1;
    data[pos] = isOpen == true ? 0x01 : 0x00; pos += 1;
    memcpy(&data[pos], &type, 4); pos += 4;
    memcpy(&data[pos], &custom1, 4); pos += 4;
    memcpy(&data[pos], &custom2, 4); pos += 4;
    memcpy(&data[pos], &custom3, 4); pos += 4;

    size = pos;
}



/// Decode params.
bool cr::camera::CameraParams::decode(uint8_t* data)
{
    // Check header.
    if (data[0] != 0x02)
        return false;

    // Check version.
    if (data[1] != CAMERA_MAJOR_VERSION || data[2] != CAMERA_MINOR_VERSION)
        return false;

    // Decode data.
    int pos = 3;

    memcpy(&width, &data[pos], 4); pos += 4;
    memcpy(&height, &data[pos], 4); pos += 4;
    memcpy(&displayMode, &data[pos], 4); pos += 4;
    memcpy(&videoOutput, &data[pos], 4); pos += 4;
    memcpy(&logMode, &data[pos], 4); pos += 4;
    memcpy(&exposureMode, &data[pos], 4); pos += 4;
    memcpy(&exposureTime, &data[pos], 4); pos += 4;
    memcpy(&whiteBalanceMode, &data[pos], 4); pos += 4;
    memcpy(&whiteBalanceArea, &data[pos], 4); pos += 4;
    memcpy(&wideDynamicRangeMode, &data[pos], 4); pos += 4;
    memcpy(&stabilisationMode, &data[pos], 4); pos += 4;
    memcpy(&isoSensetivity, &data[pos], 4); pos += 4;
    memcpy(&sceneMode, &data[pos], 4); pos += 4;
    memcpy(&fps, &data[pos], 4); pos += 4;
    memcpy(&brightnessMode, &data[pos], 4); pos += 4;
    memcpy(&brightness, &data[pos], 4); pos += 4;
    memcpy(&contrast, &data[pos], 4); pos += 4;
    memcpy(&gainMode, &data[pos], 4); pos += 4;
    memcpy(&gain, &data[pos], 4); pos += 4;
    memcpy(&sharpeningMode, &data[pos], 4); pos += 4;
    memcpy(&sharpening, &data[pos], 4); pos += 4;
    memcpy(&palette, &data[pos], 4); pos += 4;
    memcpy(&agcMode, &data[pos], 4); pos += 4;
    memcpy(&shutterMode, &data[pos], 4); pos += 4;
    memcpy(&shutterPos, &data[pos], 4); pos += 4;
    memcpy(&shutterSpeed, &data[pos], 4); pos += 4;
    memcpy(&digitalZoomMode, &data[pos], 4); pos += 4;
    memcpy(&digitalZoom, &data[pos], 4); pos += 4;
    memcpy(&exposureCompensationMode, &data[pos], 4); pos += 4;
    memcpy(&exposureCompensationPosition, &data[pos], 4); pos += 4;
    memcpy(&defogMode, &data[pos], 4); pos += 4;
    memcpy(&dehazeMode, &data[pos], 4); pos += 4;
    memcpy(&noiseReductionMode, &data[pos], 4); pos += 4;
    memcpy(&blackAndWhiteFilterMode, &data[pos], 4); pos += 4;
    memcpy(&filterMode, &data[pos], 4); pos += 4;
    memcpy(&nucMode, &data[pos], 4); pos += 4;
    memcpy(&autoNucIntervalMsec, &data[pos], 4); pos += 4;
    memcpy(&imageFlip, &data[pos], 4); pos += 4;
    memcpy(&ddeMode, &data[pos], 4); pos += 4;
    memcpy(&ddeLevel, &data[pos], 4); pos += 4;
    memcpy(&roiX0, &data[pos], 4); pos += 4;
    memcpy(&roiY0, &data[pos], 4); pos += 4;
    memcpy(&roiX1, &data[pos], 4); pos += 4;
    memcpy(&roiY1, &data[pos], 4); pos += 4;
    memcpy(&temperature, &data[pos], 4); pos += 4;
    memcpy(&alcGate, &data[pos], 4); pos += 4;
    memcpy(&sensitivity, &data[pos], 4); pos += 4;
    memcpy(&changingMode, &data[pos], 4); pos += 4;
    memcpy(&changingLevel, &data[pos], 4); pos += 4;
    memcpy(&chromeLevel, &data[pos], 4); pos += 4;
    memcpy(&detail, &data[pos], 4); pos += 4;
    memcpy(&profile, &data[pos], 4); pos += 4;
    isConnected = data[pos] == 0x00 ? false : true; pos += 1;
    isOpen = data[pos] == 0x00 ? false : true; pos += 1;
    memcpy(&type, &data[pos], 4); pos += 4;
    memcpy(&custom1, &data[pos], 4); pos += 4;
    memcpy(&custom2, &data[pos], 4); pos += 4;
    memcpy(&custom3, &data[pos], 4);

    initString = "";

    return true;
}



/// Encode set param command.
void cr::camera::Camera::encodeSetParamCommand(
        uint8_t* data, int& size, CameraParam id, float value)
{
    // Fill header.
    data[0] = 0x01;
    data[1] = CAMERA_MAJOR_VERSION;
    data[2] = CAMERA_MINOR_VERSION;

    // Fill data.
    int paramId = (int)id;
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], &value, 4);
    size = 11;
}



/// Encode command.
void cr::camera::Camera::encodeCommand(uint8_t* data,
                                   int& size,
                                   cr::camera::CameraCommand id)
{
    // Fill header.
    data[0] = 0x00;
    data[1] = CAMERA_MAJOR_VERSION;
    data[2] = CAMERA_MINOR_VERSION;

    // Fill data.
    int commandId = (int)id;
    memcpy(&data[3], &commandId, 4);
    size = 7;
}



/// Decode command.
int cr::camera::Camera::decodeCommand(uint8_t* data,
                                  int size,
                                  cr::camera::CameraParam& paramId,
                                  cr::camera::CameraCommand& commandId,
                                  float& value)
{
    // Check size.
    if (size < 7)
        return -1;

    // Check version.
    if (data[1] != CAMERA_MAJOR_VERSION || data[2] != CAMERA_MINOR_VERSION)
        return -1;

    // Extract data.
    int id = 0;
    memcpy(&id, &data[3], 4);
    value = 0.0f;


    // Check command type.
    if (data[0] == 0x00)
    {
        commandId = (CameraCommand)id;
        return 0;
    }
    else if (data[0] == 0x01)
    {
        // Check size.
        if (size != 11)
            return false;

        paramId = (CameraParam)id;
        memcpy(&value, &data[7], 4);
        return 1;
    }

    return -1;
}


