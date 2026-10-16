#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
#include "Camera.h"
#include "CameraVersion.h"
#include "ConfigReader.h"



namespace
{
using cr::camera::Camera;
using cr::camera::CameraCommand;
using cr::camera::CameraParam;
using cr::camera::CameraParams;
using cr::camera::CameraParamsMask;

/// Number of fields of CameraParams which are serialized.
constexpr size_t FIELDS_NUMBER{58};
/// Size of the encoded params without fields: data type, version, mask.
constexpr int HEADER_SIZE{11};
/// Position of the mask in the encoded params.
constexpr int MASK_POS{3};
/// Size of the encoded params if all fields are selected.
constexpr int MAX_SIZE{237};
/// Size of the encoded action command.
constexpr int COMMAND_SIZE{7};
/// Size of the encoded set param command.
constexpr int SET_PARAM_SIZE{11};
/// Number of the first and the last ID of the commands.
constexpr int FIRST_COMMAND_ID{1};
constexpr int LAST_COMMAND_ID{13};
/// Number of the first and the last ID of the params.
constexpr int FIRST_PARAM_ID{1};
constexpr int LAST_PARAM_ID{58};
/// Number of random objects in the round trip tests.
constexpr int ROUND_TRIP_NUMBER{5000};
/// Number of damaged samples in the damaged data campaign.
constexpr int DAMAGED_NUMBER{40000};
/// Name of the file of the JSON file test.
const char* const JSON_FILE_NAME{"CameraTestParams.json"};



/// State of the test random generator. The tests use own deterministic
/// generator: results must be reproducible on all platforms.
uint32_t g_randomState{20240915U};



/// Get next random 32 bit number.
uint32_t randomBits()
{
    g_randomState ^= g_randomState << 13;
    g_randomState ^= g_randomState >> 17;
    g_randomState ^= g_randomState << 5;
    return g_randomState;
}



/// Get next random number in [0, limit).
int randomInt(int limit)
{
    return static_cast<int>(randomBits() % static_cast<uint32_t>(limit));
}



/// Print a failed check and return false.
bool fail(const char* message)
{
    std::cout << message << std::endl;
    return false;
}



/// Get the bits of a value: floats are compared by their bits, never with ==.
uint32_t bitsOf(int value)
{
    uint32_t bits{0};
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}



/// Get the bits of a value: floats are compared by their bits, never with ==.
uint32_t bitsOf(float value)
{
    uint32_t bits{0};
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}



/// Description of a serialized field: the name, the field of CameraParams and
/// the flag of CameraParamsMask. The order of the table is the order of the
/// fields in the encoded data: it is the specification of the format.
struct Field
{
    /// Name of the field.
    const char* name;
    /// Field of an int type or nullptr.
    int CameraParams::* intField;
    /// Field of a float type or nullptr.
    float CameraParams::* floatField;
    /// Field of a bool type or nullptr.
    bool CameraParams::* boolField;
    /// Flag of the mask.
    bool CameraParamsMask::* maskField;
};



/// Get the description of an int field.
constexpr Field makeField(const char* name, int CameraParams::* field,
                bool CameraParamsMask::* mask)
{
    return {name, field, nullptr, nullptr, mask};
}



/// Get the description of a float field.
constexpr Field makeField(const char* name, float CameraParams::* field,
                bool CameraParamsMask::* mask)
{
    return {name, nullptr, field, nullptr, mask};
}



/// Get the description of a bool field.
constexpr Field makeField(const char* name, bool CameraParams::* field,
                bool CameraParamsMask::* mask)
{
    return {name, nullptr, nullptr, field, mask};
}



/// Table of fields in the order of the encoded data.
constexpr std::array FIELDS{
    makeField("width", &CameraParams::width, &CameraParamsMask::width),
    makeField("height", &CameraParams::height, &CameraParamsMask::height),
    makeField("displayMode", &CameraParams::displayMode,
              &CameraParamsMask::displayMode),
    makeField("videoOutput", &CameraParams::videoOutput,
              &CameraParamsMask::videoOutput),
    makeField("logMode", &CameraParams::logMode, &CameraParamsMask::logMode),
    makeField("exposureMode", &CameraParams::exposureMode,
              &CameraParamsMask::exposureMode),
    makeField("exposureTime", &CameraParams::exposureTime,
              &CameraParamsMask::exposureTime),
    makeField("whiteBalanceMode", &CameraParams::whiteBalanceMode,
              &CameraParamsMask::whiteBalanceMode),
    makeField("whiteBalanceArea", &CameraParams::whiteBalanceArea,
              &CameraParamsMask::whiteBalanceArea),
    makeField("wideDynamicRangeMode", &CameraParams::wideDynamicRangeMode,
              &CameraParamsMask::wideDynamicRangeMode),
    makeField("stabilizationMode", &CameraParams::stabilizationMode,
              &CameraParamsMask::stabilizationMode),
    makeField("isoSensitivity", &CameraParams::isoSensitivity,
              &CameraParamsMask::isoSensitivity),
    makeField("sceneMode", &CameraParams::sceneMode,
              &CameraParamsMask::sceneMode),
    makeField("fps", &CameraParams::fps, &CameraParamsMask::fps),
    makeField("brightnessMode", &CameraParams::brightnessMode,
              &CameraParamsMask::brightnessMode),
    makeField("brightness", &CameraParams::brightness,
              &CameraParamsMask::brightness),
    makeField("contrast", &CameraParams::contrast,
              &CameraParamsMask::contrast),
    makeField("gainMode", &CameraParams::gainMode,
              &CameraParamsMask::gainMode),
    makeField("gain", &CameraParams::gain, &CameraParamsMask::gain),
    makeField("sharpeningMode", &CameraParams::sharpeningMode,
              &CameraParamsMask::sharpeningMode),
    makeField("sharpening", &CameraParams::sharpening,
              &CameraParamsMask::sharpening),
    makeField("palette", &CameraParams::palette, &CameraParamsMask::palette),
    makeField("agcMode", &CameraParams::agcMode, &CameraParamsMask::agcMode),
    makeField("shutterMode", &CameraParams::shutterMode,
              &CameraParamsMask::shutterMode),
    makeField("shutterPos", &CameraParams::shutterPos,
              &CameraParamsMask::shutterPos),
    makeField("shutterSpeed", &CameraParams::shutterSpeed,
              &CameraParamsMask::shutterSpeed),
    makeField("digitalZoomMode", &CameraParams::digitalZoomMode,
              &CameraParamsMask::digitalZoomMode),
    makeField("digitalZoom", &CameraParams::digitalZoom,
              &CameraParamsMask::digitalZoom),
    makeField("exposureCompensationMode",
              &CameraParams::exposureCompensationMode,
              &CameraParamsMask::exposureCompensationMode),
    makeField("exposureCompensationPosition",
              &CameraParams::exposureCompensationPosition,
              &CameraParamsMask::exposureCompensationPosition),
    makeField("defogMode", &CameraParams::defogMode,
              &CameraParamsMask::defogMode),
    makeField("dehazeMode", &CameraParams::dehazeMode,
              &CameraParamsMask::dehazeMode),
    makeField("noiseReductionMode", &CameraParams::noiseReductionMode,
              &CameraParamsMask::noiseReductionMode),
    makeField("blackAndWhiteFilterMode",
              &CameraParams::blackAndWhiteFilterMode,
              &CameraParamsMask::blackAndWhiteFilterMode),
    makeField("filterMode", &CameraParams::filterMode,
              &CameraParamsMask::filterMode),
    makeField("nucMode", &CameraParams::nucMode, &CameraParamsMask::nucMode),
    makeField("autoNucIntervalMsec", &CameraParams::autoNucIntervalMsec,
              &CameraParamsMask::autoNucIntervalMsec),
    makeField("imageFlip", &CameraParams::imageFlip,
              &CameraParamsMask::imageFlip),
    makeField("ddeMode", &CameraParams::ddeMode, &CameraParamsMask::ddeMode),
    makeField("ddeLevel", &CameraParams::ddeLevel,
              &CameraParamsMask::ddeLevel),
    makeField("roiX0", &CameraParams::roiX0, &CameraParamsMask::roiX0),
    makeField("roiY0", &CameraParams::roiY0, &CameraParamsMask::roiY0),
    makeField("roiX1", &CameraParams::roiX1, &CameraParamsMask::roiX1),
    makeField("roiY1", &CameraParams::roiY1, &CameraParamsMask::roiY1),
    makeField("temperature", &CameraParams::temperature,
              &CameraParamsMask::temperature),
    makeField("alcGate", &CameraParams::alcGate, &CameraParamsMask::alcGate),
    makeField("sensitivity", &CameraParams::sensitivity,
              &CameraParamsMask::sensitivity),
    makeField("changingMode", &CameraParams::changingMode,
              &CameraParamsMask::changingMode),
    makeField("changingLevel", &CameraParams::changingLevel,
              &CameraParamsMask::changingLevel),
    makeField("chromaLevel", &CameraParams::chromaLevel,
              &CameraParamsMask::chromaLevel),
    makeField("detail", &CameraParams::detail, &CameraParamsMask::detail),
    makeField("profile", &CameraParams::profile, &CameraParamsMask::profile),
    makeField("isConnected", &CameraParams::isConnected,
              &CameraParamsMask::isConnected),
    makeField("isOpen", &CameraParams::isOpen, &CameraParamsMask::isOpen),
    makeField("type", &CameraParams::type, &CameraParamsMask::type),
    makeField("custom1", &CameraParams::custom1, &CameraParamsMask::custom1),
    makeField("custom2", &CameraParams::custom2, &CameraParamsMask::custom2),
    makeField("custom3", &CameraParams::custom3, &CameraParamsMask::custom3)};
static_assert(FIELDS.size() == FIELDS_NUMBER, "wrong number of fields");
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(float) == 4, "float must be 4 bytes");



