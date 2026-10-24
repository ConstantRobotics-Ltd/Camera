#include "CustomCamera.h"
#include "Camera.h"
#include "CustomCameraVersion.h"
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <mutex>
#include <string>
#include <utility>



namespace
{
using rapidpixel::CameraParam;
using rapidpixel::CameraParams;

/// Maximum size of the init string, bytes. The init string is stored in the
/// params only, so the limit protects the memory of the example.
constexpr size_t MAX_INIT_STRING_SIZE{256};
/// Limit of float values which can be converted to int. 2^31 is exactly
/// representable as float, so (-LIMIT <= value < LIMIT) is the exact range
/// of int.
constexpr float INT_RANGE_LIMIT{2147483648.0f};
/// Maximum video frame width and height, pixels.
constexpr int MAX_FRAME_SIZE{16384};
/// Maximum value of the params in percents.
constexpr int MAX_PERCENT{100};
/// Maximum shutter position (full open).
constexpr int MAX_SHUTTER_POSITION{65535};
/// Maximum auto NUC interval, milliseconds.
constexpr int MAX_AUTO_NUC_INTERVAL_MSEC{100000};
/// Minimum digital zoom (x1).
constexpr float MIN_DIGITAL_ZOOM{1.0f};
/// Maximum digital zoom (x20).
constexpr float MAX_DIGITAL_ZOOM{20.0f};
/// Number of int params which can be changed by setParam(...).
constexpr size_t INT_PARAMS_NUMBER{47};
/// Number of float params which can be changed by setParam(...).
constexpr size_t FLOAT_PARAMS_NUMBER{8};



/// Description of an int param: the field of CameraParams and the valid range
/// of the value.
struct IntParam
{
    /// Param ID.
    CameraParam id;
    /// Field of CameraParams which stores the param.
    int CameraParams::* field;
    /// Minimum value of the param.
    int minValue;
    /// Maximum value of the param.
    int maxValue;
};



/// Description of a float param: the field of CameraParams and the valid range
/// of the value.
struct FloatParam
{
    /// Param ID.
    CameraParam id;
    /// Field of CameraParams which stores the param.
    float CameraParams::* field;
    /// Minimum value of the param.
    float minValue;
    /// Maximum value of the param.
    float maxValue;
};



/// Get the description of an int param. The range is not limited by default.
constexpr IntParam makeIntParam(
        CameraParam id, int CameraParams::* field,
        int minValue = std::numeric_limits<int>::min(),
        int maxValue = std::numeric_limits<int>::max())
{
    return {id, field, minValue, maxValue};
}



/// Get the description of a float param. The range is not limited by default.
constexpr FloatParam makeFloatParam(
        CameraParam id, float CameraParams::* field,
        float minValue = std::numeric_limits<float>::lowest(),
        float maxValue = std::numeric_limits<float>::max())
{
    return {id, field, minValue, maxValue};
}



/// Int params. Temperature, isConnected and isOpen are read only: they are not
/// in the tables.
constexpr std::array INT_PARAMS{
    makeIntParam(CameraParam::WIDTH, &CameraParams::width, 0,
                 MAX_FRAME_SIZE),
    makeIntParam(CameraParam::HEIGHT, &CameraParams::height, 0,
                 MAX_FRAME_SIZE),
    makeIntParam(CameraParam::DISPLAY_MODE, &CameraParams::displayMode),
    makeIntParam(CameraParam::VIDEO_OUTPUT, &CameraParams::videoOutput),
    makeIntParam(CameraParam::LOG_MODE, &CameraParams::logMode),
    makeIntParam(CameraParam::EXPOSURE_MODE, &CameraParams::exposureMode),
    makeIntParam(CameraParam::EXPOSURE_TIME, &CameraParams::exposureTime),
    makeIntParam(CameraParam::WHITE_BALANCE_MODE,
                 &CameraParams::whiteBalanceMode),
    makeIntParam(CameraParam::WHITE_BALANCE_AREA,
                 &CameraParams::whiteBalanceArea),
    makeIntParam(CameraParam::WIDE_DYNAMIC_RANGE_MODE,
                 &CameraParams::wideDynamicRangeMode),
    makeIntParam(CameraParam::STABILIZATION_MODE,
                 &CameraParams::stabilizationMode),
    makeIntParam(CameraParam::ISO_SENSITIVITY, &CameraParams::isoSensitivity),
    makeIntParam(CameraParam::SCENE_MODE, &CameraParams::sceneMode),
    makeIntParam(CameraParam::BRIGHTNESS_MODE, &CameraParams::brightnessMode),
    makeIntParam(CameraParam::BRIGHTNESS, &CameraParams::brightness, 0,
                 MAX_PERCENT),
    makeIntParam(CameraParam::CONTRAST, &CameraParams::contrast, 0,
                 MAX_PERCENT),
    makeIntParam(CameraParam::GAIN_MODE, &CameraParams::gainMode),
    makeIntParam(CameraParam::GAIN, &CameraParams::gain, 0, MAX_PERCENT),
    makeIntParam(CameraParam::SHARPENING_MODE, &CameraParams::sharpeningMode),
    makeIntParam(CameraParam::SHARPENING, &CameraParams::sharpening, 0,
                 MAX_PERCENT),
    makeIntParam(CameraParam::PALETTE, &CameraParams::palette),
    makeIntParam(CameraParam::AGC_MODE, &CameraParams::agcMode),
    makeIntParam(CameraParam::SHUTTER_MODE, &CameraParams::shutterMode),
    makeIntParam(CameraParam::SHUTTER_POSITION, &CameraParams::shutterPos, 0,
                 MAX_SHUTTER_POSITION),
    makeIntParam(CameraParam::SHUTTER_SPEED, &CameraParams::shutterSpeed, 0,
                 MAX_PERCENT),
    makeIntParam(CameraParam::DIGITAL_ZOOM_MODE,
                 &CameraParams::digitalZoomMode),
    makeIntParam(CameraParam::EXPOSURE_COMPENSATION_MODE,
                 &CameraParams::exposureCompensationMode),
    makeIntParam(CameraParam::EXPOSURE_COMPENSATION_POSITION,
                 &CameraParams::exposureCompensationPosition),
    makeIntParam(CameraParam::DEFOG_MODE, &CameraParams::defogMode),
    makeIntParam(CameraParam::DEHAZE_MODE, &CameraParams::dehazeMode),
    makeIntParam(CameraParam::NOISE_REDUCTION_MODE,
                 &CameraParams::noiseReductionMode),
    makeIntParam(CameraParam::BLACK_WHITE_FILTER_MODE,
                 &CameraParams::blackAndWhiteFilterMode),
    makeIntParam(CameraParam::FILTER_MODE, &CameraParams::filterMode),
    makeIntParam(CameraParam::NUC_MODE, &CameraParams::nucMode),
    makeIntParam(CameraParam::AUTO_NUC_INTERVAL_MSEC,
                 &CameraParams::autoNucIntervalMsec, 0,
                 MAX_AUTO_NUC_INTERVAL_MSEC),
    makeIntParam(CameraParam::IMAGE_FLIP, &CameraParams::imageFlip),
    makeIntParam(CameraParam::DDE_MODE, &CameraParams::ddeMode),
    makeIntParam(CameraParam::ROI_X0, &CameraParams::roiX0),
    makeIntParam(CameraParam::ROI_Y0, &CameraParams::roiY0),
    makeIntParam(CameraParam::ROI_X1, &CameraParams::roiX1),
    makeIntParam(CameraParam::ROI_Y1, &CameraParams::roiY1),
    makeIntParam(CameraParam::ALC_GATE, &CameraParams::alcGate),
    makeIntParam(CameraParam::CHANGING_MODE, &CameraParams::changingMode),
    makeIntParam(CameraParam::CHROMA_LEVEL, &CameraParams::chromaLevel, 0,
                 MAX_PERCENT),
    makeIntParam(CameraParam::DETAIL, &CameraParams::detail, 0, MAX_PERCENT),
    makeIntParam(CameraParam::PROFILE, &CameraParams::profile),
    makeIntParam(CameraParam::TYPE, &CameraParams::type)};
static_assert(INT_PARAMS.size() == INT_PARAMS_NUMBER,
              "wrong number of int params");



/// Float params.
constexpr std::array FLOAT_PARAMS{
    makeFloatParam(CameraParam::FPS, &CameraParams::fps),
    makeFloatParam(CameraParam::DIGITAL_ZOOM, &CameraParams::digitalZoom,
                   MIN_DIGITAL_ZOOM, MAX_DIGITAL_ZOOM),
    makeFloatParam(CameraParam::DDE_LEVEL, &CameraParams::ddeLevel),
    makeFloatParam(CameraParam::SENSITIVITY, &CameraParams::sensitivity),
    makeFloatParam(CameraParam::CHANGING_LEVEL, &CameraParams::changingLevel),
    makeFloatParam(CameraParam::CUSTOM_1, &CameraParams::custom1),
    makeFloatParam(CameraParam::CUSTOM_2, &CameraParams::custom2),
    makeFloatParam(CameraParam::CUSTOM_3, &CameraParams::custom3)};
static_assert(FLOAT_PARAMS.size() == FLOAT_PARAMS_NUMBER,
              "wrong number of float params");



/// Find the description of an int param. Returns nullptr if the param is not
/// an int param which can be changed.
const IntParam* findIntParam(CameraParam id)
{
    for (const IntParam& param : INT_PARAMS)
    {
        if (param.id == id)
        {
            return &param;
        }
    }

    return nullptr;
}



/// Find the description of a float param. Returns nullptr if the param is not
/// a float param which can be changed.
const FloatParam* findFloatParam(CameraParam id)
{
    for (const FloatParam& param : FLOAT_PARAMS)
    {
        if (param.id == id)
        {
            return &param;
        }
    }

    return nullptr;
}



/// Convert float param value to int. A conversion of NaN or of a value outside
/// of the int range is undefined behavior, so such values are rejected.
bool toInt(float value, int& result)
{
    // The comparison is false for NaN, so NaN is rejected.
    if (!(value >= -INT_RANGE_LIMIT && value < INT_RANGE_LIMIT))
    {
        return false;
    }
    result = static_cast<int>(value);

    return true;
}



/// Check that all params of the object are inside their ranges.
bool areParamsValid(const CameraParams& params)
{
    if (params.initString.size() > MAX_INIT_STRING_SIZE)
    {
        return false;
    }
    for (const IntParam& param : INT_PARAMS)
    {
        const int value = params.*(param.field);
        if (value < param.minValue || value > param.maxValue)
        {
            return false;
        }
    }
    for (const FloatParam& param : FLOAT_PARAMS)
    {
        const float value = params.*(param.field);
        // The comparison is false for NaN, so NaN is rejected.
        if (!(value >= param.minValue && value <= param.maxValue))
        {
            return false;
        }
    }

    return true;
}
}



