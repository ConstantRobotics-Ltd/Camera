#include "Camera.h"
#include "CameraVersion.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <tuple>
#include <utility>



namespace
{
// Encoded data stores int and float fields as raw 4 bytes values.
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(float) == 4, "float must be 4 bytes");

/// Number of CameraParams fields which are serialized (initString is not).
constexpr size_t FIELDS_NUMBER{58};
/// Number of bool fields (isConnected and isOpen).
constexpr int FLAGS_NUMBER{2};
/// Size of an int or float field in the encoded data, bytes.
constexpr int VALUE_SIZE{4};
/// Size of a bool field in the encoded data, bytes.
constexpr int FLAG_SIZE{1};

/// Data type of encoded params (first byte of the encoded data).
constexpr uint8_t PARAMS_DATA_TYPE{0x02};
/// Data type of encoded action command.
constexpr uint8_t COMMAND_DATA_TYPE{0x00};
/// Data type of encoded set param command.
constexpr uint8_t SET_PARAM_DATA_TYPE{0x01};
/// Version of the library in the encoded data: major and minor numbers. Data
/// with another version is rejected.
constexpr uint8_t VERSION_MAJOR{CAMERA_MAJOR_VERSION};
constexpr uint8_t VERSION_MINOR{CAMERA_MINOR_VERSION};
/// Position of the major version in the encoded data. The minor version
/// follows it.
constexpr int VERSION_POS{1};

/// Position of the mask in the encoded params: after data type and version.
constexpr int PARAMS_MASK_POS{3};
/// Size of the mask in the encoded params: one bit for each field.
constexpr int PARAMS_MASK_SIZE{(static_cast<int>(FIELDS_NUMBER) + 7) / 8};
/// Size of the encoded params header: data type, version and mask. It is the
/// minimum size of the encoded params (no field is selected).
constexpr int PARAMS_HEADER_SIZE{PARAMS_MASK_POS + PARAMS_MASK_SIZE};
/// Maximum size of the encoded params (all fields are selected). The buffer
/// of encode(...) must have at least this size.
constexpr int PARAMS_MAX_SIZE{
        PARAMS_HEADER_SIZE +
        (static_cast<int>(FIELDS_NUMBER) - FLAGS_NUMBER) * VALUE_SIZE +
        FLAGS_NUMBER * FLAG_SIZE};
static_assert(PARAMS_MASK_SIZE == 8, "wrong size of params mask");
static_assert(PARAMS_MAX_SIZE == 237, "wrong size of encoded params");

/// Position of the command or param ID in the encoded command.
constexpr int COMMAND_ID_POS{3};
/// Position of the param value in the encoded set param command.
constexpr int COMMAND_VALUE_POS{COMMAND_ID_POS + VALUE_SIZE};
/// Size of the encoded action command: data type, version and command ID.
constexpr int COMMAND_SIZE{COMMAND_VALUE_POS};
/// Size of the encoded set param command: data type, version, param ID and
/// param value.
constexpr int SET_PARAM_COMMAND_SIZE{COMMAND_VALUE_POS + VALUE_SIZE};

/// The first and the last command ID: the enum values are consecutive.
constexpr int FIRST_COMMAND_ID{
        static_cast<int>(cr::camera::CameraCommand::RESTART)};
constexpr int LAST_COMMAND_ID{
        static_cast<int>(cr::camera::CameraCommand::DEFREEZE)};
/// The first and the last param ID: the enum values are consecutive.
constexpr int FIRST_PARAM_ID{static_cast<int>(cr::camera::CameraParam::WIDTH)};
constexpr int LAST_PARAM_ID{
        static_cast<int>(cr::camera::CameraParam::CUSTOM_3)};
static_assert(LAST_PARAM_ID - FIRST_PARAM_ID + 1 ==
              static_cast<int>(FIELDS_NUMBER),
              "CameraParam enum doesn't match CameraParams");

