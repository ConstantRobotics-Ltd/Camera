#include "CustomCamera.h"
#include "CustomCameraVersion.h"



cr::camera::CustomCamera::CustomCamera()
{
    // Reset connection flags.
    m_params.isOpen = false;
    m_params.isConnected = false;
}



cr::camera::CustomCamera::~CustomCamera()
{

}



std::string cr::camera::CustomCamera::getVersion()
{
    return CUSTOM_CAMERA_VERSION;
}



bool cr::camera::CustomCamera::openCamera(std::string initString)
{
    // Set connection flags.
    m_params.isOpen = true;
    m_params.isConnected = true;

    return true;
}



bool cr::camera::CustomCamera::initCamera(CameraParams& params)
{
    // Copy params.
    m_params = params;

    // Set connection flags.
    m_params.isOpen = true;
    m_params.isConnected = true;

    return true;
}



void cr::camera::CustomCamera::closeCamera()
{
    // Reset connection flags.
    m_params.isOpen = false;
    m_params.isConnected = false;
}



bool cr::camera::CustomCamera::isCameraOpen()
{
    return m_params.isOpen;
}




bool cr::camera::CustomCamera::isCameraConnected()
{
    return m_params.isConnected;
}



bool cr::camera::CustomCamera::setParam(CameraParam id, float value)
{
    // Check param ID.
    switch (id)
    {
    case CameraParam::WIDTH:
    {
        // Save value.
        m_params.width = (int)value;
        return true;
    }
    case CameraParam::HEIGHT:
    {
        // Save value.
        m_params.height = (int)value;
        return true;
    }
    case CameraParam::DISPLAY_MODE:
    {
        // Save value.
        m_params.displayMode = (int)value;
        return true;
    }
    case CameraParam::VIDEO_OUTPUT:
    {
        // Save value.
        m_params.videoOutput = (int)value;
        return true;
    }
    case CameraParam::LOG_MODE:
    {
        // Save value.
        m_params.logMode = (int)value;
        return true;
    }
    case CameraParam::EXPOSURE_MODE:
    {
        // Save value.
        m_params.exposureMode = (int)value;
        return true;
    }
    case CameraParam::EXPOSURE_TIME:
    {
        // Save value.
        m_params.exposureTime = (int)value;
        return true;
    }
    case CameraParam::WHITE_BALANCE_MODE:
    {
        // Save value.
        m_params.whiteBalanceMode = (int)value;
        return true;
    }
    case CameraParam::WHITE_BALANCE_AREA:
    {
        // Save value.
        m_params.whiteBalanceArea = (int)value;
        return true;
    }
    case CameraParam::WIDE_DINAMIC_RANGE_MODE:
    {
        // Save value.
        m_params.wideDynamicRangeMode = (int)value;
        return true;
    }
    case CameraParam::STABILIZATION_MODE:
    {
        // Save value.
        m_params.stabilisationMode = (int)value;
        return true;
    }
    case CameraParam::ISO_SENSITIVITY:
    {
        // Save value.
        m_params.isoSensetivity = (int)value;
        return true;
    }
    case CameraParam::SCENE_MODE:
    {
        // Save value.
        m_params.sceneMode = (int)value;
        return true;
    }
    case CameraParam::FPS:
    {
        // Save value.
        m_params.fps = value;
        return true;
    }
    case CameraParam::BRIGHTNESS_MODE:
    {
        // Save value.
        m_params.brightnessMode = (int)value;
        return true;
    }
    case CameraParam::BRIGHTNESS:
    {
        // Save value.
        m_params.brightness = (int)value;
        return true;
    }
    case CameraParam::CONTRAST:
    {
        // Save value.
        m_params.contrast = (int)value;
        return true;
    }
    case CameraParam::GAIN_MODE:
    {
        // Save value.
        m_params.gainMode = (int)value;
        return true;
    }
    case CameraParam::GAIN:
    {
        // Save value.
        m_params.gain = (int)value;
        return true;
    }
    case CameraParam::SHARPENING_MODE:
    {
        // Save value.
        m_params.sharpeningMode = (int)value;
        return true;
    }
    case CameraParam::SHARPENING:
    {
        // Save value.
        m_params.sharpening = (int)value;
        return true;
    }
    case CameraParam::PALETTE:
    {
        // Save value.
        m_params.palette = (int)value;
        return true;
    }
    case CameraParam::AGC_MODE:
    {
        // Save value.
        m_params.agcMode = (int)value;
        return true;
    }
    case CameraParam::SHUTTER_MODE:
    {
        // Save value.
        m_params.shutterMode = (int)value;
        return true;
    }
    case CameraParam::SHUTTER_POSITION:
    {
        // Save value.
        m_params.shutterPos = (int)value;
        return true;
    }
    case CameraParam::SHUTTER_SPEED:
    {
        // Save value.
        m_params.shutterSpeed = (int)value;
        return true;
    }
    case CameraParam::DIGITAL_ZOOM_MODE:
    {
        // Save value.
        m_params.digitalZoomMode = (int)value;
        return true;
    }
    case CameraParam::DIGITAL_ZOOM:
    {
        // Save value.
        m_params.digitalZoom = value;
        return true;
    }
    case CameraParam::EXPOSURE_COMPENSATION_MODE:
    {
        // Save value.
        m_params.exposureCompensationMode = (int)value;
        return true;
    }
    case CameraParam::EXPOSURE_COMPENSATION_POSITION:
    {
        // Save value.
        m_params.exposureCompensationPosition = (int)value;
        return true;
    }
    case CameraParam::DEFOG_MODE:
    {
        // Save value.
        m_params.defogMode = (int)value;
        return true;
    }
    case CameraParam::DEHAZE_MODE:
    {
        // Save value.
        m_params.dehazeMode = (int)value;
        return true;
    }
    case CameraParam::NOISE_REDUCTION_MODE:
    {
        // Save value.
        m_params.noiseReductionMode = (int)value;
        return true;
    }
    case CameraParam::BLACK_WHITE_FILTER_MODE:
    {
        // Save value.
        m_params.blackAndWhiteFilterMode = (int)value;
        return true;
    }
    case CameraParam::FILTER_MODE:
    {
        // Save value.
        m_params.filterMode = (int)value;
        return true;
    }
    case CameraParam::NUC_MODE:
    {
        // Save value.
        m_params.nucMode = (int)value;
        return true;
    }
    case CameraParam::AUTO_NUC_INTERVAL_MSEC:
    {
        // Save value.
        m_params.autoNucIntervalMsec = (int)value;
        return true;
    }
    case CameraParam::IMAGE_FLIP:
    {
        // Save value.
        m_params.imageFlip = (int)value;
        return true;
    }
    case CameraParam::DDE_MODE:
    {
        // Save value.
        m_params.ddeMode = (int)value;
        return true;
    }
    case CameraParam::DDE_LEVEL:
    {
        // Save value.
        m_params.ddeLevel = value;
        return true;
    }
    case CameraParam::ROI_X0:
    {
        // Save value.
        m_params.roiX0 = (int)value;
        return true;
    }
    case CameraParam::ROI_Y0:
    {
        // Save value.
        m_params.roiY0 = (int)value;
        return true;
    }
    case CameraParam::ROI_X1:
    {
        // Save value.
        m_params.roiX1 = (int)value;
        return true;
    }
    case CameraParam::ROI_Y1:
    {
        // Save value.
        m_params.roiY1 = (int)value;
        return true;
    }
    case CameraParam::TEMPERATURE:
    {
        // Read only.
        return false;
    }
    case CameraParam::ALC_GATE:
    {
        // Save value.
        m_params.alcGate = (int)value;
        return true;
    }
    case CameraParam::SENSITIVITY:
    {
        // Save value.
        m_params.sensitivity = value;
        return true;
    }
    case CameraParam::CHANGING_MODE:
    {
        // Save value.
        m_params.changingMode = (int)value;
        return true;
    }
    case CameraParam::CHANGING_LEVEL:
    {
        // Save value.
        m_params.changingLevel = value;
        return true;
    }
    case CameraParam::CHROMA_LEVEL:
    {
        // Save value.
        m_params.chromaLevel = (int)value;
        return true;
    }
    case CameraParam::DETAIL:
    {
        // Save value.
        m_params.detail = (int)value;
        return true;
    }
    case CameraParam::PROFILE:
    {
        // Save value.
        m_params.profile = (int)value;
        return true;
    }
    case CameraParam::IS_CONNECTED:
    {
        // Read only.
        return false;
    }
    case CameraParam::IS_OPEN:
    {
        // Read only.
        return false;
    }
    case CameraParam::TYPE:
    {
        // Save value.
        m_params.type = (int)value;
        return true;
    }
    case CameraParam::CUSTOM_1:
    {
        // Save value.
        m_params.custom1 = value;
        return true;
    }
    case CameraParam::CUSTOM_2:
    {
        // Save value.
        m_params.custom2 = value;
        return true;
    }
    case CameraParam::CUSTOM_3:
    {
        // Save value.
        m_params.custom3 = value;
        return true;
    }
    default:
    {
        return false;
    }
    }

    return false;
}



