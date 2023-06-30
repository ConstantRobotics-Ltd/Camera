#include <iostream>
#include "Camera.h"



/// Link namesapces.
using namespace cr::camera;
using namespace std;



/// Copy test.
bool copyTest();

/// Encode/decode params test.
bool encodeDecodeParamsTest();

/// Encode/decode commands test.
bool encodeDecodeCommandsTest();

/// JSON read/write test.
bool jsonReadWriteTest();



/// Entry point.
int main(void)
{
    cout << "#####################################" << endl;
    cout << "#                                   #" << endl;
    cout << "# Camera data structures test      #" << endl;
    cout << "#                                   #" << endl;
    cout << "#####################################" << endl;
    cout << endl;

    cout << "Copy test:" << endl;
    if (copyTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode params test:" << endl;
    if (encodeDecodeParamsTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode commands test:" << endl;
    if (encodeDecodeCommandsTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "JSON read/write test:" << endl;
    if (jsonReadWriteTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    return 1;
}



// Copy test.
bool copyTest()
{
    // Prepare random params.
    CameraParams in;
    in.initString = "dfhglsjirhuhjfb";
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.displayMode = rand() % 255;
    in.videoOutput = rand() % 255;
    in.logMode = rand() % 255;
    in.exposureMode = rand() % 255;
    in.exposureTime = rand() % 255;
    in.whiteBalanceMode = rand() % 255;
    in.whiteBalanceArea = rand() % 255;
    in.wideDynamicRangeMode = rand() % 255;
    in.stabilisationMode = rand() % 255;
    in.isoSensetivity = rand() % 255;
    in.sceneMode = rand() % 255;
    in.fps = rand() % 255;
    in.brightnessMode = rand() % 255;
    in.brightness = rand() % 255;
    in.contrast = rand() % 255;
    in.gainMode = rand() % 255;
    in.gain = rand() % 255;
    in.sharpeningMode = rand() % 255;
    in.sharpening = rand() % 255;
    in.palette = rand() % 255;
    in.agcMode = rand() % 255;
    in.shutterMode = rand() % 255;
    in.shutterPos = rand() % 255;
    in.shutterSpeed = rand() % 255;
    in.digitalZoomMode = rand() % 255;
    in.digitalZoom = rand() % 255;
    in.exposureCompensationMode = rand() % 255;
    in.exposureCompensationPosition = rand() % 255;
    in.defogMode = rand() % 255;
    in.dehazeMode = rand() % 255;
    in.noiseReductionMode = rand() % 255;
    in.blackAndWhiteFilterMode = rand() % 255;
    in.filterMode = rand() % 255;
    in.nucMode = rand() % 255;
    in.autoNucIntervalMsec = rand() % 255;
    in.imageFlip = rand() % 255;
    in.ddeMode = rand() % 255;
    in.ddeLevel = rand() % 255;
    in.roiX0 = rand() % 255;
    in.roiY0 = rand() % 255;
    in.roiX1 = rand() % 255;
    in.roiY1 = rand() % 255;
    in.temperature = rand() % 255;
    in.alcGate = rand() % 255;
    in.sensitivity = rand() % 255;
    in.changingMode = rand() % 255;
    in.changingLevel = rand() % 255;
    in.chromeLevel = rand() % 255;
    in.detail = rand() % 255;
    in.profile = rand() % 255;
    in.isConnected = true;
    in.isOpen = true;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Copy params.
    CameraParams out = in;

    // Compare params.
    bool result = true;
    if (in.initString != out.initString)
    {
        cout << "in.initString" << endl;
        result = false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        result = false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        result = false;
    }
    if (in.displayMode != out.displayMode)
    {
        cout << "in.displayMode" << endl;
        result = false;
    }
    if (in.videoOutput != out.videoOutput)
    {
        cout << "in.videoOutput" << endl;
        result = false;
    }
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        result = false;
    }
    if (in.exposureMode != out.exposureMode)
    {
        cout << "in.exposureMode" << endl;
        result = false;
    }
    if (in.exposureTime != out.exposureTime)
    {
        cout << "in.exposureTime" << endl;
        result = false;
    }
    if (in.whiteBalanceMode != out.whiteBalanceMode)
    {
        cout << "in.whiteBalanceMode" << endl;
        result = false;
    }
    if (in.whiteBalanceArea != out.whiteBalanceArea)
    {
        cout << "in.whiteBalanceArea" << endl;
        result = false;
    }
    if (in.wideDynamicRangeMode != out.wideDynamicRangeMode)
    {
        cout << "in.wideDynamicRangeMode" << endl;
        result = false;
    }
    if (in.stabilisationMode != out.stabilisationMode)
    {
        cout << "in.stabilisationMode" << endl;
        result = false;
    }
    if (in.isoSensetivity != out.isoSensetivity)
    {
        cout << "in.isoSensetivity" << endl;
        result = false;
    }
    if (in.sceneMode != out.sceneMode)
    {
        cout << "in.sceneMode" << endl;
        result = false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        result = false;
    }
    if (in.brightnessMode != out.brightnessMode)
    {
        cout << "in.brightnessMode" << endl;
        result = false;
    }
    if (in.brightness != out.brightness)
    {
        cout << "in.brightness" << endl;
        result = false;
    }
    if (in.contrast != out.contrast)
    {
        cout << "in.contrast" << endl;
        result = false;
    }
    if (in.gainMode != out.gainMode)
    {
        cout << "in.gainMode" << endl;
        result = false;
    }
    if (in.gain != out.gain)
    {
        cout << "in.gain" << endl;
        result = false;
    }
    if (in.sharpeningMode != out.sharpeningMode)
    {
        cout << "in.sharpeningMode" << endl;
        result = false;
    }
    if (in.sharpening != out.sharpening)
    {
        cout << "in.sharpening" << endl;
        result = false;
    }
    if (in.palette != out.palette)
    {
        cout << "in.palette" << endl;
        result = false;
    }
    if (in.agcMode != out.agcMode)
    {
        cout << "in.agcMode" << endl;
        result = false;
    }
    if (in.shutterMode != out.shutterMode)
    {
        cout << "in.shutterMode" << endl;
        result = false;
    }
    if (in.shutterPos != out.shutterPos)
    {
        cout << "in.shutterPos" << endl;
        result = false;
    }
    if (in.shutterSpeed != out.shutterSpeed)
    {
        cout << "in.shutterSpeed" << endl;
        result = false;
    }
    if (in.digitalZoomMode != out.digitalZoomMode)
    {
        cout << "in.digitalZoomMode" << endl;
        result = false;
    }
    if (in.digitalZoom != out.digitalZoom)
    {
        cout << "in.digitalZoom" << endl;
        result = false;
    }
    if (in.exposureCompensationMode != out.exposureCompensationMode)
    {
        cout << "in.exposureCompensationMode" << endl;
        result = false;
    }
    if (in.exposureCompensationPosition != out.exposureCompensationPosition)
    {
        cout << "in.exposureCompensationPosition" << endl;
        result = false;
    }
    if (in.defogMode != out.defogMode)
    {
        cout << "in.defogMode" << endl;
        result = false;
    }
    if (in.dehazeMode != out.dehazeMode)
    {
        cout << "in.dehazeMode" << endl;
        result = false;
    }
    if (in.noiseReductionMode != out.noiseReductionMode)
    {
        cout << "in.noiseReductionMode" << endl;
        result = false;
    }
    if (in.blackAndWhiteFilterMode != out.blackAndWhiteFilterMode)
    {
        cout << "in.blackAndWhiteFilterMode" << endl;
        result = false;
    }
    if (in.filterMode != out.filterMode)
    {
        cout << "in.filterMode" << endl;
        result = false;
    }
    if (in.nucMode != out.nucMode)
    {
        cout << "in.nucMode" << endl;
        result = false;
    }
    if (in.autoNucIntervalMsec != out.autoNucIntervalMsec)
    {
        cout << "in.autoNucInterval" << endl;
        result = false;
    }
    if (in.imageFlip != out.imageFlip)
    {
        cout << "in.imageFlip" << endl;
        result = false;
    }
    if (in.ddeMode != out.ddeMode)
    {
        cout << "in.ddeMode" << endl;
        result = false;
    }
    if (in.ddeLevel != out.ddeLevel)
    {
        cout << "in.ddeLevel" << endl;
        result = false;
    }
    if (in.roiX0 != out.roiX0)
    {
        cout << "in.roiX0" << endl;
        result = false;
    }
    if (in.roiY0 != out.roiY0)
    {
        cout << "in.roiY0" << endl;
        result = false;
    }
    if (in.roiX1 != out.roiX1)
    {
        cout << "in.roiX1" << endl;
        result = false;
    }
    if (in.roiY1 != out.roiY1)
    {
        cout << "in.roiY1" << endl;
        result = false;
    }
    if (in.temperature != out.temperature)
    {
        cout << "in.temperature" << endl;
        result = false;
    }
    if (in.alcGate != out.alcGate)
    {
        cout << "in.alcGate" << endl;
        result = false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        result = false;
    }
    if (in.changingMode != out.changingMode)
    {
        cout << "in.changingMode" << endl;
        result = false;
    }
    if (in.changingLevel != out.changingLevel)
    {
        cout << "in.changingLevel" << endl;
        result = false;
    }
    if (in.detail != out.detail)
    {
        cout << "in.detail" << endl;
        result = false;
    }
    if (in.profile != out.profile)
    {
        cout << "in.profile" << endl;
        result = false;
    }
    if (in.isConnected != out.isConnected)
    {
        cout << "in.isConnected" << endl;
        result = false;
    }
    if (in.isOpen != out.isOpen)
    {
        cout << "in.isOpen" << endl;
        result = false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        result = false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        result = false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        result = false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        result = false;
    }

    return result;
}



// Encode/decode test.
bool encodeDecodeParamsTest()
{
    // Prepare random params.
    CameraParams in;
    in.initString = "dfhglsjirhuhjfb";
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.displayMode = rand() % 255;
    in.videoOutput = rand() % 255;
    in.logMode = rand() % 255;
    in.exposureMode = rand() % 255;
    in.exposureTime = rand() % 255;
    in.whiteBalanceMode = rand() % 255;
    in.whiteBalanceArea = rand() % 255;
    in.wideDynamicRangeMode = rand() % 255;
    in.stabilisationMode = rand() % 255;
    in.isoSensetivity = rand() % 255;
    in.sceneMode = rand() % 255;
    in.fps = rand() % 255;
    in.brightnessMode = rand() % 255;
    in.brightness = rand() % 255;
    in.contrast = rand() % 255;
    in.gainMode = rand() % 255;
    in.gain = rand() % 255;
    in.sharpeningMode = rand() % 255;
    in.sharpening = rand() % 255;
    in.palette = rand() % 255;
    in.agcMode = rand() % 255;
    in.shutterMode = rand() % 255;
    in.shutterPos = rand() % 255;
    in.shutterSpeed = rand() % 255;
    in.digitalZoomMode = rand() % 255;
    in.digitalZoom = rand() % 255;
    in.exposureCompensationMode = rand() % 255;
    in.exposureCompensationPosition = rand() % 255;
    in.defogMode = rand() % 255;
    in.dehazeMode = rand() % 255;
    in.noiseReductionMode = rand() % 255;
    in.blackAndWhiteFilterMode = rand() % 255;
    in.filterMode = rand() % 255;
    in.nucMode = rand() % 255;
    in.autoNucIntervalMsec = rand() % 255;
    in.imageFlip = rand() % 255;
    in.ddeMode = rand() % 255;
    in.ddeLevel = rand() % 255;
    in.roiX0 = rand() % 255;
    in.roiY0 = rand() % 255;
    in.roiX1 = rand() % 255;
    in.roiY1 = rand() % 255;
    in.temperature = rand() % 255;
    in.alcGate = rand() % 255;
    in.sensitivity = rand() % 255;
    in.changingMode = rand() % 255;
    in.changingLevel = rand() % 255;
    in.chromeLevel = rand() % 255;
    in.detail = rand() % 255;
    in.profile = rand() % 255;
    in.isConnected = true;
    in.isOpen = true;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, size);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    CameraParams out;
    if (!out.decode(data))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    bool result = true;
    if (out.initString != "")
    {
        cout << "in.initString" << endl;
        result = false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        result = false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        result = false;
    }
    if (in.displayMode != out.displayMode)
    {
        cout << "in.displayMode" << endl;
        result = false;
    }
    if (in.videoOutput != out.videoOutput)
    {
        cout << "in.videoOutput" << endl;
        result = false;
    }
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        result = false;
    }
    if (in.exposureMode != out.exposureMode)
    {
        cout << "in.exposureMode" << endl;
        result = false;
    }
    if (in.exposureTime != out.exposureTime)
    {
        cout << "in.exposureTime" << endl;
        result = false;
    }
    if (in.whiteBalanceMode != out.whiteBalanceMode)
    {
        cout << "in.whiteBalanceMode" << endl;
        result = false;
    }
    if (in.whiteBalanceArea != out.whiteBalanceArea)
    {
        cout << "in.whiteBalanceArea" << endl;
        result = false;
    }
    if (in.wideDynamicRangeMode != out.wideDynamicRangeMode)
    {
        cout << "in.wideDynamicRangeMode" << endl;
        result = false;
    }
    if (in.stabilisationMode != out.stabilisationMode)
    {
        cout << "in.stabilisationMode" << endl;
        result = false;
    }
    if (in.isoSensetivity != out.isoSensetivity)
    {
        cout << "in.isoSensetivity" << endl;
        result = false;
    }
    if (in.sceneMode != out.sceneMode)
    {
        cout << "in.sceneMode" << endl;
        result = false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        result = false;
    }
    if (in.brightnessMode != out.brightnessMode)
    {
        cout << "in.brightnessMode" << endl;
        result = false;
    }
    if (in.brightness != out.brightness)
    {
        cout << "in.brightness" << endl;
        result = false;
    }
    if (in.contrast != out.contrast)
    {
        cout << "in.contrast" << endl;
        result = false;
    }
    if (in.gainMode != out.gainMode)
    {
        cout << "in.gainMode" << endl;
        result = false;
    }
    if (in.gain != out.gain)
    {
        cout << "in.gain" << endl;
        result = false;
    }
    if (in.sharpeningMode != out.sharpeningMode)
    {
        cout << "in.sharpeningMode" << endl;
        result = false;
    }
    if (in.sharpening != out.sharpening)
    {
        cout << "in.sharpening" << endl;
        result = false;
    }
    if (in.palette != out.palette)
    {
        cout << "in.palette" << endl;
        result = false;
    }
    if (in.agcMode != out.agcMode)
    {
        cout << "in.agcMode" << endl;
        result = false;
    }
    if (in.shutterMode != out.shutterMode)
    {
        cout << "in.shutterMode" << endl;
        result = false;
    }
    if (in.shutterPos != out.shutterPos)
    {
        cout << "in.shutterPos" << endl;
        result = false;
    }
    if (in.shutterSpeed != out.shutterSpeed)
    {
        cout << "in.shutterSpeed" << endl;
        result = false;
    }
    if (in.digitalZoomMode != out.digitalZoomMode)
    {
        cout << "in.digitalZoomMode" << endl;
        result = false;
    }
    if (in.digitalZoom != out.digitalZoom)
    {
        cout << "in.digitalZoom" << endl;
        result = false;
    }
    if (in.exposureCompensationMode != out.exposureCompensationMode)
    {
        cout << "in.exposureCompensationMode" << endl;
        result = false;
    }
    if (in.exposureCompensationPosition != out.exposureCompensationPosition)
    {
        cout << "in.exposureCompensationPosition" << endl;
        result = false;
    }
    if (in.defogMode != out.defogMode)
    {
        cout << "in.defogMode" << endl;
        result = false;
    }
    if (in.dehazeMode != out.dehazeMode)
    {
        cout << "in.dehazeMode" << endl;
        result = false;
    }
    if (in.noiseReductionMode != out.noiseReductionMode)
    {
        cout << "in.noiseReductionMode" << endl;
        result = false;
    }
    if (in.blackAndWhiteFilterMode != out.blackAndWhiteFilterMode)
    {
        cout << "in.blackAndWhiteFilterMode" << endl;
        result = false;
    }
    if (in.filterMode != out.filterMode)
    {
        cout << "in.filterMode" << endl;
        result = false;
    }
    if (in.nucMode != out.nucMode)
    {
        cout << "in.nucMode" << endl;
        result = false;
    }
    if (in.autoNucIntervalMsec != out.autoNucIntervalMsec)
    {
        cout << "in.autoNucInterval" << endl;
        result = false;
    }
    if (in.imageFlip != out.imageFlip)
    {
        cout << "in.imageFlip" << endl;
        result = false;
    }
    if (in.ddeMode != out.ddeMode)
    {
        cout << "in.ddeMode" << endl;
        result = false;
    }
    if (in.ddeLevel != out.ddeLevel)
    {
        cout << "in.ddeLevel" << endl;
        result = false;
    }
    if (in.roiX0 != out.roiX0)
    {
        cout << "in.roiX0" << endl;
        result = false;
    }
    if (in.roiY0 != out.roiY0)
    {
        cout << "in.roiY0" << endl;
        result = false;
    }
    if (in.roiX1 != out.roiX1)
    {
        cout << "in.roiX1" << endl;
        result = false;
    }
    if (in.roiY1 != out.roiY1)
    {
        cout << "in.roiY1" << endl;
        result = false;
    }
    if (in.temperature != out.temperature)
    {
        cout << "in.temperature" << endl;
        result = false;
    }
    if (in.alcGate != out.alcGate)
    {
        cout << "in.alcGate" << endl;
        result = false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        result = false;
    }
    if (in.changingMode != out.changingMode)
    {
        cout << "in.changingMode" << endl;
        result = false;
    }
    if (in.changingLevel != out.changingLevel)
    {
        cout << "in.changingLevel" << endl;
        result = false;
    }
    if (in.detail != out.detail)
    {
        cout << "in.detail" << endl;
        result = false;
    }
    if (in.profile != out.profile)
    {
        cout << "in.profile" << endl;
        result = false;
    }
    if (in.isConnected != out.isConnected)
    {
        cout << "in.isConnected" << endl;
        result = false;
    }
    if (in.isOpen != out.isOpen)
    {
        cout << "in.isOpen" << endl;
        result = false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        result = false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        result = false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        result = false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        result = false;
    }

    return result;
}



// Encode/decode commands test.
bool encodeDecodeCommandsTest()
{
    // Encode command.
    uint8_t data[1024];
    int size = 0;
    float outValue = (float)(rand() % 20);
    Camera::encodeCommand(data, size, CameraCommand::NUC);

    // Decode command.
    CameraCommand commandId;
    CameraParam paramId;
    float value = 0.0f;
    if (Camera::decodeCommand(data, size, paramId, commandId, value) != 0)
    {
        cout << "Command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (commandId != CameraCommand::NUC)
    {
        cout << "not a CameraCommand::NUC" << endl;
        return false;
    }

    // Encode param.
    outValue = (float)(rand() % 20);
    Camera::encodeSetParamCommand(data, size, CameraParam::ROI_X0, outValue);

    // Decode command.
    value = 0.0f;
    if (Camera::decodeCommand(data, size, paramId, commandId, value) != 1)
    {
        cout << "Set param command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (paramId != CameraParam::ROI_X0)
    {
        cout << "not a CameraParam::ROI_X0" << endl;
        return false;
    }
    if (value != outValue)
    {
        cout << "not equal value" << endl;
        return false;
    }

    return true;
}



/// JSON read/write test.
bool jsonReadWriteTest()
{
    // Prepare random params.
    CameraParams in;
    in.initString = "dfhglsjirhuhjfb";
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.displayMode = rand() % 255;
    in.videoOutput = rand() % 255;
    in.logMode = rand() % 255;
    in.exposureMode = rand() % 255;
    in.exposureTime = rand() % 255;
    in.whiteBalanceMode = rand() % 255;
    in.whiteBalanceArea = rand() % 255;
    in.wideDynamicRangeMode = rand() % 255;
    in.stabilisationMode = rand() % 255;
    in.isoSensetivity = rand() % 255;
    in.sceneMode = rand() % 255;
    in.fps = rand() % 255;
    in.brightnessMode = rand() % 255;
    in.brightness = rand() % 255;
    in.contrast = rand() % 255;
    in.gainMode = rand() % 255;
    in.gain = rand() % 255;
    in.sharpeningMode = rand() % 255;
    in.sharpening = rand() % 255;
    in.palette = rand() % 255;
    in.agcMode = rand() % 255;
    in.shutterMode = rand() % 255;
    in.shutterPos = rand() % 255;
    in.shutterSpeed = rand() % 255;
    in.digitalZoomMode = rand() % 255;
    in.digitalZoom = rand() % 255;
    in.exposureCompensationMode = rand() % 255;
    in.exposureCompensationPosition = rand() % 255;
    in.defogMode = rand() % 255;
    in.dehazeMode = rand() % 255;
    in.noiseReductionMode = rand() % 255;
    in.blackAndWhiteFilterMode = rand() % 255;
    in.filterMode = rand() % 255;
    in.nucMode = rand() % 255;
    in.autoNucIntervalMsec = rand() % 255;
    in.imageFlip = rand() % 255;
    in.ddeMode = rand() % 255;
    in.ddeLevel = rand() % 255;
    in.roiX0 = rand() % 255;
    in.roiY0 = rand() % 255;
    in.roiX1 = rand() % 255;
    in.roiY1 = rand() % 255;
    in.temperature = rand() % 255;
    in.alcGate = rand() % 255;
    in.sensitivity = rand() % 255;
    in.changingMode = rand() % 255;
    in.changingLevel = rand() % 255;
    in.chromeLevel = rand() % 255;
    in.detail = rand() % 255;
    in.profile = rand() % 255;
    in.isConnected = true;
    in.isOpen = true;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Write params to file.
    cr::utils::ConfigReader inConfig;
    inConfig.set(in, "cameraParams");
    inConfig.writeToFile("TestCameraParams.json");

    // Read params from file.
    cr::utils::ConfigReader outConfig;
    if(!outConfig.readFromFile("TestCameraParams.json"))
    {
        cout << "Can't open config file" << endl;
        return false;
    }

    CameraParams out;
    if(!outConfig.get(out, "cameraParams"))
    {
        cout << "Can't read params from file" << endl;
        return false;
    }

    // Compare params.
    bool result = true;
    if (in.initString != out.initString)
    {
        cout << "in.initString" << endl;
        result = false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        result = false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        result = false;
    }
    if (in.displayMode != out.displayMode)
    {
        cout << "in.displayMode" << endl;
        result = false;
    }
    if (in.videoOutput != out.videoOutput)
    {
        cout << "in.videoOutput" << endl;
        result = false;
    }
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        result = false;
    }
    if (in.exposureMode != out.exposureMode)
    {
        cout << "in.exposureMode" << endl;
        result = false;
    }
    if (in.exposureTime != out.exposureTime)
    {
        cout << "in.exposureTime" << endl;
        result = false;
    }
    if (in.whiteBalanceMode != out.whiteBalanceMode)
    {
        cout << "in.whiteBalanceMode" << endl;
        result = false;
    }
    if (in.whiteBalanceArea != out.whiteBalanceArea)
    {
        cout << "in.whiteBalanceArea" << endl;
        result = false;
    }
    if (in.wideDynamicRangeMode != out.wideDynamicRangeMode)
    {
        cout << "in.wideDynamicRangeMode" << endl;
        result = false;
    }
    if (in.stabilisationMode != out.stabilisationMode)
    {
        cout << "in.stabilisationMode" << endl;
        result = false;
    }
    if (in.isoSensetivity != out.isoSensetivity)
    {
        cout << "in.isoSensetivity" << endl;
        result = false;
    }
    if (in.sceneMode != out.sceneMode)
    {
        cout << "in.sceneMode" << endl;
        result = false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        result = false;
    }
    if (in.brightnessMode != out.brightnessMode)
    {
        cout << "in.brightnessMode" << endl;
        result = false;
    }
    if (in.brightness != out.brightness)
    {
        cout << "in.brightness" << endl;
        result = false;
    }
    if (in.contrast != out.contrast)
    {
        cout << "in.contrast" << endl;
        result = false;
    }
    if (in.gainMode != out.gainMode)
    {
        cout << "in.gainMode" << endl;
        result = false;
    }
    if (in.gain != out.gain)
    {
        cout << "in.gain" << endl;
        result = false;
    }
    if (in.sharpeningMode != out.sharpeningMode)
    {
        cout << "in.sharpeningMode" << endl;
        result = false;
    }
    if (in.sharpening != out.sharpening)
    {
        cout << "in.sharpening" << endl;
        result = false;
    }
    if (in.palette != out.palette)
    {
        cout << "in.palette" << endl;
        result = false;
    }
    if (in.agcMode != out.agcMode)
    {
        cout << "in.agcMode" << endl;
        result = false;
    }
    if (in.shutterMode != out.shutterMode)
    {
        cout << "in.shutterMode" << endl;
        result = false;
    }
    if (in.shutterPos != out.shutterPos)
    {
        cout << "in.shutterPos" << endl;
        result = false;
    }
    if (in.shutterSpeed != out.shutterSpeed)
    {
        cout << "in.shutterSpeed" << endl;
        result = false;
    }
    if (in.digitalZoomMode != out.digitalZoomMode)
    {
        cout << "in.digitalZoomMode" << endl;
        result = false;
    }
    if (in.digitalZoom != out.digitalZoom)
    {
        cout << "in.digitalZoom" << endl;
        result = false;
    }
    if (in.exposureCompensationMode != out.exposureCompensationMode)
    {
        cout << "in.exposureCompensationMode" << endl;
        result = false;
    }
    if (in.exposureCompensationPosition != out.exposureCompensationPosition)
    {
        cout << "in.exposureCompensationPosition" << endl;
        result = false;
    }
    if (in.defogMode != out.defogMode)
    {
        cout << "in.defogMode" << endl;
        result = false;
    }
    if (in.dehazeMode != out.dehazeMode)
    {
        cout << "in.dehazeMode" << endl;
        result = false;
    }
    if (in.noiseReductionMode != out.noiseReductionMode)
    {
        cout << "in.noiseReductionMode" << endl;
        result = false;
    }
    if (in.blackAndWhiteFilterMode != out.blackAndWhiteFilterMode)
    {
        cout << "in.blackAndWhiteFilterMode" << endl;
        result = false;
    }
    if (in.filterMode != out.filterMode)
    {
        cout << "in.filterMode" << endl;
        result = false;
    }
    if (in.nucMode != out.nucMode)
    {
        cout << "in.nucMode" << endl;
        result = false;
    }
    if (in.autoNucIntervalMsec != out.autoNucIntervalMsec)
    {
        cout << "in.autoNucInterval" << endl;
        result = false;
    }
    if (in.imageFlip != out.imageFlip)
    {
        cout << "in.imageFlip" << endl;
        result = false;
    }
    if (in.ddeMode != out.ddeMode)
    {
        cout << "in.ddeMode" << endl;
        result = false;
    }
    if (in.ddeLevel != out.ddeLevel)
    {
        cout << "in.ddeLevel" << endl;
        result = false;
    }
    if (in.roiX0 != out.roiX0)
    {
        cout << "in.roiX0" << endl;
        result = false;
    }
    if (in.roiY0 != out.roiY0)
    {
        cout << "in.roiY0" << endl;
        result = false;
    }
    if (in.roiX1 != out.roiX1)
    {
        cout << "in.roiX1" << endl;
        result = false;
    }
    if (in.roiY1 != out.roiY1)
    {
        cout << "in.roiY1" << endl;
        result = false;
    }
    if (in.alcGate != out.alcGate)
    {
        cout << "in.alcGate" << endl;
        result = false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        result = false;
    }
    if (in.changingMode != out.changingMode)
    {
        cout << "in.changingMode" << endl;
        result = false;
    }
    if (in.changingLevel != out.changingLevel)
    {
        cout << "in.changingLevel" << endl;
        result = false;
    }
    if (in.detail != out.detail)
    {
        cout << "in.detail" << endl;
        result = false;
    }
    if (in.profile != out.profile)
    {
        cout << "in.profile" << endl;
        result = false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        result = false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        result = false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        result = false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        result = false;
    }

    return result;
}