/// Result of decodeCommand(...): error.
constexpr int DECODE_ERROR{-1};
/// Result of decodeCommand(...): action command decoded.
constexpr int DECODED_COMMAND{0};
/// Result of decodeCommand(...): set param command decoded.
constexpr int DECODED_SET_PARAM{1};



/// Location of a CameraParams field in the encoded data.
struct FieldRef
{
    /// Pointer to the field of a CameraParams object.
    void* value{nullptr};
    /// Size of the field in the encoded data: VALUE_SIZE or FLAG_SIZE.
    int size{0};
};



/// Get location of an int field.
FieldRef makeField(int& value)
{
    return {&value, VALUE_SIZE};
}



/// Get location of a float field.
FieldRef makeField(float& value)
{
    return {&value, VALUE_SIZE};
}



/// Get location of a bool field.
FieldRef makeField(bool& value)
{
    return {&value, FLAG_SIZE};
}



/// Get the table of CameraParams fields in the order they are stored in the
/// encoded data (the same order as the bits of the mask). The type of the
/// table is deduced from the number of the fields: it is checked below.
auto makeFieldTable(cr::camera::CameraParams& p)
{
    return std::array{
        makeField(p.width), makeField(p.height), makeField(p.displayMode),
        makeField(p.videoOutput), makeField(p.logMode),
        makeField(p.exposureMode), makeField(p.exposureTime),
        makeField(p.whiteBalanceMode), makeField(p.whiteBalanceArea),
        makeField(p.wideDynamicRangeMode), makeField(p.stabilizationMode),
        makeField(p.isoSensitivity), makeField(p.sceneMode), makeField(p.fps),
        makeField(p.brightnessMode), makeField(p.brightness),
        makeField(p.contrast), makeField(p.gainMode), makeField(p.gain),
        makeField(p.sharpeningMode), makeField(p.sharpening),
        makeField(p.palette), makeField(p.agcMode), makeField(p.shutterMode),
        makeField(p.shutterPos), makeField(p.shutterSpeed),
        makeField(p.digitalZoomMode), makeField(p.digitalZoom),
        makeField(p.exposureCompensationMode),
        makeField(p.exposureCompensationPosition), makeField(p.defogMode),
        makeField(p.dehazeMode), makeField(p.noiseReductionMode),
        makeField(p.blackAndWhiteFilterMode), makeField(p.filterMode),
        makeField(p.nucMode), makeField(p.autoNucIntervalMsec),
        makeField(p.imageFlip), makeField(p.ddeMode), makeField(p.ddeLevel),
        makeField(p.roiX0), makeField(p.roiY0), makeField(p.roiX1),
        makeField(p.roiY1), makeField(p.temperature), makeField(p.alcGate),
        makeField(p.sensitivity), makeField(p.changingMode),
        makeField(p.changingLevel), makeField(p.chromaLevel),
        makeField(p.detail), makeField(p.profile), makeField(p.isConnected),
        makeField(p.isOpen), makeField(p.type), makeField(p.custom1),
        makeField(p.custom2), makeField(p.custom3)};
}



/// Get the table of mask flags in the same order as the table of fields.
auto makeMaskTable(const cr::camera::CameraParamsMask& m)
{
    return std::array{
        m.width, m.height, m.displayMode, m.videoOutput, m.logMode,
        m.exposureMode, m.exposureTime, m.whiteBalanceMode,
        m.whiteBalanceArea, m.wideDynamicRangeMode, m.stabilizationMode,
        m.isoSensitivity, m.sceneMode, m.fps, m.brightnessMode, m.brightness,
        m.contrast, m.gainMode, m.gain, m.sharpeningMode, m.sharpening,
        m.palette, m.agcMode, m.shutterMode, m.shutterPos, m.shutterSpeed,
        m.digitalZoomMode, m.digitalZoom, m.exposureCompensationMode,
        m.exposureCompensationPosition, m.defogMode, m.dehazeMode,
        m.noiseReductionMode, m.blackAndWhiteFilterMode, m.filterMode,
        m.nucMode, m.autoNucIntervalMsec, m.imageFlip, m.ddeMode, m.ddeLevel,
        m.roiX0, m.roiY0, m.roiX1, m.roiY1, m.temperature, m.alcGate,
        m.sensitivity, m.changingMode, m.changingLevel, m.chromaLevel,
        m.detail, m.profile, m.isConnected, m.isOpen, m.type, m.custom1,
        m.custom2, m.custom3};
}

