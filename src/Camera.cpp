#include "Camera.h"
#include "CameraVersion.h"



cr::camera::Camera::~Camera()
{

}



std::string cr::camera::Camera::getVersion()
{
    return CAMERA_VERSION;
}



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
    stabilizationMode = src.stabilizationMode;
    isoSensitivity = src.isoSensitivity;
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
    chromaLevel = src.chromaLevel;
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



bool cr::camera::CameraParams::encode(
    uint8_t* data, int bufferSize, int& size, CameraParamsMask* mask)
{
    // Check buffer size.
    if (bufferSize < 237)
        return false;

    // Encode version.
    int pos = 0;
    data[pos] = 0x02; pos += 1;
    data[pos] = CAMERA_MAJOR_VERSION; pos += 1;
    data[pos] = CAMERA_MINOR_VERSION; pos += 1;

    // Default parameters mask.
    CameraParamsMask defaultMask;
    if (mask == nullptr)
        mask = &defaultMask;

    // Prepare mask.
    data[pos] = 0;
    data[pos] = data[pos] | (mask->width ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->height ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->displayMode ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->videoOutput ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->logMode ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->exposureMode ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->exposureTime ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->whiteBalanceMode ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->whiteBalanceArea ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->wideDynamicRangeMode ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->stabilizationMode ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->isoSensitivity ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->sceneMode ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->fps ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->brightnessMode ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->brightness ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->contrast ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->gainMode ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->gain ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->sharpeningMode ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->sharpening ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->palette ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->agcMode ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->shutterMode ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->shutterPos ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->shutterSpeed ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->digitalZoomMode ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->digitalZoom ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->exposureCompensationMode ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->exposureCompensationPosition ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->defogMode ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->dehazeMode ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->noiseReductionMode ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->blackAndWhiteFilterMode ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->filterMode ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->nucMode ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->autoNucIntervalMsec ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->imageFlip ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->ddeMode ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->ddeLevel ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->roiX0 ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->roiY0 ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->roiX1 ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->roiY1 ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->temperature ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->alcGate ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->sensitivity ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->changingMode ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->changingLevel ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->chromaLevel ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->detail ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->profile ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->isConnected ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->isOpen ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->type ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->custom1 ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->custom2 ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->custom3 ? (uint8_t)64 : (uint8_t)0);
    pos += 1;

    // Encode data.
    if (mask->width)
    {
        memcpy(&data[pos], &width, 4); pos += 4;
    }
    if (mask->height)
    {
        memcpy(&data[pos], &height, 4); pos += 4;
    }
    if (mask->displayMode)
    {
        memcpy(&data[pos], &displayMode, 4); pos += 4;
    }
    if (mask->videoOutput)
    {
        memcpy(&data[pos], &videoOutput, 4); pos += 4;
    }
    if (mask->logMode)
    {
        memcpy(&data[pos], &logMode, 4); pos += 4;
    }
    if (mask->exposureMode)
    {
        memcpy(&data[pos], &exposureMode, 4); pos += 4;
    }
    if (mask->exposureTime)
    {
        memcpy(&data[pos], &exposureTime, 4); pos += 4;
    }
    if (mask->whiteBalanceMode)
    {
        memcpy(&data[pos], &whiteBalanceMode, 4); pos += 4;
    }

    if (mask->whiteBalanceArea)
    {
        memcpy(&data[pos], &whiteBalanceArea, 4); pos += 4;
    }
    if (mask->wideDynamicRangeMode)
    {
        memcpy(&data[pos], &wideDynamicRangeMode, 4); pos += 4;
    }
    if (mask->stabilizationMode)
    {
        memcpy(&data[pos], &stabilizationMode, 4); pos += 4;
    }
    if (mask->isoSensitivity)
    {
        memcpy(&data[pos], &isoSensitivity, 4); pos += 4;
    }
    if (mask->sceneMode)
    {
        memcpy(&data[pos], &sceneMode, 4); pos += 4;
    }
    if (mask->fps)
    {
        memcpy(&data[pos], &fps, 4); pos += 4;
    }
    if (mask->brightnessMode)
    {
        memcpy(&data[pos], &brightnessMode, 4); pos += 4;
    }
    if (mask->brightness)
    {
        memcpy(&data[pos], &brightness, 4); pos += 4;
    }

    if (mask->contrast)
    {
        memcpy(&data[pos], &contrast, 4); pos += 4;
    }
    if (mask->gainMode)
    {
        memcpy(&data[pos], &gainMode, 4); pos += 4;
    }
    if (mask->gain)
    {
        memcpy(&data[pos], &gain, 4); pos += 4;
    }
    if (mask->sharpeningMode)
    {
        memcpy(&data[pos], &sharpeningMode, 4); pos += 4;
    }
    if (mask->sharpening)
    {
        memcpy(&data[pos], &sharpening, 4); pos += 4;
    }
    if (mask->palette)
    {
        memcpy(&data[pos], &palette, 4); pos += 4;
    }
    if (mask->agcMode)
    {
        memcpy(&data[pos], &agcMode, 4); pos += 4;
    }
    if (mask->shutterMode)
    {
        memcpy(&data[pos], &shutterMode, 4); pos += 4;
    }

    if (mask->shutterPos)
    {
        memcpy(&data[pos], &shutterPos, 4); pos += 4;
    }
    if (mask->shutterSpeed)
    {
        memcpy(&data[pos], &shutterSpeed, 4); pos += 4;
    }
    if (mask->digitalZoomMode)
    {
        memcpy(&data[pos], &digitalZoomMode, 4); pos += 4;
    }
    if (mask->digitalZoom)
    {
        memcpy(&data[pos], &digitalZoom, 4); pos += 4;
    }
    if (mask->exposureCompensationMode)
    {
        memcpy(&data[pos], &exposureCompensationMode, 4); pos += 4;
    }
    if (mask->exposureCompensationPosition)
    {
        memcpy(&data[pos], &exposureCompensationPosition, 4); pos += 4;
    }
    if (mask->defogMode)
    {
        memcpy(&data[pos], &defogMode, 4); pos += 4;
    }
    if (mask->dehazeMode)
    {
        memcpy(&data[pos], &dehazeMode, 4); pos += 4;
    }

    if (mask->noiseReductionMode)
    {
        memcpy(&data[pos], &noiseReductionMode, 4); pos += 4;
    }
    if (mask->blackAndWhiteFilterMode)
    {
        memcpy(&data[pos], &blackAndWhiteFilterMode, 4); pos += 4;
    }
    if (mask->filterMode)
    {
        memcpy(&data[pos], &filterMode, 4); pos += 4;
    }
    if (mask->nucMode)
    {
        memcpy(&data[pos], &nucMode, 4); pos += 4;
    }
    if (mask->autoNucIntervalMsec)
    {
        memcpy(&data[pos], &autoNucIntervalMsec, 4); pos += 4;
    }
    if (mask->imageFlip)
    {
        memcpy(&data[pos], &imageFlip, 4); pos += 4;
    }
    if (mask->ddeMode)
    {
        memcpy(&data[pos], &ddeMode, 4); pos += 4;
    }
    if (mask->ddeLevel)
    {
        memcpy(&data[pos], &ddeLevel, 4); pos += 4;
    }

    if (mask->roiX0)
    {
        memcpy(&data[pos], &roiX0, 4); pos += 4;
    }
    if (mask->roiY0)
    {
        memcpy(&data[pos], &roiY0, 4); pos += 4;
    }
    if (mask->roiX1)
    {
        memcpy(&data[pos], &roiX1, 4); pos += 4;
    }
    if (mask->roiY1)
    {
        memcpy(&data[pos], &roiY1, 4); pos += 4;
    }
    if (mask->temperature)
    {
        memcpy(&data[pos], &temperature, 4); pos += 4;
    }
    if (mask->alcGate)
    {
        memcpy(&data[pos], &alcGate, 4); pos += 4;
    }
    if (mask->sensitivity)
    {
        memcpy(&data[pos], &sensitivity, 4); pos += 4;
    }
    if (mask->changingMode)
    {
        memcpy(&data[pos], &changingMode, 4); pos += 4;
    }

    if (mask->changingLevel)
    {
        memcpy(&data[pos], &changingLevel, 4); pos += 4;
    }
    if (mask->chromaLevel)
    {
        memcpy(&data[pos], &chromaLevel, 4); pos += 4;
    }
    if (mask->detail)
    {
        memcpy(&data[pos], &detail, 4); pos += 4;
    }
    if (mask->profile)
    {
        memcpy(&data[pos], &profile, 4); pos += 4;
    }
    if (mask->isConnected)
    {
        data[pos] = isConnected == true ? 0x01 : 0x00; pos += 1;
    }
    if (mask->isOpen)
    {
        data[pos] = isOpen == true ? 0x01 : 0x00; pos += 1;
    }
    if (mask->type)
    {
        memcpy(&data[pos], &type, 4); pos += 4;
    }
    if (mask->custom1)
    {
        memcpy(&data[pos], &custom1, 4); pos += 4;
    }

    if (mask->custom2)
    {
        memcpy(&data[pos], &custom2, 4); pos += 4;
    }
    if (mask->custom3)
    {
        memcpy(&data[pos], &custom3, 4); pos += 4;
    }

    size = pos;

    return true;
}