rapidpixel::CustomCamera::CustomCamera()
{
    // Reset connection flags.
    m_params.isOpen = false;
    m_params.isConnected = false;
}



rapidpixel::CustomCamera::~CustomCamera() = default;



std::string rapidpixel::CustomCamera::getVersion()
{
    return CUSTOM_CAMERA_VERSION;
}



bool rapidpixel::CustomCamera::openCamera(std::string initString)
{
    // Check the size of the init string.
    if (initString.size() > MAX_INIT_STRING_SIZE)
    {
        return false;
    }

    // Set default params and connection flags.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    m_params = CameraParams();
    m_params.initString = std::move(initString);
    m_params.isOpen = true;
    m_params.isConnected = true;

    return true;
}



bool rapidpixel::CustomCamera::initCamera(CameraParams& params)
{
    // Check the params.
    if (!areParamsValid(params))
    {
        return false;
    }

    // Copy params and set connection flags.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    m_params = params;
    m_params.isOpen = true;
    m_params.isConnected = true;

    return true;
}



void rapidpixel::CustomCamera::closeCamera()
{
    // Reset connection flags.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    m_params.isOpen = false;
    m_params.isConnected = false;
}



bool rapidpixel::CustomCamera::isCameraOpen()
{
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    return m_params.isOpen;
}