/// Flags of the fields selected for serialization.
using Flags = std::array<bool, FIELDS_NUMBER>;



/// Size of the field in the encoded data, bytes.
int fieldSize(const Field& field)
{
    return field.boolField != nullptr ? 1 : 4;
}



/// Get the size of the encoded params for the selected fields.
int expectedSize(const Flags& flags)
{
    int size = HEADER_SIZE;
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        if (flags[i])
        {
            size += fieldSize(FIELDS[i]);
        }
    }
    return size;
}



/// Fill the mask structure by flags.
void applyFlags(const Flags& flags, CameraParamsMask& mask)
{
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        mask.*(FIELDS[i].maskField) = flags[i];
    }
}



/// Get random flags. The variant selects the density of the selected fields.
Flags randomFlags(int variant)
{
    Flags flags{};
    for (bool& flag : flags)
    {
        switch (variant % 4)
        {
        case 0:
            flag = true;
            break;
        case 1:
            flag = (randomBits() & 1U) != 0;
            break;
        case 2:
            flag = (randomBits() & 7U) == 0;
            break;
        default:
            flag = (randomBits() & 7U) != 0;
            break;
        }
    }
    return flags;
}



/// Fill all fields by random bits (also NaN and infinity bit patterns of
/// floats) and set a random init string.
void randomParams(CameraParams& params)
{
    params.initString = "init" + std::to_string(randomBits());
    for (const Field& field : FIELDS)
    {
        if (field.intField != nullptr)
        {
            const uint32_t bits = randomBits();
            std::memcpy(&(params.*(field.intField)), &bits, sizeof(bits));
        }
        else if (field.floatField != nullptr)
        {
            const uint32_t bits = randomBits();
            std::memcpy(&(params.*(field.floatField)), &bits, sizeof(bits));
        }
        else
        {
            params.*(field.boolField) = (randomBits() & 1U) != 0;
        }
    }
}