float cr::camera::CustomCamera::getParam(CameraParam id)
{
    // Check param ID.
    switch (id)
    {
    case CameraParam::WIDTH:
    {
        return (float)m_params.width;
    }
    case CameraParam::HEIGHT:
    {
        return (float)m_params.height;
    }
    case CameraParam::DISPLAY_MODE:
    {
        return (float)m_params.displayMode;
    }
    case CameraParam::VIDEO_OUTPUT:
    {
        return (float)m_params.videoOutput;
    }
    case CameraParam::LOG_MODE:
    {
        return (float)m_params.logMode;
    }
    case CameraParam::EXPOSURE_MODE:
    {
        return (float)m_params.exposureMode;
    }
    case CameraParam::EXPOSURE_TIME:
    {
        return (float)m_params.exposureTime;
    }
    case CameraParam::WHITE_BALANCE_MODE:
    {
        return (float)m_params.whiteBalanceMode;
    }
    case CameraParam::WHITE_BALANCE_AREA:
    {
        return (float)m_params.whiteBalanceArea;
    }
    case CameraParam::WIDE_DINAMIC_RANGE_MODE:
    {
        return (float)m_params.wideDynamicRangeMode;
    }
    case CameraParam::STABILIZATION_MODE:
    {
        return (float)m_params.stabilisationMode;
    }
    case CameraParam::ISO_SENSITIVITY:
    {
        return (float)m_params.isoSensetivity;
    }
    case CameraParam::SCENE_MODE:
    {
        return (float)m_params.sceneMode;
    }
    case CameraParam::FPS:
    {
        return m_params.fps;
    }
    case CameraParam::BRIGHTNESS_MODE:
    {
        return (float)m_params.brightnessMode;
    }
    case CameraParam::BRIGHTNESS:
    {
        return (float)m_params.brightness;
    }
    case CameraParam::CONTRAST:
    {
        return (float)m_params.contrast;
    }
    case CameraParam::GAIN_MODE:
    {
        return (float)m_params.gainMode;
    }
    case CameraParam::GAIN:
    {
        return (float)m_params.gain;
    }
    case CameraParam::SHARPENING_MODE:
    {
        return (float)m_params.sharpeningMode;
    }
    case CameraParam::SHARPENING:
    {
        return (float)m_params.sharpening;
    }
    case CameraParam::PALETTE:
    {
        return (float)m_params.palette;
    }
    case CameraParam::AGC_MODE:
    {
        return (float)m_params.agcMode;
    }
    case CameraParam::SHUTTER_MODE:
    {
        return (float)m_params.shutterMode;
    }
    case CameraParam::SHUTTER_POSITION:
    {
        return (float)m_params.shutterPos;
    }
    case CameraParam::SHUTTER_SPEED:
    {
        return (float)m_params.shutterSpeed;
    }
    case CameraParam::DIGITAL_ZOOM_MODE:
    {
        return (float)m_params.digitalZoomMode;
    }
    case CameraParam::DIGITAL_ZOOM:
    {
        return m_params.digitalZoom;
    }
    case CameraParam::EXPOSURE_COMPENSATION_MODE:
    {
        return (float)m_params.exposureCompensationMode;
    }
    case CameraParam::EXPOSURE_COMPENSATION_POSITION:
    {
        return (float)m_params.exposureCompensationPosition;
    }
    case CameraParam::DEFOG_MODE:
    {
        return (float)m_params.defogMode;
    }
    case CameraParam::DEHAZE_MODE:
    {
        return (float)m_params.dehazeMode;
    }
    case CameraParam::NOISE_REDUCTION_MODE:
    {
        return (float)m_params.noiseReductionMode;
    }
    case CameraParam::BLACK_WHITE_FILTER_MODE:
    {
        return (float)m_params.blackAndWhiteFilterMode;
    }
    case CameraParam::FILTER_MODE:
    {
        return (float)m_params.filterMode;
    }
    case CameraParam::NUC_MODE:
    {
        return (float)m_params.nucMode;
    }
    case CameraParam::AUTO_NUC_INTERVAL_MSEC:
    {
        return (float)m_params.autoNucIntervalMsec;
    }
    case CameraParam::IMAGE_FLIP:
    {
        return (float)m_params.imageFlip;
    }
    case CameraParam::DDE_MODE:
    {
        return (float)m_params.ddeMode;
    }
    case CameraParam::DDE_LEVEL:
    {
        return m_params.ddeLevel;
    }
    case CameraParam::ROI_X0:
    {
        return (float)m_params.roiX0;
    }
    case CameraParam::ROI_Y0:
    {
        return (float)m_params.roiY0;
    }
    case CameraParam::ROI_X1:
    {
        return (float)m_params.roiX1;
    }
    case CameraParam::ROI_Y1:
    {
        return (float)m_params.roiY1;
    }
    case CameraParam::TEMPERATURE:
    {
        return m_params.temperature;
    }
    case CameraParam::ALC_GATE:
    {
        return (float)m_params.alcGate;
    }
    case CameraParam::SENSITIVITY:
    {
        return (float)m_params.sensitivity;
    }
    case CameraParam::CHANGING_MODE:
    {
        return (float)m_params.changingMode;
    }
    case CameraParam::CHANGING_LEVEL:
    {
        return m_params.changingLevel;
    }
    case CameraParam::CHROMA_LEVEL:
    {
        return (float)m_params.chromaLevel;
    }
    case CameraParam::DETAIL:
    {
        return (float)m_params.detail;
    }
    case CameraParam::PROFILE:
    {
        return (float)m_params.profile;
    }
    case CameraParam::IS_CONNECTED:
    {
        return m_params.isConnected ? 1.0f : 0.0f;
    }
    case CameraParam::IS_OPEN:
    {
        return m_params.isOpen ? 1.0f : 0.0f;
    }
    case CameraParam::TYPE:
    {
        return (float)m_params.type;
    }
    case CameraParam::CUSTOM_1:
    {
        return m_params.custom1;
    }
    case CameraParam::CUSTOM_2:
    {
        return m_params.custom2;
    }
    case CameraParam::CUSTOM_3:
    {
        return m_params.custom3;
    }
    default:
    {
        return -1.0f;
    }
    }

    return -1.0f;
}