bool rapidpixel::CustomCamera::isCameraConnected()
{
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    return m_params.isConnected;
}



bool rapidpixel::CustomCamera::setParam(CameraParam id, float value)
{
    // Int params: the value must be convertible to int and inside the range.
    if (const IntParam* param = findIntParam(id); param != nullptr)
    {
        int intValue = 0;
        if (!toInt(value, intValue) ||
            intValue < param->minValue || intValue > param->maxValue)
        {
            return false;
        }
        const std::lock_guard<std::mutex> lock(m_paramsMutex);
        m_params.*(param->field) = intValue;
        return true;
    }

    // Float params: the value must be inside the range (NaN is rejected).
    if (const FloatParam* param = findFloatParam(id); param != nullptr)
    {
        if (!(value >= param->minValue && value <= param->maxValue))
        {
            return false;
        }
        const std::lock_guard<std::mutex> lock(m_paramsMutex);
        m_params.*(param->field) = value;
        return true;
    }

    // Read only params (temperature, connection and open status) and unknown
    // IDs.
    return false;
}



float rapidpixel::CustomCamera::getParam(CameraParam id)
{
    const std::lock_guard<std::mutex> lock(m_paramsMutex);

    if (const IntParam* param = findIntParam(id); param != nullptr)
    {
        return static_cast<float>(m_params.*(param->field));
    }
    if (const FloatParam* param = findFloatParam(id); param != nullptr)
    {
        return m_params.*(param->field);
    }

    // Read only params and unknown IDs.
    switch (id)
    {
    case CameraParam::TEMPERATURE:
    {
        return m_params.temperature;
    }
    case CameraParam::IS_CONNECTED:
    {
        return m_params.isConnected ? 1.0f : 0.0f;
    }
    case CameraParam::IS_OPEN:
    {
        return m_params.isOpen ? 1.0f : 0.0f;
    }
    default:
    {
        return -1.0f;
    }
    }
}



