#pragma once
#include <cstdint>
#include <string>
#include "ConfigReader.h"



namespace cr
{
namespace camera
{
/**
 * @brief Camera params mask.
 *
 * Each flag selects the CameraParams field with the same name for
 * serialization (see CameraParams::encode(...)). The order of the flags is the
 * order of the bits of the mask in the encoded data: the first flag is the
 * most significant bit of the first mask byte.
 */
typedef struct CameraParamsMask
{
    bool width{true};                         ///< Serialize the field.
    bool height{true};                        ///< Serialize the field.
    bool displayMode{true};                   ///< Serialize the field.
    bool videoOutput{true};                   ///< Serialize the field.
    bool logMode{true};                       ///< Serialize the field.
    bool exposureMode{true};                  ///< Serialize the field.
    bool exposureTime{true};                  ///< Serialize the field.
    bool whiteBalanceMode{true};              ///< Serialize the field.
    bool whiteBalanceArea{true};              ///< Serialize the field.
    bool wideDynamicRangeMode{true};          ///< Serialize the field.
    bool stabilizationMode{true};             ///< Serialize the field.
    bool isoSensitivity{true};                ///< Serialize the field.
    bool sceneMode{true};                     ///< Serialize the field.
    bool fps{true};                           ///< Serialize the field.
    bool brightnessMode{true};                ///< Serialize the field.
    bool brightness{true};                    ///< Serialize the field.
    bool contrast{true};                      ///< Serialize the field.
    bool gainMode{true};                      ///< Serialize the field.
    bool gain{true};                          ///< Serialize the field.
    bool sharpeningMode{true};                ///< Serialize the field.
    bool sharpening{true};                    ///< Serialize the field.
    bool palette{true};                       ///< Serialize the field.
    bool agcMode{true};                       ///< Serialize the field.
    bool shutterMode{true};                   ///< Serialize the field.
    bool shutterPos{true};                    ///< Serialize the field.
    bool shutterSpeed{true};                  ///< Serialize the field.
    bool digitalZoomMode{true};               ///< Serialize the field.
    bool digitalZoom{true};                   ///< Serialize the field.
    bool exposureCompensationMode{true};      ///< Serialize the field.
    bool exposureCompensationPosition{true};  ///< Serialize the field.
    bool defogMode{true};                     ///< Serialize the field.
    bool dehazeMode{true};                    ///< Serialize the field.
    bool noiseReductionMode{true};            ///< Serialize the field.
    bool blackAndWhiteFilterMode{true};       ///< Serialize the field.
    bool filterMode{true};                    ///< Serialize the field.
    bool nucMode{true};                       ///< Serialize the field.
    bool autoNucIntervalMsec{true};           ///< Serialize the field.
    bool imageFlip{true};                     ///< Serialize the field.
    bool ddeMode{true};                       ///< Serialize the field.
    bool ddeLevel{true};                      ///< Serialize the field.
    bool roiX0{true};                         ///< Serialize the field.
    bool roiY0{true};                         ///< Serialize the field.
    bool roiX1{true};                         ///< Serialize the field.
    bool roiY1{true};                         ///< Serialize the field.
    bool temperature{true};                   ///< Serialize the field.
    bool alcGate{true};                       ///< Serialize the field.
    bool sensitivity{true};                   ///< Serialize the field.
    bool changingMode{true};                  ///< Serialize the field.
    bool changingLevel{true};                 ///< Serialize the field.
    bool chromaLevel{true};                   ///< Serialize the field.
    bool detail{true};                        ///< Serialize the field.
    bool profile{true};                       ///< Serialize the field.
    bool isConnected{true};                   ///< Serialize the field.
    bool isOpen{true};                        ///< Serialize the field.
    bool type{true};                          ///< Serialize the field.
    bool custom1{true};                       ///< Serialize the field.
    bool custom2{true};                       ///< Serialize the field.
    bool custom3{true};                       ///< Serialize the field.
} CameraParamsMask;



/**
 * @brief Camera params class.
 *
 * @note The class is not thread-safe: an object must not be accessed from
 * several threads at the same time without external synchronization.
 */
class CameraParams
{
public:
    /// Initialization string. Formats depends on implementation.
    std::string initString{"/dev/ttyUSB0;9600;20"};
    /// Video frame width. Value from 0 to 16384.
    int width{0};
    /// Video frame height Value from 0 to 16384.
    int height{0};
    /// Display menu mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off. 1 - On.
    int displayMode{0};
    /// Video output type. Value depends on implementation.
    int videoOutput{0};
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal (console), 3 - File and terminal.
    int logMode{0};
    /// Exposure mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Manual, 1 - Auto (default),
    /// 2 - Shutter priority, 3 - Aperture priority.
    int exposureMode{1};
    /// Exposure time of the camera sensor. The exposure time is limited by the
    /// frame interval. Camera controller should interpret the values as 100 us
    /// units, where the value 1 stands for 1/10000th of a second, 10000 for
    /// 1 second and 100000 for 10 seconds.
    int exposureTime{0};
    /// White balance mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    int whiteBalanceMode{1};
    /// White balance area. Value depends on implementation.
    int whiteBalanceArea{0};
    /// White dynamic range mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    int wideDynamicRangeMode{0};
    /// Image stabilization mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    int stabilizationMode{0};
    /// ISO sensitivity. Value depends on implementation.
    int isoSensitivity{0};
    /// Scene mode. Value depends on implementation.
    int sceneMode{0};
    /// FPS.
    float fps{0.0f};
    /// Brightness mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Manual, 1 - Auto.
    int brightnessMode{1};
    /// Brightness. Value 0 - 100%.
    int brightness{0};
    /// Contrast. Value 1 - 100%.
    int contrast{0};
    /// Gain mode. Value depends on implementation but it is recommended to keep
    /// default values: 0 - Manual, 1 - Auto.
    int gainMode{1};
    /// Gain. Value 1 - 100%.
    int gain{0};
    /// Sharpening mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Manual, 1 - Auto.
    int sharpeningMode{0};
    /// Sharpening. Value 1 - 100%.
    int sharpening{0};
    /// Palette. Value depends on implementation but it is recommended to keep
    /// default values for thermal cameras: 0 - White hot, 1 - Black hot.
    int palette{0};
    /// Analog gain control mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    int agcMode{1};
    /// Shutter mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Manual, 1 - Auto.
    int shutterMode{1};
    /// Shutter position. 0 (full close) - 65535 (full open).
    int shutterPos{0};
    /// Shutter speed. Value: 0 - 100%.
    int shutterSpeed{0};
    /// Digital zoom mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off, 1 - On.
    int digitalZoomMode{0};
    /// Digital zoom. Value 1.0 (x1) - 20.0 (x20).
    float digitalZoom{1.0f};
    /// Exposure compensation mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    int exposureCompensationMode{0};
    /// Exposure compensation position. Value depends on particular camera
    /// controller.
    int exposureCompensationPosition{0};
    /// Defog mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Off, 1 - On.
    int defogMode{0};
    /// Dehaze mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Off, 1 - On.
    int dehazeMode{0};
    /// Noise reduction mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - 2D, 3 - 3D.
    int noiseReductionMode{0};
    /// Black and white filter mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    int blackAndWhiteFilterMode{0};
    /// Filter mode. Value depends on implementation.
    int filterMode{0};
    /// NUC mode for thermal cameras. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    int nucMode{0};
    /// Auto NUC interval for thermal cameras. Value in milliseconds
    /// from 0 (Off) to 100000.
    int autoNucIntervalMsec{0};
    /// Image flip mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off, 1 - Horizontal, 2 - Vertical,
    /// 3 - Horizontal and vertical.
    int imageFlip{0};
    /// DDE mode. Value depends on implementation but it is recommended to keep
    /// default values: 0 - Off, 1 - On.
    int ddeMode{0};
    /// DDE level. Value depends on implementation.
    float ddeLevel{0};
    /// ROI top-left horizontal position, pixels.
    int roiX0{0};
    /// ROI top-left vertical position, pixels.
    int roiY0{0};
    /// ROI bottom-right horizontal position, pixels.
    int roiX1{0};
    /// ROI bottom-right vertical position, pixels.
    int roiY1{0};
    /// Camera temperature, degree.
    float temperature{0.0f};
    /// ALC gate. Value depends on implementation.
    int alcGate{0};
    /// Sensor sensitivity. Value depends on implementation.
    float sensitivity{0};
    /// Changing mode (day / night). Value depends on implementation.
    int changingMode{0};
    /// Changing level (day / night). Value depends on implementation.
    float changingLevel{0.0f};
    /// Chroma level. Values: 0 - 100%.
    int chromaLevel{0};
    /// Details, enhancement. Values: 0 - 100%.
    int detail{0};
    /// Camera settings profile. Value depends on implementation.
    int profile{0};
    /// Connection status (read only). Shows if we have response from camera.
    /// Value: false - not connected, true - connected.
    bool isConnected{false};
    /// Open status (read only):
    /// true - camera control port open, false - not open.
    bool isOpen{false};
    /// Camera type. Value depends on implementation.
    int type{0};
    /// Camera custom param. Value depends on implementation.
    float custom1{0.0f};
    /// Camera custom param. Value depends on implementation.
    float custom2{0.0f};
    /// Camera custom param. Value depends on implementation.
    float custom3{0.0f};