/// Compare all serialized fields (not initString). Returns the number of
/// mismatches. The mismatches are printed if print is true.
int compareFields(const CameraParams& expected, const CameraParams& actual,
                  bool print)
{
    int errors = 0;
    for (const Field& field : FIELDS)
    {
        bool equal = true;
        if (field.intField != nullptr)
        {
            equal = bitsOf(expected.*(field.intField)) ==
                    bitsOf(actual.*(field.intField));
        }
        else if (field.floatField != nullptr)
        {
            equal = bitsOf(expected.*(field.floatField)) ==
                    bitsOf(actual.*(field.floatField));
        }
        else
        {
            equal = expected.*(field.boolField) == actual.*(field.boolField);
        }
        if (!equal)
        {
            if (print)
            {
                std::cout << "Mismatch in field " << field.name << std::endl;
            }
            ++errors;
        }
    }
    return errors;
}



/// Check that two objects are equal: all fields and the init string.
bool sameParams(const CameraParams& expected, const CameraParams& actual,
                bool print)
{
    const bool sameString = expected.initString == actual.initString;
    if (!sameString && print)
    {
        std::cout << "Mismatch in field initString" << std::endl;
    }
    return compareFields(expected, actual, print) == 0 && sameString;
}



/// Get the object which decode(...) must produce for the encoded data: the
/// selected fields are copied, other fields are zero, initString is empty.
CameraParams expectedDecoded(const CameraParams& source, const Flags& flags)
{
    CameraParams result;
    result.initString.clear();
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        const Field& field = FIELDS[i];
        if (field.intField != nullptr)
        {
            result.*(field.intField) = flags[i] ? source.*(field.intField) : 0;
        }
        else if (field.floatField != nullptr)
        {
            result.*(field.floatField) =
                    flags[i] ? source.*(field.floatField) : 0.0f;
        }
        else
        {
            result.*(field.boolField) =
                    flags[i] ? source.*(field.boolField) : false;
        }
    }
    return result;
}



/// Reference decoder written from the description of the format. It returns
/// false for data which must be rejected. Otherwise it fills the result.
bool referenceDecode(const std::vector<uint8_t>& data, CameraParams& result)
{
    if (data.size() < static_cast<size_t>(HEADER_SIZE) ||
        data[0] != 0x02 || data[1] != CAMERA_MAJOR_VERSION ||
        data[2] != CAMERA_MINOR_VERSION)
    {
        return false;
    }
    Flags flags{};
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        flags[i] = (data[static_cast<size_t>(MASK_POS) + i / 8] &
                    (0x80U >> (i % 8))) != 0;
    }
    if (data.size() < static_cast<size_t>(expectedSize(flags)))
    {
        return false;
    }
    CameraParams source;
    size_t pos = static_cast<size_t>(HEADER_SIZE);
    for (size_t i = 0; i < FIELDS_NUMBER; ++i)
    {
        const Field& field = FIELDS[i];
        if (!flags[i])
        {
            continue;
        }
        if (field.boolField != nullptr)
        {
            source.*(field.boolField) = data[pos] != 0;
            ++pos;
            continue;
        }
        uint32_t bits{0};
        std::memcpy(&bits, &data[pos], sizeof(bits));
        pos += sizeof(bits);
        if (field.intField != nullptr)
        {
            std::memcpy(&(source.*(field.intField)), &bits, sizeof(bits));
        }
        else
        {
            std::memcpy(&(source.*(field.floatField)), &bits, sizeof(bits));
        }
    }
    result = expectedDecoded(source, flags);
    return true;
}



/// Encode params to an exact-size vector (so that a sanitizer sees every
/// access outside of the encoded data).
bool encodeToVector(CameraParams& params, CameraParamsMask* mask,
                    std::vector<uint8_t>& result)
{
    std::vector<uint8_t> buffer(static_cast<size_t>(MAX_SIZE), 0xCD);
    int size = -1;
    if (!params.encode(buffer.data(), MAX_SIZE, size, mask))
    {
        return false;
    }
    if (size < HEADER_SIZE || size > MAX_SIZE)
    {
        return false;
    }
    result.assign(buffer.begin(), buffer.begin() + size);
    return true;
}



/// Decode data which is copied to an exact-size heap buffer.
bool decodeVector(const std::vector<uint8_t>& data, CameraParams& params)
{
    std::vector<uint8_t> exact(data);
    exact.shrink_to_fit();
    return params.decode(exact.data(), static_cast<int>(exact.size()));
}



/// Removes a file when the object is destroyed and reports a failed removal.
class TempFile
{
public:
    /// Class constructor. The file is removed by the destructor.
    explicit TempFile(std::string name) : m_name(std::move(name))
    {
    }

    /// Class destructor. Removes the file and reports an error if the file
    /// still exists.
    ~TempFile()
    {
        if (std::remove(m_name.c_str()) != 0)
        {
            const std::ifstream stillThere(m_name);
            if (stillThere.good())
            {
                std::cout << "Can't remove file " << m_name << std::endl;
            }
        }
    }

    TempFile(const TempFile&) = delete;
    TempFile(TempFile&&) = delete;
    TempFile& operator= (const TempFile&) = delete;
    TempFile& operator= (TempFile&&) = delete;

private:
    /// Name of the file.
    std::string m_name;
};