cr::camera::CameraParams cr::camera::CustomCamera::getParams()
{
    return m_params;
}



bool cr::camera::CustomCamera::executeCommand(CameraCommand id)
{
    // Check command.
    switch (id)
    {
    case CameraCommand::RESTART:
    {
        return true;
    }
    case CameraCommand::NUC:
    {
        return true;
    }
    case CameraCommand::APPLY_PARAMS:
    {
        return true;
    }
    case CameraCommand::SAVE_PARAMS:
    {
        return true;
    }
    case CameraCommand::MENU_ON:
    {
        return true;
    }
    case CameraCommand::MENU_OFF:
    {
        return true;
    }
    case CameraCommand::MENU_SET:
    {
        return true;
    }
    case CameraCommand::MENU_UP:
    {
        return true;
    }
    case CameraCommand::MENU_DOWN:
    {
        return true;
    }
    case CameraCommand::MENU_LEFT:
    {
        return true;
    }
    case CameraCommand::MENU_RIGHT:
    {
        return true;
    }
    case CameraCommand::FREEZE:
    {
        return true;
    }
    case CameraCommand::DEFREEZE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }

    return false;
}



bool cr::camera::CustomCamera::decodeAndExecuteCommand(uint8_t* data, int size)
{
    // Decode command.
    CameraCommand commandId = CameraCommand::NUC;
    CameraParam paramId = CameraParam::NUC_MODE;
    float value = 0.0f;
    switch (Camera::decodeCommand(data, size, paramId, commandId, value))
    {
    // COMMAND.
    case 0:
        // Executte command.
        return executeCommand(commandId);
    // SET_PARAM.
    case 1:
    {
        // Set param.
        return setParam(paramId, value);
    }
    default:
    {
        return false;
    }
    }

    return false;
}