// Both tables must have one element for each field.
static_assert(std::tuple_size<decltype(makeFieldTable(
        std::declval<cr::camera::CameraParams&>()))>::value == FIELDS_NUMBER,
        "wrong number of fields in the table of fields");
static_assert(std::tuple_size<decltype(makeMaskTable(
        std::declval<const cr::camera::CameraParamsMask&>()))>::value ==
        FIELDS_NUMBER, "wrong number of flags in the table of mask flags");



/// Get the position of the mask byte which holds the bit of a field.
int maskBytePos(size_t fieldIndex)
{
    return PARAMS_MASK_POS + static_cast<int>(fieldIndex / 8);
}



/// Get the bit of a field inside the mask byte: the first field of a byte is
/// the most significant bit.
uint8_t maskBit(size_t fieldIndex)
{
    return static_cast<uint8_t>(0x80U >> (fieldIndex % 8));
}



/// Write the first bytes of the encoded data: data type and version.
void writeHeader(uint8_t* data, uint8_t dataType)
{
    data[0] = dataType;
    data[VERSION_POS] = VERSION_MAJOR;
    data[VERSION_POS + 1] = VERSION_MINOR;
}



/// Check the version of the encoded data.
bool isVersionValid(const uint8_t* data)
{
    return data[VERSION_POS] == VERSION_MAJOR &&
           data[VERSION_POS + 1] == VERSION_MINOR;
}
}



cr::camera::Camera::~Camera() = default;



std::string cr::camera::Camera::getVersion()
{
    return CAMERA_VERSION;
}



bool cr::camera::CameraParams::encode(
        uint8_t* data, int bufferSize, int& size, CameraParamsMask* mask)
{
    // Nothing is encoded until the arguments are checked.
    size = 0;

    // Check the pointer and the size of the buffer: all fields must fit.
    if (data == nullptr || bufferSize < PARAMS_MAX_SIZE)
    {
        return false;
    }

    // Default parameters mask: all fields are selected.
    const CameraParamsMask defaultMask;
    const CameraParamsMask& selected = (mask != nullptr) ? *mask : defaultMask;

    // Encode the header: data type, version and the mask.
    writeHeader(data, PARAMS_DATA_TYPE);
    std::memset(&data[PARAMS_MASK_POS], 0,
                static_cast<size_t>(PARAMS_MASK_SIZE));
    const auto flags = makeMaskTable(selected);
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        if (flags[i])
        {
            const int pos = maskBytePos(i);
            data[pos] = static_cast<uint8_t>(data[pos] | maskBit(i));
        }
    }

    // Encode the values of the selected fields.
    const auto fields = makeFieldTable(*this);
    int pos = PARAMS_HEADER_SIZE;
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        if (!flags[i])
        {
            continue;
        }
        if (fields[i].size == FLAG_SIZE)
        {
            data[pos] = *static_cast<const bool*>(fields[i].value) ?
                        uint8_t{0x01} : uint8_t{0x00};
        }
        else
        {
            std::memcpy(&data[pos], fields[i].value,
                        static_cast<size_t>(fields[i].size));
        }
        pos += fields[i].size;
    }

    size = pos;

    return true;
}