/// Copy test.
bool copyTest()
{
    CameraParams in;
    randomParams(in);

    // Copy constructor and copy assignment.
    CameraParams copied(in);
    if (!sameParams(in, copied, true))
    {
        return fail("Copy constructor");
    }
    CameraParams assigned;
    assigned = in;
    if (!sameParams(in, assigned, true))
    {
        return fail("Copy assignment");
    }

    // Self assignment (through a reference).
    const CameraParams& reference = assigned;
    assigned = reference;
    if (!sameParams(in, assigned, true))
    {
        return fail("Self assignment");
    }

    // Objects are independent.
    copied.width = ~copied.width;
    copied.initString += "x";
    if (in.width == copied.width || in.initString == copied.initString)
    {
        return fail("Objects are not independent");
    }

    // Move constructor and move assignment.
    CameraParams source(in);
    const CameraParams moved(std::move(source));
    if (!sameParams(in, moved, true))
    {
        return fail("Move constructor");
    }
    CameraParams source2(in);
    CameraParams moveAssigned;
    moveAssigned = std::move(source2);
    if (!sameParams(in, moveAssigned, true))
    {
        return fail("Move assignment");
    }

    return true;
}



/// Version test: the version string, the version macros and the version
/// in the encoded data.
bool versionTest()
{
    const std::string expected = std::to_string(CAMERA_MAJOR_VERSION) + "." +
            std::to_string(CAMERA_MINOR_VERSION) + "." +
            std::to_string(CAMERA_PATCH_VERSION);
    if (Camera::getVersion() != expected || expected != CAMERA_VERSION)
    {
        return fail("Version string doesn't match version macros");
    }

    CameraParams params;
    std::vector<uint8_t> data;
    if (!encodeToVector(params, nullptr, data))
    {
        return fail("Can't encode params");
    }
    if (data[0] != 0x02 || data[1] != CAMERA_MAJOR_VERSION ||
        data[2] != CAMERA_MINOR_VERSION)
    {
        return fail("Wrong header of encoded params");
    }

    return true;
}



/// Get flags with all fields selected.
Flags allFlags()
{
    Flags flags{};
    flags.fill(true);
    return flags;
}



/// Encode / decode params round trip: all fields, default mask.
bool encodeDecodeTest()
{
    bool result = true;
    for (int i = 0; i < ROUND_TRIP_NUMBER; ++i)
    {
        CameraParams in;
        randomParams(in);

        // Without mask (all fields) and with the mask which selects all.
        for (int useMask = 0; useMask < 2; ++useMask)
        {
            CameraParamsMask mask;
            std::vector<uint8_t> data;
            if (!encodeToVector(in, useMask != 0 ? &mask : nullptr, data))
            {
                return fail("Can't encode params");
            }
            if (data.size() != static_cast<size_t>(MAX_SIZE))
            {
                return fail("Wrong size of encoded params");
            }

            // The decoded object has all fields and an empty init string
            // (the init string is not encoded).
            CameraParams out;
            randomParams(out);
            if (!decodeVector(data, out))
            {
                return fail("Can't decode params");
            }
            if (!sameParams(expectedDecoded(in, allFlags()), out, true))
            {
                result = false;
            }
        }
    }
    return result;
}



/// Mask test: random masks, every single field, all fields except one and the
/// empty mask.
bool maskTest()
{
    bool result = true;

    // Random masks: size, mask bits, decoded object.
    for (int i = 0; i < ROUND_TRIP_NUMBER; ++i)
    {
        CameraParams in;
        randomParams(in);
        const Flags flags = randomFlags(i);
        CameraParamsMask mask;
        applyFlags(flags, mask);
        std::vector<uint8_t> data;
        if (!encodeToVector(in, &mask, data))
        {
            return fail("Can't encode params");
        }
        if (data.size() != static_cast<size_t>(expectedSize(flags)))
        {
            return fail("Wrong size of encoded params");
        }
        for (size_t f = 0; f < FIELDS_NUMBER; ++f)
        {
            const bool bit = (data[static_cast<size_t>(MASK_POS) + f / 8] &
                              (0x80U >> (f % 8))) != 0;
            if (bit != flags[f])
            {
                std::cout << "Wrong mask bit of field " << FIELDS[f].name
                          << std::endl;
                result = false;
            }
        }
        if ((data[static_cast<size_t>(MASK_POS) + 7] & 0x3FU) != 0)
        {
            return fail("Unused bits of the mask must be zero");
        }
        CameraParams out;
        randomParams(out);
        if (!decodeVector(data, out) ||
            !sameParams(expectedDecoded(in, flags), out, true))
        {
            result = false;
        }
    }

    // Single field and all fields except one.
    for (size_t f = 0; f < FIELDS_NUMBER; ++f)
    {
        for (int inverted = 0; inverted < 2; ++inverted)
        {
            Flags flags{};
            flags.fill(inverted != 0);
            flags[f] = inverted == 0;
            CameraParams in;
            randomParams(in);
            CameraParamsMask mask;
            applyFlags(flags, mask);
            std::vector<uint8_t> data;
            if (!encodeToVector(in, &mask, data) ||
                data.size() != static_cast<size_t>(expectedSize(flags)))
            {
                std::cout << "Wrong encoded size, field " << FIELDS[f].name
                          << std::endl;
                result = false;
                continue;
            }
            CameraParams out;
            randomParams(out);
            if (!decodeVector(data, out) ||
                !sameParams(expectedDecoded(in, flags), out, true))
            {
                std::cout << "Wrong decoding, field " << FIELDS[f].name
                          << std::endl;
                result = false;
            }
        }
    }

    // Empty mask: only the header is encoded and it can be decoded.
    CameraParams in;
    randomParams(in);
    Flags none{};
    none.fill(false);
    CameraParamsMask emptyMask;
    applyFlags(none, emptyMask);
    std::vector<uint8_t> data;
    if (!encodeToVector(in, &emptyMask, data) ||
        data.size() != static_cast<size_t>(HEADER_SIZE))
    {
        return fail("Wrong size of params with empty mask");
    }
    CameraParams out;
    randomParams(out);
    if (!decodeVector(data, out) ||
        !sameParams(expectedDecoded(in, none), out, true))
    {
        return fail("Can't decode params with empty mask");
    }

    return result;
}