bool cr::camera::CameraParams::decode(uint8_t* data, int dataSize)
{
    // Check data size.
    if (dataSize < 12)
        return false;

    // Check header.
    if (data[0] != 0x02)
        return false;

    // Check version.
    if (data[1] != CAMERA_MAJOR_VERSION ||
        data[2] != CAMERA_MINOR_VERSION)
        return false;

    // Decode data.
    int pos = 11;

    if ((data[3] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&width, &data[pos], 4); pos += 4;
    }
    else
    {
        width = 0;
    }
    if ((data[3] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&height, &data[pos], 4); pos += 4;
    }
    else
    {
        height = 0;
    }
    if ((data[3] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&displayMode, &data[pos], 4); pos += 4;
    }
    else
    {
        displayMode = 0;
    }
    if ((data[3] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&videoOutput, &data[pos], 4); pos += 4;
    }
    else
    {
        videoOutput = 0;
    }
    if ((data[3] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&logMode, &data[pos], 4); pos += 4;
    }
    else
    {
        logMode = 0;
    }
    if ((data[3] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&exposureMode, &data[pos], 4); pos += 4;
    }
    else
    {
        exposureMode = 0;
    }
    if ((data[3] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&exposureTime, &data[pos], 4); pos += 4;
    }
    else
    {
        exposureTime = 0;
    }
    if ((data[3] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&whiteBalanceMode, &data[pos], 4); pos += 4;
    }
    else
    {
        whiteBalanceMode = 0;
    }



    if ((data[4] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&whiteBalanceArea, &data[pos], 4); pos += 4;
    }
    else
    {
        whiteBalanceArea = 0;
    }
    if ((data[4] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&wideDynamicRangeMode, &data[pos], 4); pos += 4;
    }
    else
    {
        wideDynamicRangeMode = 0;
    }
    if ((data[4] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&stabilizationMode, &data[pos], 4); pos += 4;
    }
    else
    {
        stabilizationMode = 0;
    }
    if ((data[4] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&isoSensitivity, &data[pos], 4); pos += 4;
    }
    else
    {
        isoSensitivity = 0;
    }
    if ((data[4] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&sceneMode, &data[pos], 4); pos += 4;
    }
    else
    {
        sceneMode = 0;
    }
    if ((data[4] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&fps, &data[pos], 4); pos += 4;
    }
    else
    {
        fps = 0.0f;
    }
    if ((data[4] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&brightnessMode, &data[pos], 4); pos += 4;
    }
    else
    {
        brightnessMode = 0;
    }
    if ((data[4] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&brightness, &data[pos], 4); pos += 4;
    }
    else
    {
        brightness = 0;
    }



    if ((data[5] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&contrast, &data[pos], 4); pos += 4;
    }
    else
    {
        contrast = 0;
    }
    if ((data[5] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&gainMode, &data[pos], 4); pos += 4;
    }
    else
    {
        gainMode = 0;
    }
    if ((data[5] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&gain, &data[pos], 4); pos += 4;
    }
    else
    {
        gain = 0;
    }
    if ((data[5] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&sharpeningMode, &data[pos], 4); pos += 4;
    }
    else
    {
        sharpeningMode = 0;
    }
    if ((data[5] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&sharpening, &data[pos], 4); pos += 4;
    }
    else
    {
        sharpening = 0;
    }
    if ((data[5] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&palette, &data[pos], 4); pos += 4;
    }
    else
    {
        palette = 0;
    }
    if ((data[5] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&agcMode, &data[pos], 4); pos += 4;
    }
    else
    {
        agcMode = 0;
    }
    if ((data[5] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&shutterMode, &data[pos], 4); pos += 4;
    }
    else
    {
        shutterMode = 0;
    }


    if ((data[6] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&shutterPos, &data[pos], 4); pos += 4;
    }
    else
    {
        shutterPos = 0;
    }
    if ((data[6] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&shutterSpeed, &data[pos], 4); pos += 4;
    }
    else
    {
        shutterSpeed = 0;
    }
    if ((data[6] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&digitalZoomMode, &data[pos], 4); pos += 4;
    }
    else
    {
        digitalZoomMode = 0;
    }
    if ((data[6] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&digitalZoom, &data[pos], 4); pos += 4;
    }
    else
    {
        digitalZoom = 0.0f;
    }
    if ((data[6] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&exposureCompensationMode, &data[pos], 4); pos += 4;
    }
    else
    {
        exposureCompensationMode = 0;
    }
    if ((data[6] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&exposureCompensationPosition, &data[pos], 4); pos += 4;
    }
    else
    {
        exposureCompensationPosition = 0;
    }
    if ((data[6] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&defogMode, &data[pos], 4); pos += 4;
    }
    else
    {
        defogMode = 0;
    }
    if ((data[6] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&dehazeMode, &data[pos], 4); pos += 4;
    }
    else
    {
        dehazeMode = 0;
    }



    if ((data[7] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&noiseReductionMode, &data[pos], 4); pos += 4;
    }
    else
    {
        noiseReductionMode = 0;
    }
    if ((data[7] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&blackAndWhiteFilterMode, &data[pos], 4); pos += 4;
    }
    else
    {
        blackAndWhiteFilterMode = 0;
    }
    if ((data[7] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&filterMode, &data[pos], 4); pos += 4;
    }
    else
    {
        filterMode = 0;
    }
    if ((data[7] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&nucMode, &data[pos], 4); pos += 4;
    }
    else
    {
        nucMode = 0;
    }
    if ((data[7] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&autoNucIntervalMsec, &data[pos], 4); pos += 4;
    }
    else
    {
        autoNucIntervalMsec = 0;
    }
    if ((data[7] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&imageFlip, &data[pos], 4); pos += 4;
    }
    else
    {
        imageFlip = 0;
    }
    if ((data[7] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&ddeMode, &data[pos], 4); pos += 4;
    }
    else
    {
        ddeMode = 0;
    }
    if ((data[7] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&ddeLevel, &data[pos], 4); pos += 4;
    }
    else
    {
        ddeLevel = 0.0f;
    }



    if ((data[8] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&roiX0, &data[pos], 4); pos += 4;
    }
    else
    {
        roiX0 = 0;
    }
    if ((data[8] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&roiY0, &data[pos], 4); pos += 4;
    }
    else
    {
        roiY0 = 0;
    }
    if ((data[8] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&roiX1, &data[pos], 4); pos += 4;
    }
    else
    {
        roiX1 = 0;
    }
    if ((data[8] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&roiY1, &data[pos], 4); pos += 4;
    }
    else
    {
        roiY1 = 0;
    }
    if ((data[8] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&temperature, &data[pos], 4); pos += 4;
    }
    else
    {
        temperature = 0.0f;
    }
    if ((data[8] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&alcGate, &data[pos], 4); pos += 4;
    }
    else
    {
        alcGate = 0;
    }
    if ((data[8] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&sensitivity, &data[pos], 4); pos += 4;
    }
    else
    {
        sensitivity = 0;
    }
    if ((data[8] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&changingMode, &data[pos], 4); pos += 4;
    }
    else
    {
        changingMode = 0;
    }



    if ((data[9] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&changingLevel, &data[pos], 4); pos += 4;
    }
    else
    {
        changingLevel = 0.0f;
    }
    if ((data[9] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&chromaLevel, &data[pos], 4); pos += 4;
    }
    else
    {
        chromaLevel = 0;
    }
    if ((data[9] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&detail, &data[pos], 4); pos += 4;
    }
    else
    {
        detail = 0;
    }
    if ((data[9] & (uint8_t)16) == (uint8_t)16)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&profile, &data[pos], 4); pos += 4;
    }
    else
    {
        profile = 0;
    }
    if ((data[9] & (uint8_t)8) == (uint8_t)8)
    {
        if (dataSize < pos + 1)
            return false;
        isConnected = data[pos] == 0x00 ? false : true; pos += 1;
    }
    else
    {
        isConnected = false;
    }
    if ((data[9] & (uint8_t)4) == (uint8_t)4)
    {
        if (dataSize < pos + 1)
            return false;
        isOpen = data[pos] == 0x00 ? false : true; pos += 1;
    }
    else
    {
        isOpen = false;
    }
    if ((data[9] & (uint8_t)2) == (uint8_t)2)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&type, &data[pos], 4); pos += 4;
    }
    else
    {
        type = 0;
    }
    if ((data[9] & (uint8_t)1) == (uint8_t)1)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&custom1, &data[pos], 4); pos += 4;
    }
    else
    {
        custom1 = 0.0f;
    }



    if ((data[10] & (uint8_t)128) == (uint8_t)128)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&custom2, &data[pos], 4); pos += 4;
    }
    else
    {
        custom2 = 0.0f;
    }
    if ((data[10] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
            return false;
        memcpy(&custom3, &data[pos], 4);
    }
    else
    {
        custom3 = 0.0f;
    }

    initString = "";

    return true;
}



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