    // JSON read / write of the fields. The fields temperature, isConnected and
    // isOpen are not stored in JSON.
    JSON_READABLE(CameraParams, initString, width, height, displayMode,
                  videoOutput, logMode, exposureMode, exposureTime,
                  whiteBalanceMode, whiteBalanceArea, wideDynamicRangeMode,
                  stabilizationMode, isoSensitivity, sceneMode, fps,
                  brightnessMode, brightness, contrast, gainMode, gain,
                  sharpeningMode, sharpening, palette, agcMode, shutterMode,
                  shutterPos, shutterSpeed, digitalZoomMode, digitalZoom,
                  exposureCompensationMode, exposureCompensationPosition,
                  defogMode, dehazeMode, noiseReductionMode,
                  blackAndWhiteFilterMode, filterMode, nucMode,
                  autoNucIntervalMsec, imageFlip, ddeMode, ddeLevel, roiX0,
                  roiY0, roiX1, roiY1, alcGate, sensitivity, changingMode,
                  changingLevel, chromaLevel, detail, profile, type, custom1,
                  custom2, custom3)

    /**
     * @brief Default constructor. All fields have default values.
     */
    CameraParams() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    CameraParams(const CameraParams& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    CameraParams(CameraParams&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    CameraParams& operator= (const CameraParams& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    CameraParams& operator= (CameraParams&& src) = default;

    /**
     * @brief Encode (serialize) params. The method doesn't encode initString.
     *
     * The encoded data contains the data type, the version of the library
     * (major and minor), the mask of 8 bytes and the values of the fields
     * selected by the mask. The values are stored in the byte order of the
     * host.
     *
     * @param data Pointer to data buffer. Must not be nullptr. The method
     * can't check that the buffer is valid for bufferSize bytes: this is the
     * contract of the method.
     * @param bufferSize Data buffer size, bytes. Must be >= 237 (the size of
     * the data with all fields selected).
     * @param size Size of encoded data, bytes. Set to 0 if the method returns
     * FALSE.
     * @param mask Pointer to parameters mask structure. If nullptr all fields
     * are encoded.
     * @return TRUE if params encoded or FALSE if not (data is nullptr or
     * bufferSize is too small).
     */
    bool encode(uint8_t* data, int bufferSize, int& size,
                CameraParamsMask* mask = nullptr);

    /**
     * @brief Decode (deserialize) params encoded by encode(...) method.
     *
     * The method checks the data type, the version and the size of the data
     * before reading each field. A field which is not selected by the mask of
     * the encoded data is set to zero (false) and initString is set to an
     * empty string. Mask bits which don't belong to any field and bytes after
     * the last field are ignored. Values of the fields are not checked against
     * any range: the camera controller must validate them before use.
     *
     * @param data Pointer to encoded data. Must not be nullptr.
     * @param dataSize Size of the encoded data, bytes. Must be >= 11 (the
     * size of the data without fields).
     * @return TRUE if params decoded or FALSE if not. If FALSE is returned
     * the object is not changed.
     */
    bool decode(uint8_t* data, int dataSize);
};



/// Camera controller commands enum. The values are consecutive: the first
/// value is RESTART and the last one is DEFREEZE. Camera::decodeCommand(...)
/// uses them to check the command ID.
enum class CameraCommand
{
    /// Restart camera controller.
    RESTART = 1,
    /// Do NUC.
    NUC,
    /// Apply settings.
    APPLY_PARAMS,
    /// Save params.
    SAVE_PARAMS,
    /// Menu on.
    MENU_ON,
    /// Menu off.
    MENU_OFF,
    /// Menu set.
    MENU_SET,
    /// Menu up.
    MENU_UP,
    /// Menu down.
    MENU_DOWN,
    /// Menu left.
    MENU_LEFT,
    /// Menu right.
    MENU_RIGHT,
    /// Freeze image.
    FREEZE,
    /// Disable freeze. The last value of the enum.
    DEFREEZE
};



/// Camera controller params. The values are consecutive: the first value is
/// WIDTH and the last one is CUSTOM_3. Camera::decodeCommand(...) uses them to
/// check the param ID.
enum class CameraParam
{
    /// Video frame width. Value from 0 to 16384.
    WIDTH = 1,
    /// Video frame height Value from 0 to 16384.
    HEIGHT,
    /// Display menu mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off. 1 - On.
    DISPLAY_MODE,
    /// Video output type. Value depends on implementation.
    VIDEO_OUTPUT,
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal (console), 3 - File and terminal.
    LOG_MODE,
    /// Exposure mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Manual, 1 - Auto (default),
    /// 2 - Shutter priority, 3 - Aperture priority.
    EXPOSURE_MODE,
    /// Exposure time of the camera sensor. The exposure time is limited by the
    /// frame interval. Camera controller should interpret the values as 100 us
    /// units, where the value 1 stands for 1/10000th of a second, 10000 for
    /// 1 second and 100000 for 10 seconds.
    EXPOSURE_TIME,
    /// White balance mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    WHITE_BALANCE_MODE,
    /// White balance area. Value depends on implementation.
    WHITE_BALANCE_AREA,
    /// White dynamic range mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    WIDE_DYNAMIC_RANGE_MODE,
    /// Image stabilization mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    STABILIZATION_MODE,
    /// ISO sensitivity. Value depends on implementation.
    ISO_SENSITIVITY,
    /// Scene mode. Value depends on implementation.
    SCENE_MODE,
    /// FPS.
    FPS,
    /// Brightness mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Manual, 1 - Auto.
    BRIGHTNESS_MODE,
    /// Brightness. Value 0 - 100%.
    BRIGHTNESS,
    /// Contrast. Value 1 - 100%.
    CONTRAST,
    /// Gain mode. Value depends on implementation but it is recommended to keep
    /// default values: 0 - Manual, 1 - Auto.
    GAIN_MODE,
    /// Gain. Value 1 - 100%.
    GAIN,
    /// Sharpening mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Manual, 1 - Auto.
    SHARPENING_MODE,
    /// Sharpening. Value 1 - 100%.
    SHARPENING,
    /// Palette. Value depends on implementation but it is recommended to keep
    /// default values for thermal cameras: 0 - White hot, 1 - Black hot.
    PALETTE,
    /// Analog gain control mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    AGC_MODE,
    /// Shutter mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Manual, 1 - Auto.
    SHUTTER_MODE,
    /// Shutter position. 0 (full close) - 65535 (full open).
    SHUTTER_POSITION,
    /// Shutter speed. Value: 0 - 100%.
    SHUTTER_SPEED,
    /// Digital zoom mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off, 1 - On.
    DIGITAL_ZOOM_MODE,
    /// Digital zoom. Value 1.0 (x1) - 20.0 (x20).
    DIGITAL_ZOOM,
    /// Exposure compensation mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    EXPOSURE_COMPENSATION_MODE,
    /// Exposure compensation position. Value depends on particular camera
    /// controller.
    EXPOSURE_COMPENSATION_POSITION,
    /// Defog mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Off, 1 - On.
    DEFOG_MODE,
    /// Dehaze mode. Value depends on implementation but it is recommended to
    /// keep default values: 0 - Off, 1 - On.
    DEHAZE_MODE,
    /// Noise reduction mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - 2D, 3 - 3D.
    NOISE_REDUCTION_MODE,
    /// Black and white filter mode. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Off, 1 - On.
    BLACK_WHITE_FILTER_MODE,
    /// Filter mode. Value depends on implementation.
    FILTER_MODE,
    /// NUC mode for thermal cameras. Value depends on implementation but it is
    /// recommended to keep default values: 0 - Manual, 1 - Auto.
    NUC_MODE,
    /// Auto NUC interval for thermal cameras. Value in milliseconds
    /// from 0 (Off) to 100000.
    AUTO_NUC_INTERVAL_MSEC,
    /// Image flip mode. Value depends on implementation but it is recommended
    /// to keep default values: 0 - Off, 1 - Horizontal, 2 - Vertical,
    /// 3 - Horizontal and vertical.
    IMAGE_FLIP,
    /// DDE mode. Value depends on implementation but it is recommended to keep
    /// default values: 0 - Off, 1 - On.
    DDE_MODE,
    /// DDE level. Value depends on implementation.
    DDE_LEVEL,
    /// ROI top-left horizontal position, pixels.
    ROI_X0,
    /// ROI top-left vertical position, pixels.
    ROI_Y0,
    /// ROI bottom-right horizontal position, pixels.
    ROI_X1,
    /// ROI bottom-right vertical position, pixels.
    ROI_Y1,
    /// Camera temperature, degree.
    TEMPERATURE,
    /// ALC gate. Value depends on implementation.
    ALC_GATE,
    /// Sensor sensitivity. Value depends on implementation.
    SENSITIVITY,
    /// Changing mode (day / night). Value depends on implementation.
    CHANGING_MODE,
    /// Changing level (day / night). Value depends on implementation.
    CHANGING_LEVEL,
    /// Chroma level. Values: 0 - 100%.
    CHROMA_LEVEL,
    /// Details, enhancement. Values: 0 - 100%.
    DETAIL,
    /// Camera settings profile. Value depends on implementation.
    PROFILE,
    /// Connection status (read only). Shows if we have response from camera.
    /// Value: 0 - not connected, 1 - connected.
    IS_CONNECTED,
    /// Open status (read only):
    /// 1 - camera control port open, 0 - not open.
    IS_OPEN,
    /// Camera type. Value depends on implementation.
    TYPE,
    /// Camera custom param. Value depends on implementation.
    CUSTOM_1,
    /// Camera custom param. Value depends on implementation.
    CUSTOM_2,
    /// Camera custom param. Value depends on implementation. The last value
    /// of the enum.
    CUSTOM_3
};



/**
 * @brief Camera controller interface class.
 */
class Camera
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~Camera();

    /**
     * @brief Get Camera class version.
     * @return String of current class version "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Open camera controller.
     * @param initString Init string. Format depends on camera controller.
     * @return TRUE if the camera controller is init or FALSE.
     */
    virtual bool openCamera(std::string initString) = 0;

    /**
     * @brief Init camera controller by set of parameters. Can be used instead
     * openCamera(...) method.
     * @param params Camera parameters. The initString field is used as the
     * init string.
     * @return TRUE if the camera controller is init or FALSE if not.
     */
    virtual bool initCamera(CameraParams& params) = 0;

    /**
     * @brief Close camera connection.
     */
    virtual void closeCamera() = 0;

    /**
     * @brief Get camera open status.
     * @return TRUE if the camera is open or FALSE.
     */
    virtual bool isCameraOpen() = 0;

    /**
     * @brief Get camera connection status.
     * @return TRUE if the camera controller has data exchange with the camera
     * equipment or FALSE.
     */
    virtual bool isCameraConnected() = 0;

    /**
     * @brief Set the camera controller parameter.
     * @note The implementation must be thread-safe.
     * @param id Param ID.
     * @param value Param value.
     * @return TRUE if the property set or FALSE.
     */
    virtual bool setParam(CameraParam id, float value) = 0;

    /**
     * @brief Get the camera controller parameter.
     * @note The implementation must be thread-safe.
     * @param id Parameter ID.
     * @return Param value or -1 if the param doesn't exist.
     */
    virtual float getParam(CameraParam id) = 0;

    /**
     * @brief Get all camera controller parameters.
     * @note The implementation must be thread-safe.
     * @param params Reference to CameraParams object.
     */
    virtual void getParams(CameraParams& params) = 0;

    /**
     * @brief Execute camera controller action command.
     * @note The implementation must be thread-safe.
     * @param id Command ID.
     * @return TRUE if the command executed or FALSE.
     */
    virtual bool executeCommand(CameraCommand id) = 0;

    /**
     * @brief Encode set param command.
     *
     * The method is thread-safe. The value is not checked: it is transported
     * as is (also NaN and infinity).
     *
     * @param data Pointer to data buffer. Must not be nullptr. The method
     * can't check that the buffer is valid for 11 bytes: this is the contract
     * of the method.
     * @param size Size of encoded command, bytes. Is 11 after encoding and 0
     * if data is nullptr.
     * @param id Camera parameter id.
     * @param value Camera parameter value.
     */
    static void encodeSetParamCommand(
            uint8_t* data, int& size, CameraParam id, float value);

    /**
     * @brief Encode command.
     *
     * The method is thread-safe.
     *
     * @param data Pointer to data buffer. Must not be nullptr. The method
     * can't check that the buffer is valid for 7 bytes: this is the contract
     * of the method.
     * @param size Size of encoded data, bytes. Is 7 after encoding and 0 if
     * data is nullptr.
     * @param id Camera command ID.
     */
    static void encodeCommand(
            uint8_t* data, int& size, CameraCommand id);

    /**
     * @brief Decode command.
     *
     * The method checks the pointer, the size, the version and the ID: the ID
     * must be inside the range of CameraCommand or CameraParam enum. The
     * output arguments are changed only if the command was decoded. The
     * method is thread-safe.
     *
     * @param data Pointer to command data. Must not be nullptr.
     * @param size Size of data, bytes. Must be 7 for action command and 11
     * for set param command.
     * @param paramId Output param ID (set param command only).
     * @param commandId Output command ID (action command only).
     * @param value Output param value (set param command) or 0 (action
     * command).
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             CameraParam& paramId,
                             CameraCommand& commandId,
                             float& value);

    /**
     * @brief Decode and execute command.
     * @note The implementation must be thread-safe.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @return TRUE if command decoded and executed or FALSE if not.
     */
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;

protected:

    /**
     * @brief Default constructor. The class can be used as a base only.
     */
    Camera() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    Camera(const Camera& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    Camera(Camera&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    Camera& operator= (const Camera& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    Camera& operator= (Camera&& src) = default;
};
}
}