/// Buffer boundaries test: encode(...) checks the pointer and the buffer size
/// and doesn't write after the encoded data.
bool bufferBoundariesTest()
{
    CameraParams in;
    randomParams(in);
    constexpr uint8_t SENTINEL{0xAB};

    // Null pointer.
    int size = 77;
    if (in.encode(nullptr, MAX_SIZE, size) || size != 0)
    {
        return fail("Null pointer is not rejected");
    }

    // Too small buffer: nothing is written, the size is zero.
    for (const int bufferSize : {std::numeric_limits<int>::min(), -1, 0, 1,
                           HEADER_SIZE, 100, MAX_SIZE - 1})
    {
        std::vector<uint8_t> buffer(static_cast<size_t>(MAX_SIZE), SENTINEL);
        size = 77;
        if (in.encode(buffer.data(), bufferSize, size) || size != 0)
        {
            return fail("Small buffer is not rejected");
        }
        for (const uint8_t value : buffer)
        {
            if (value != SENTINEL)
            {
                return fail("Buffer is changed by a rejected call");
            }
        }
    }

    // Exact size of the buffer: the data fits and nothing is written after
    // the encoded data.
    for (int i = 0; i < 2000; ++i)
    {
        const Flags flags = randomFlags(i);
        CameraParamsMask mask;
        applyFlags(flags, mask);
        std::vector<uint8_t> buffer(static_cast<size_t>(MAX_SIZE), SENTINEL);
        size = -1;
        if (!in.encode(buffer.data(), MAX_SIZE, size, &mask) ||
            size != expectedSize(flags))
        {
            return fail("Wrong result of encode");
        }
        for (size_t pos = static_cast<size_t>(size);
             pos < static_cast<size_t>(MAX_SIZE); ++pos)
        {
            if (buffer[pos] != SENTINEL)
            {
                return fail("Data is written after the encoded data");
            }
        }
    }

    // Exact-size heap buffer (a sanitizer sees every access outside of it).
    std::vector<uint8_t> exact(static_cast<size_t>(MAX_SIZE));
    exact.shrink_to_fit();
    if (!in.encode(exact.data(), MAX_SIZE, size) || size != MAX_SIZE)
    {
        return fail("Can't encode into the exact-size buffer");
    }

    return true;
}



/// Invalid data test: a rejected decode(...) returns false and doesn't change
/// the object.
bool invalidDataTest()
{
    bool result = true;
    CameraParams target;
    randomParams(target);
    const CameraParams before(target);

    CameraParams in;
    randomParams(in);
    std::vector<uint8_t> all;
    if (!encodeToVector(in, nullptr, all))
    {
        return fail("Can't encode params");
    }

    // Null pointer and wrong sizes.
    if (target.decode(nullptr, MAX_SIZE) || !sameParams(before, target, true))
    {
        return fail("Null pointer is not rejected");
    }
    for (const int size : {std::numeric_limits<int>::min(), -1, 0})
    {
        if (target.decode(all.data(), size) || !sameParams(before, target, true))
        {
            return fail("Wrong size is not rejected");
        }
    }

    // Every truncation of the data of random masks.
    for (int i = 0; i < 300; ++i)
    {
        CameraParams source;
        randomParams(source);
        CameraParamsMask mask;
        applyFlags(randomFlags(i), mask);
        std::vector<uint8_t> data;
        if (!encodeToVector(source, &mask, data))
        {
            return fail("Can't encode params");
        }
        for (size_t length = 0; length < data.size(); ++length)
        {
            const std::vector<uint8_t> part(data.begin(),
                    data.begin() + static_cast<std::ptrdiff_t>(length));
            if (decodeVector(part, target) || !sameParams(before, target, false))
            {
                std::cout << "Truncated data is accepted, length " << length
                          << std::endl;
                result = false;
            }
        }
    }

    // Every value of the data type and of the version bytes.
    for (size_t pos = 0; pos < 3; ++pos)
    {
        for (int value = 0; value < 256; ++value)
        {
            std::vector<uint8_t> data(all);
            data[pos] = static_cast<uint8_t>(value);
            const bool accepted = decodeVector(data, target);
            const bool valid = data == all;
            if (accepted != valid ||
                (!accepted && !sameParams(before, target, false)))
            {
                std::cout << "Wrong result for header byte " << pos
                          << " value " << value << std::endl;
                result = false;
            }
            if (accepted)
            {
                target = before;
            }
        }
    }

    // A mask bit without the data of the field.
    for (size_t f = 0; f < FIELDS_NUMBER; ++f)
    {
        std::vector<uint8_t> data(static_cast<size_t>(HEADER_SIZE), 0);
        data[0] = 0x02;
        data[1] = CAMERA_MAJOR_VERSION;
        data[2] = CAMERA_MINOR_VERSION;
        data[static_cast<size_t>(MASK_POS) + f / 8] =
                static_cast<uint8_t>(0x80U >> (f % 8));
        if (decodeVector(data, target) || !sameParams(before, target, false))
        {
            std::cout << "Missing data of field " << FIELDS[f].name
                      << std::endl;
            result = false;
        }
    }

    // Bytes after the last field are ignored.
    for (const int extra : {1, 3, 16})
    {
        std::vector<uint8_t> data(all);
        for (int i = 0; i < extra; ++i)
        {
            data.push_back(static_cast<uint8_t>(randomBits()));
        }
        CameraParams out;
        if (!decodeVector(data, out) ||
            !sameParams(expectedDecoded(in, allFlags()), out, true))
        {
            std::cout << "Trailing bytes are not ignored" << std::endl;
            result = false;
        }
    }

    // Mask bits which don't belong to any field are ignored.
    {
        std::vector<uint8_t> data(all);
        data[static_cast<size_t>(MASK_POS) + 7] |= 0x3F;
        CameraParams out;
        if (!decodeVector(data, out) ||
            !sameParams(expectedDecoded(in, allFlags()), out, true))
        {
            std::cout << "Unused mask bits are not ignored" << std::endl;
            result = false;
        }
    }

    // Bool fields: any non zero byte is true.
    {
        Flags flags{};
        flags.fill(false);
        for (size_t f = 0; f < FIELDS_NUMBER; ++f)
        {
            flags[f] = FIELDS[f].boolField != nullptr;
        }
        CameraParams source;
        CameraParamsMask mask;
        applyFlags(flags, mask);
        std::vector<uint8_t> data;
        if (!encodeToVector(source, &mask, data) ||
            data.size() != static_cast<size_t>(HEADER_SIZE) + 2)
        {
            return fail("Can't encode bool fields");
        }
        const uint8_t values[] = {0x00, 0x01, 0x02, 0x7F, 0x80, 0xFF};
        for (const uint8_t first : values)
        {
            for (const uint8_t second : values)
            {
                data[static_cast<size_t>(HEADER_SIZE)] = first;
                data[static_cast<size_t>(HEADER_SIZE) + 1] = second;
                CameraParams out;
                if (!decodeVector(data, out) || out.isConnected != (first != 0) ||
                    out.isOpen != (second != 0))
                {
                    return fail("Wrong value of a bool field");
                }
            }
        }
    }

    return result;
}