void rapidpixel::CustomCamera::getParams(CameraParams& params)
{
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    params = m_params;
}



bool rapidpixel::CustomCamera::executeCommand(CameraCommand id)
{
    // The example accepts every command of the interface and does nothing.
    switch (id)
    {
    case CameraCommand::RESTART:
    case CameraCommand::NUC:
    case CameraCommand::APPLY_PARAMS:
    case CameraCommand::SAVE_PARAMS:
    case CameraCommand::MENU_ON:
    case CameraCommand::MENU_OFF:
    case CameraCommand::MENU_SET:
    case CameraCommand::MENU_UP:
    case CameraCommand::MENU_DOWN:
    case CameraCommand::MENU_LEFT:
    case CameraCommand::MENU_RIGHT:
    case CameraCommand::FREEZE:
    case CameraCommand::DEFREEZE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}



bool rapidpixel::CustomCamera::decodeAndExecuteCommand(
        uint8_t* data, int size)
{
    // Decode command. The decoder checks the size, the version and the IDs.
    CameraCommand commandId = CameraCommand::NUC;
    CameraParam paramId = CameraParam::NUC_MODE;
    float value = 0.0f;
    const int result =
            Camera::decodeCommand(data, size, paramId, commandId, value);

    // Execute the decoded command.
    if (result == 0)
    {
        return executeCommand(commandId);
    }
    if (result == 1)
    {
        return setParam(paramId, value);
    }

    return false;
}