bool cr::camera::CameraParams::decode(uint8_t* data, int dataSize)
{
    // Check the pointer and the size of the data: the header must be complete.
    if (data == nullptr || dataSize < PARAMS_HEADER_SIZE)
    {
        return false;
    }

    // Check the data type and the version.
    if (data[0] != PARAMS_DATA_TYPE || !isVersionValid(data))
    {
        return false;
    }

    // Decode into a temporary object: this object is changed only if the
    // whole data is valid. Fields which are not selected by the mask are set
    // to zero, initString is empty.
    CameraParams result;
    result.initString.clear();
    const auto fields = makeFieldTable(result);
    int pos = PARAMS_HEADER_SIZE;
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        const FieldRef& field = fields[i];
        const bool encoded = (data[maskBytePos(i)] & maskBit(i)) != 0;
        if (!encoded)
        {
            std::memset(field.value, 0, static_cast<size_t>(field.size));
            continue;
        }

        // Check that the field is inside the data.
        if (dataSize - pos < field.size)
        {
            return false;
        }
        if (field.size == FLAG_SIZE)
        {
            *static_cast<bool*>(field.value) = data[pos] != 0x00;
        }
        else
        {
            std::memcpy(field.value, &data[pos],
                        static_cast<size_t>(field.size));
        }
        pos += field.size;
    }

    *this = result;

    return true;
}



void cr::camera::Camera::encodeSetParamCommand(
        uint8_t* data, int& size, CameraParam id, float value)
{
    // Nothing is encoded without a buffer.
    if (data == nullptr)
    {
        size = 0;
        return;
    }

    // Fill header and data.
    writeHeader(data, SET_PARAM_DATA_TYPE);
    const int paramId = static_cast<int>(id);
    std::memcpy(&data[COMMAND_ID_POS], &paramId, sizeof(paramId));
    std::memcpy(&data[COMMAND_VALUE_POS], &value, sizeof(value));
    size = SET_PARAM_COMMAND_SIZE;
}



void cr::camera::Camera::encodeCommand(
        uint8_t* data, int& size, cr::camera::CameraCommand id)
{
    // Nothing is encoded without a buffer.
    if (data == nullptr)
    {
        size = 0;
        return;
    }

    // Fill header and data.
    writeHeader(data, COMMAND_DATA_TYPE);
    const int commandId = static_cast<int>(id);
    std::memcpy(&data[COMMAND_ID_POS], &commandId, sizeof(commandId));
    size = COMMAND_SIZE;
}



int cr::camera::Camera::decodeCommand(uint8_t* data,
                                      int size,
                                      cr::camera::CameraParam& paramId,
                                      cr::camera::CameraCommand& commandId,
                                      float& value)
{
    // Check the pointer, the size (both commands have at least this size) and
    // the version.
    if (data == nullptr || size < COMMAND_SIZE || !isVersionValid(data))
    {
        return DECODE_ERROR;
    }

    // Extract the ID. An ID which is outside of the enum is an error: it is
    // not passed to the camera controller. The output arguments are changed
    // only after all checks.
    int id = 0;
    std::memcpy(&id, &data[COMMAND_ID_POS], sizeof(id));

    // Action command: the size must be exact.
    if (data[0] == COMMAND_DATA_TYPE)
    {
        if (size != COMMAND_SIZE ||
            id < FIRST_COMMAND_ID || id > LAST_COMMAND_ID)
        {
            return DECODE_ERROR;
        }
        commandId = static_cast<CameraCommand>(id);
        value = 0.0f;
        return DECODED_COMMAND;
    }

    // Set param command: the size must be exact.
    if (data[0] == SET_PARAM_DATA_TYPE)
    {
        if (size != SET_PARAM_COMMAND_SIZE ||
            id < FIRST_PARAM_ID || id > LAST_PARAM_ID)
        {
            return DECODE_ERROR;
        }
        paramId = static_cast<CameraParam>(id);
        std::memcpy(&value, &data[COMMAND_VALUE_POS], sizeof(value));
        return DECODED_SET_PARAM;
    }

    return DECODE_ERROR;
}