/// Damaged data campaign: deterministic damaged samples. The result of
/// decode(...) must be equal to the result of the reference decoder, a
/// rejected call must not change the object.
bool damagedDataTest()
{
    bool result = true;
    int accepted = 0;
    for (int i = 0; i < DAMAGED_NUMBER; ++i)
    {
        CameraParams source;
        randomParams(source);
        CameraParamsMask mask;
        applyFlags(randomFlags(i), mask);
        std::vector<uint8_t> data;
        if (!encodeToVector(source, &mask, data))
        {
            return fail("Can't encode params");
        }

        switch (i % 5)
        {
        case 0:
        case 1:
        {
            // Random replacement of 0.1, 0.5 or 2 percents of bytes (at least
            // one byte).
            const int percents[] = {1, 5, 20};
            const int promille = percents[randomInt(3)];
            int count = static_cast<int>(data.size()) * promille / 1000;
            count = count < 1 ? 1 : count;
            for (int k = 0; k < count; ++k)
            {
                data[static_cast<size_t>(randomInt(
                        static_cast<int>(data.size())))] =
                                static_cast<uint8_t>(randomBits());
            }
            break;
        }
        case 2:
        {
            // Truncation at 10, 50 or 90 percents of the size.
            const int percents[] = {10, 50, 90};
            data.resize(data.size() *
                        static_cast<size_t>(percents[randomInt(3)]) / 100);
            break;
        }
        case 3:
        {
            // Extra bytes.
            const int extra = 1 + randomInt(16);
            for (int k = 0; k < extra; ++k)
            {
                data.push_back(static_cast<uint8_t>(randomBits()));
            }
            break;
        }
        default:
        {
            // Random data, a half of it with a valid header.
            data.resize(static_cast<size_t>(randomInt(MAX_SIZE + 20)));
            for (uint8_t& value : data)
            {
                value = static_cast<uint8_t>(randomBits());
            }
            if (data.size() >= 3 && (i % 2) == 0)
            {
                data[0] = 0x02;
                data[1] = CAMERA_MAJOR_VERSION;
                data[2] = CAMERA_MINOR_VERSION;
            }
            break;
        }
        }

        CameraParams target;
        randomParams(target);
        const CameraParams before(target);
        CameraParams expected;
        const bool expectedAccepted = referenceDecode(data, expected);
        const bool decoded = decodeVector(data, target);
        if (decoded != expectedAccepted)
        {
            std::cout << "Wrong result of decode, sample " << i << std::endl;
            result = false;
        }
        else if (decoded)
        {
            ++accepted;
            if (!sameParams(expected, target, false))
            {
                std::cout << "Wrong decoded object, sample " << i
                          << std::endl;
                result = false;
            }
        }
        else if (!sameParams(before, target, false))
        {
            std::cout << "Object is changed by a rejected call, sample " << i
                      << std::endl;
            result = false;
        }
    }

    // The campaign must contain both accepted and rejected samples.
    if (accepted == 0 || accepted == DAMAGED_NUMBER)
    {
        return fail("The campaign doesn't cover both results");
    }

    return result;
}



/// Action commands test: round trip of every command ID.
bool actionCommandsTest()
{
    bool result = true;

    for (int id = FIRST_COMMAND_ID; id <= LAST_COMMAND_ID; ++id)
    {
        std::vector<uint8_t> data(static_cast<size_t>(COMMAND_SIZE));
        int size = -1;
        Camera::encodeCommand(data.data(), size,
                              static_cast<CameraCommand>(id));
        if (size != COMMAND_SIZE)
        {
            return fail("Wrong size of encoded command");
        }
        CameraParam paramId = CameraParam::GAIN;
        CameraCommand commandId = CameraCommand::NUC;
        float value = 5.0f;
        if (Camera::decodeCommand(data.data(), size, paramId, commandId,
                                  value) != 0 ||
            static_cast<int>(commandId) != id || bitsOf(value) != bitsOf(0.0f))
        {
            std::cout << "Wrong decoding of command " << id << std::endl;
            result = false;
        }
        if (paramId != CameraParam::GAIN)
        {
            std::cout << "Param ID is changed by command " << id << std::endl;
            result = false;
        }
    }

    return result;
}



/// Set param commands test: round trip of every param ID with random values,
/// also NaN and infinity.
bool setParamCommandsTest()
{
    bool result = true;

    for (int id = FIRST_PARAM_ID; id <= LAST_PARAM_ID; ++id)
    {
        for (int k = 0; k < 20; ++k)
        {
            const uint32_t patterns[] = {0x7FC00000U, 0x7F800000U, 0xFF800000U,
                                         0x00000001U};
            const uint32_t bits = k < 4 ? patterns[k] : randomBits();
            float outValue{0.0f};
            std::memcpy(&outValue, &bits, sizeof(bits));
            std::vector<uint8_t> data(static_cast<size_t>(SET_PARAM_SIZE));
            int size = -1;
            Camera::encodeSetParamCommand(data.data(), size,
                                          static_cast<CameraParam>(id),
                                          outValue);
            if (size != SET_PARAM_SIZE)
            {
                return fail("Wrong size of encoded set param command");
            }
            CameraParam paramId = CameraParam::GAIN;
            CameraCommand commandId = CameraCommand::NUC;
            float value = 0.0f;
            if (Camera::decodeCommand(data.data(), size, paramId, commandId,
                                      value) != 1 ||
                static_cast<int>(paramId) != id ||
                bitsOf(value) != bitsOf(outValue))
            {
                std::cout << "Wrong decoding of param " << id << std::endl;
                result = false;
            }
            if (commandId != CameraCommand::NUC)
            {
                std::cout << "Command ID is changed by param " << id
                          << std::endl;
                result = false;
            }
        }
    }

    return result;
}



/// Wrong commands test: wrong sizes, versions and data types are rejected and
/// the outputs are not changed.
bool wrongCommandsTest()
{
    bool result = true;

    for (int type = 0; type < 256; ++type)
    {
        for (int size = 0; size <= 14; ++size)
        {
            for (int variant = 0; variant < 3; ++variant)
            {
                std::vector<uint8_t> data(static_cast<size_t>(size), 0);
                if (size > 0)
                {
                    data[0] = static_cast<uint8_t>(type);
                }
                const int id = type == 0 ? 2 : 5;
                if (size >= 7)
                {
                    data[1] = static_cast<uint8_t>(
                            variant == 1 ? CAMERA_MAJOR_VERSION + 1
                                         : CAMERA_MAJOR_VERSION);
                    data[2] = static_cast<uint8_t>(
                            variant == 2 ? CAMERA_MINOR_VERSION + 1
                                         : CAMERA_MINOR_VERSION);
                    std::memcpy(&data[3], &id, sizeof(id));
                }
                const bool valid = variant == 0 &&
                        ((type == 0 && size == COMMAND_SIZE) ||
                         (type == 1 && size == SET_PARAM_SIZE));
                CameraParam paramId = CameraParam::AGC_MODE;
                CameraCommand commandId = CameraCommand::MENU_UP;
                float value = 7.0f;
                const int decoded = Camera::decodeCommand(
                        data.data(), size, paramId, commandId, value);
                int expected = -1;
                if (valid)
                {
                    expected = type == 0 ? 0 : 1;
                }
                if (decoded != expected)
                {
                    std::cout << "Wrong result " << decoded << ", type "
                              << type << ", size " << size << ", variant "
                              << variant << std::endl;
                    result = false;
                }
                if (!valid && (paramId != CameraParam::AGC_MODE ||
                               commandId != CameraCommand::MENU_UP ||
                               bitsOf(value) != bitsOf(7.0f)))
                {
                    std::cout << "Outputs are changed by a rejected command"
                              << std::endl;
                    result = false;
                }
            }
        }
    }

    return result;
}



/// Command IDs test: IDs outside of the enums are rejected.
bool commandIdsTest()
{
    bool result = true;
    const int wrongIds[] = {std::numeric_limits<int>::min(), -1, 0,
                            LAST_COMMAND_ID + 1, LAST_PARAM_ID + 1, 1000,
                            std::numeric_limits<int>::max()};
    for (int type = 0; type < 2; ++type)
    {
        for (int id : wrongIds)
        {
            // IDs of the commands are valid IDs of other type if they are
            // inside of the range of the params.
            const bool valid = (type == 0 && id >= FIRST_COMMAND_ID &&
                                id <= LAST_COMMAND_ID) ||
                               (type == 1 && id >= FIRST_PARAM_ID &&
                                id <= LAST_PARAM_ID);
            std::vector<uint8_t> data(static_cast<size_t>(
                    type == 0 ? COMMAND_SIZE : SET_PARAM_SIZE), 0);
            data[0] = static_cast<uint8_t>(type);
            data[1] = CAMERA_MAJOR_VERSION;
            data[2] = CAMERA_MINOR_VERSION;
            std::memcpy(&data[3], &id, sizeof(id));
            CameraParam paramId = CameraParam::AGC_MODE;
            CameraCommand commandId = CameraCommand::MENU_UP;
            float value = 7.0f;
            const int decoded = Camera::decodeCommand(
                    data.data(), static_cast<int>(data.size()), paramId,
                    commandId, value);
            if ((decoded == -1) == valid)
            {
                std::cout << "Wrong result for ID " << id << ", type "
                          << type << std::endl;
                result = false;
            }
        }
    }

    return result;
}



/// Null pointers test: the commands functions reject a null pointer.
bool nullCommandsTest()
{
    int size = 55;
    Camera::encodeCommand(nullptr, size, CameraCommand::NUC);
    if (size != 0)
    {
        return fail("Null pointer is not rejected by encodeCommand");
    }
    size = 55;
    Camera::encodeSetParamCommand(nullptr, size, CameraParam::GAIN, 1.0f);
    if (size != 0)
    {
        return fail("Null pointer is not rejected by encodeSetParamCommand");
    }
    CameraParam paramId = CameraParam::AGC_MODE;
    CameraCommand commandId = CameraCommand::MENU_UP;
    float value = 7.0f;
    if (Camera::decodeCommand(nullptr, SET_PARAM_SIZE, paramId, commandId,
                              value) != -1)
    {
        return fail("Null pointer is not rejected by decodeCommand");
    }

    return true;
}



/// Fill the params for JSON tests: JSON can't hold NaN and infinity.
void jsonParams(CameraParams& params)
{
    randomParams(params);
    for (const Field& field : FIELDS)
    {
        if (field.floatField != nullptr)
        {
            params.*(field.floatField) =
                    static_cast<float>(randomInt(2001) - 1000);
        }
    }
}



/// Get the object which must be read from JSON: temperature, isConnected and
/// isOpen are not stored in JSON.
CameraParams expectedFromJson(const CameraParams& written)
{
    CameraParams expected(written);
    expected.temperature = CameraParams().temperature;
    expected.isConnected = CameraParams().isConnected;
    expected.isOpen = CameraParams().isOpen;
    return expected;
}



/// JSON string test: round trip and invalid documents.
bool jsonStringTest()
{
    bool result = true;

    // Round trip.
    for (int i = 0; i < 200; ++i)
    {
        CameraParams in;
        jsonParams(in);
        cr::utils::ConfigReader writer;
        std::string json;
        if (!writer.set(in, "cameraParams") || !writer.writeToString(json))
        {
            return fail("Can't write params to string");
        }
        cr::utils::ConfigReader reader;
        CameraParams out;
        if (!reader.readFromString(json) || !reader.get(out, "cameraParams"))
        {
            return fail("Can't read params from string");
        }
        if (!sameParams(expectedFromJson(in), out, true))
        {
            result = false;
        }
    }

    // Invalid and incomplete documents are rejected, the object is not
    // changed.
    const char* const documents[] = {
        "",
        "{",
        "[]",
        "null",
        "{\"cameraParams\": 5}",
        "{\"cameraParams\": {}}",
        "{\"cameraParams\": {\"width\": 5}}",
        "{\"cameraParams\": {\"width\": \"text\"}}",
        "{\"other\": {}}"};
    for (const char* document : documents)
    {
        CameraParams out;
        randomParams(out);
        const CameraParams before(out);
        cr::utils::ConfigReader reader;
        if (reader.readFromString(document) &&
            reader.get(out, "cameraParams"))
        {
            std::cout << "Document is accepted: " << document << std::endl;
            result = false;
        }
        if (!sameParams(before, out, true))
        {
            std::cout << "Object is changed by document: " << document
                      << std::endl;
            result = false;
        }
    }

    return result;
}



/// JSON file test: write the params to a file and read them back. The file is
/// removed at the end of the test.
bool jsonFileTest()
{
    const TempFile file(JSON_FILE_NAME);
    CameraParams in;
    jsonParams(in);

    cr::utils::ConfigReader writer;
    if (!writer.set(in, "cameraParams") || !writer.writeToFile(JSON_FILE_NAME))
    {
        return fail("Can't write params to file");
    }
    cr::utils::ConfigReader reader;
    CameraParams out;
    if (!reader.readFromFile(JSON_FILE_NAME) ||
        !reader.get(out, "cameraParams"))
    {
        return fail("Can't read params from file");
    }

    return sameParams(expectedFromJson(in), out, true);
}



/// Run one test and print the result.
bool runTest(const char* title, bool (*test)())
{
    std::cout << title << ":" << std::endl;
    const bool passed = test();
    std::cout << (passed ? "OK" : "ERROR") << std::endl << std::endl;
    return passed;
}
}



/// Entry point. Returns 0 if all tests passed.
int main()
{
    std::cout << "#####################################" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "# Camera data structures test       #" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "#####################################" << std::endl;
    std::cout << std::endl;

    bool passed = true;
    passed = runTest("Copy test", copyTest) && passed;
    passed = runTest("Version test", versionTest) && passed;
    passed = runTest("Encode/Decode params test", encodeDecodeTest) && passed;
    passed = runTest("Params mask test", maskTest) && passed;
    passed = runTest("Buffer boundaries test", bufferBoundariesTest) && passed;
    passed = runTest("Invalid data test", invalidDataTest) && passed;
    passed = runTest("Damaged data test", damagedDataTest) && passed;
    passed = runTest("Action commands test", actionCommandsTest) && passed;
    passed = runTest("Set param commands test", setParamCommandsTest) &&
             passed;
    passed = runTest("Wrong commands test", wrongCommandsTest) && passed;
    passed = runTest("Command IDs test", commandIdsTest) && passed;
    passed = runTest("Null commands test", nullCommandsTest) && passed;
    passed = runTest("JSON string test", jsonStringTest) && passed;
    passed = runTest("JSON file test", jsonFileTest) && passed;

    std::cout << (passed ? "ALL TESTS PASSED" : "TESTS FAILED") << std::endl;

    return passed ? 0 : 1;
}
