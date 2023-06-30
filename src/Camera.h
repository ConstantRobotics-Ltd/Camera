#pragma once
#include <string>
#include <cstdint>
#include "ConfigReader.h"



namespace cr
{
namespace camera
{

/// Camera params structure.
class CameraParams
{
public:
    /// Initialization string. Formats depends on implementation.
    std::string initString{"/dev/ttyUSB0;9600;20"};
    /// Video frame width. Value from 0 to 16384.
    int width{0};
    /// Video frame height Value from 0 to 16384.
    int height{0};
    /// Display menu mode. Values: 0 - Off. 1 - On.
    int displayMode{0};
    /// Video output type. Value depends on particular camera controller.
    int videoOutput{0};
    /// Logging mode.
    /// Default values:
    /// 0 - Disable.
    /// 1 - Only file.
    /// 2 - Only terminal.
    /// 3 - File and terminal.
    int logMode{0};
    /// Exposure mode. Value depends on particular camera controller.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto (default),
    /// 2 - Shutter priority.
    /// 3 - Aperture priority.
    int exposureMode{1};
    /// Exposure time of the camera sensor. The exposure time is limited by the
    /// frame interval. Camera controller should interpret the values as 100 µs
    /// units, where the value 1 stands for 1/10000th of a second, 10000 for 1
    /// second and 100000 for 10 seconds.
    int exposureTime{0};
    /// White balance mode.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto
    int whiteBalanceMode{1};
    /// White balance area.
    int whiteBalanceArea{0};
    /// White dynamic range mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - On.
    int wideDynamicRangeMode{0};
    /// Image stabilization mode.
    /// Default value:
    /// 0 - Off.
    /// 1 - On.
    int stabilisationMode{0};
    /// ISO sensetivity. Value depends on particular camera controller.
    int isoSensetivity{0};
    /// Scene mode. Value depends on particular camera controller.
    int sceneMode{0};
    /// FPS.
    float fps{0.0f};
    /// Brightness mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    int brightnessMode{1};
    /// Brightness. Value 0-100%.
    int brightness{0};
    /// Contrast. Value 1-100%.
    int contrast{0};
    /// AGC mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    int gainMode{1};
    /// Gain. Value 1-100%.
    int gain{0};
    /// Sharpening mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    int sharpeningMode{0};
    /// Sharpening. Value 1-100%.
    int sharpening{0};
    /// Palette. Value depends on particular camera controller.
    /// Default values for thermal cameras:
    /// 0 - White hot.
    /// 1 - Black hot.
    int palette{0};
    /// Analog gain control mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    int agcMode{1};
    /// Shutter mode.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto.
    int shutterMode{1};
    /// Shutter position. 0 (full close) - 65535 (full open).
    int shutterPos{0};
    /// Shutter speed. Value: 0% - 100%.
    int shutterSpeed{0};
    /// Digital zoom mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    int digitalZoomMode{0};
    /// Digital zoom. Value x1.0 to x20.0.
    float digitalZoom{1.0f};
    /// Exposure compensation mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    int exposureCompensationMode{0};
    /// Exposure compensation position. Value depends on
    /// particular camera controller.
    int exposureCompensationPosition{0};
    /// Defog mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    int defogMode{0};
    /// Dehaze mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - On.
    int dehazeMode{0};
    /// Noise reduction mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - 2D.
    /// 3 - 3D.
    int noiseReductionMode{0};
    /// Black and white filter mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    int blackAndWhiteFilterMode{0};
    /// Filter mode. Value depends on particular camera controller.
    int filterMode{0};
    /// NUC mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    int nucMode{0};
    /// Auto NUC interval. Value in milliseconds from 0 (Off) to 100000.
    int autoNucIntervalMsec{0};
    /// Image flip.
    /// Default values:
    /// 0 - Off,
    /// 1 - Horizontal,
    /// 2 - Vertical,
    /// 3 - Horizontal and vertical.
    int imageFlip{0};
    /// DDE mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    int ddeMode{0};
    /// DDE level. Value depends on particular camera controller.
    int ddeLevel{0};
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
    /// ALC gate. Value depends on particular camera controller.
    int alcGate{0};
    /// Sensor sensitivity. Value depends on particular camera controller.
    float sensitivity{0};
    /// Changing mode (day / night). Value depends on particular camera controller.
    int changingMode{0};
    /// Changing level (day / night). Value depends on particular camera controller.
    float changingLevel{0.0f};
    /// Chroma level. Values: 0% - 100%.
    int chromeLevel{0};
    /// Details, enhancement. Values: 0% - 100%.
    int detail{0};
    /// Camera settings profile. Value depends on particular camera controller.
    int profile{0};
    /// Connection status (read only). Shows if we have respons from camera. Value:
    /// 0 - not connected, 1 - connected.
    bool isConnected{false};
    /// Open status (read only): 1 - camera control port open, 0 - not open.
    bool isOpen{false};
    /// Camera type. Value depends on implementation.
    int type{0};
    /// Camera custom param 1. Value depends on implementation.
    float custom1{0.0f};
    /// Camera custom param 2. Value depends on implementation.
    float custom2{0.0f};
    /// Camera custom param 3. Value depends on implementation.
    float custom3{0.0f};


    JSON_READABLE(CameraParams,
                  initString,
                  width,
                  height,
                  displayMode,
                  videoOutput,
                  logMode,
                  exposureMode,
                  exposureTime,
                  whiteBalanceMode,
                  whiteBalanceArea,
                  wideDynamicRangeMode,
                  stabilisationMode,
                  isoSensetivity,
                  sceneMode,
                  fps,
                  brightnessMode,
                  brightness,
                  contrast,
                  gainMode,
                  gain,
                  sharpeningMode,
                  sharpening,
                  palette,
                  agcMode,
                  shutterMode,
                  shutterPos,
                  shutterSpeed,
                  digitalZoomMode,
                  digitalZoom,
                  exposureCompensationMode,
                  exposureCompensationPosition,
                  defogMode,
                  dehazeMode,
                  noiseReductionMode,
                  blackAndWhiteFilterMode,
                  filterMode,
                  nucMode,
                  autoNucIntervalMsec,
                  imageFlip,
                  ddeMode,
                  ddeLevel,
                  roiX0,
                  roiY0,
                  roiX1,
                  roiY1,
                  alcGate,
                  sensitivity,
                  changingMode,
                  changingLevel,
                  chromeLevel,
                  detail,
                  profile,
                  type,
                  custom1,
                  custom2,
                  custom3)

    /**
     * @brief operator =
     * @param src Source object.
     * @return CameraParams obect.
     */
    CameraParams& operator= (const CameraParams& src);

    /**
     * @brief Encode params. The method doesn't encode initString.
     * @param data Pointer to data buffer.
     * @param size Size of data.
     */
    void encode(uint8_t* data, int& size);

    /**
     * @brief Decode params. The method doesn't decode initString.
     * @param data Pointer to data.
     * @return TRUE is params decoded or FALSE if not.
     */
    bool decode(uint8_t* data);
};



/// Camera controller commands enum.
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
    /// Freeze, Argument: time msec.
    FREEZE,
    /// Disable freeze.
    DEFREEZE
};



/// Camera controller params.
enum class CameraParam
{
    /// Video frame width. Value from 0 to 16384.
    WIDTH = 1,
    /// Video frame height Value from 0 to 16384.
    HEIGHT,
    /// Display menu mode. Values: 0 - Off. 1 - On.
    DISPLAY_MODE,
    /// Video output type. Value depends on particular camera controller.
    VIDEO_OUTPUT,
    /// Logging mode.
    /// Default values:
    /// 0 - Disable.
    /// 1 - Only file.
    /// 2 - Only terminal.
    /// 3 - File and terminal.
    LOG_MODE,
    /// Exposure mode. Value depends on particular camera controller.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto (default),
    /// 2 - Shutter priority.
    /// 3 - Aperture priority.
    EXPOSURE_MODE,
    /// Exposure time of the camera sensor. The exposure time is limited by the
    /// frame interval. Camera controller should interpret the values as 100 µs
    /// units, where the value 1 stands for 1/10000th of a second, 10000 for 1
    /// second and 100000 for 10 seconds.
    EXPOSURE_TIME,
    /// White balance mode.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto
    WHITE_BALANCE_MODE,
    /// White balance area.
    WHITE_BALANCE_AREA,
    /// Wide dynamic range mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - On.
    WIDE_DINAMIC_RANGE_MODE,
    /// Image stabilization mode.
    /// Default value:
    /// 0 - Off.
    /// 1 - On.
    STABILIZATION_MODE,
    /// ISO sensetivity. Value depends on particular camera controller.
    ISO_SENSITIVITY,
    /// Scene mode. Value depends on particular camera controller.
    SCENE_MODE,
    /// FPS.
    FPS,
    /// Brightness mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    BRIGHTNESS_MODE,
    /// Brightness. Value 0-100%.
    BRIGHTNESS,
    /// Contrast. Value 1-100%.
    CONTRAST,
    /// AGC mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    GAIN_MODE,
    /// Gain. Value 1-100%.
    GAIN,
    /// Sharpening mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    SHARPENING_MODE,
    /// Sharpening. Value 1-100%.
    SHARPENING,
    /// Palette. Value depends on particular camera controller.
    /// Default values for thermal cameras:
    /// 0 - White hot.
    /// 1 - Black hot.
    PALETTE,
    /// Analog gain control mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    AGC_MODE,
    /// Shutter mode.
    /// Default values:
    /// 0 - Manual,
    /// 1 - Auto.
    SHUTTER_MODE,
    /// Shutter position. 0 (full close) - 65535 (full open).
    SHUTTER_POSITION,
    /// Shutter speed. Value: 0% - 100%.
    SHUTTER_SPEED,
    /// Digital zoom mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    DIGITAL_ZOOM_MODE,
    /// Digital zoom. Value x1.0 to x20.0.
    DIGITAL_ZOOM,
    /// Exposure compensation mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    EXPOSURE_COMPENSATION_MODE,
    /// Exposure compensation position. Value depends on
    /// particular camera controller.
    EXPOSURE_COMPENSATION_POSITION,
    /// Defog mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    DEFOG_MODE,
    /// Dehaze mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - On.
    DEHAZE_MODE,
    /// Noise reduction mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - 2D.
    /// 3 - 3D.
    NOISE_REDUCTION_MODE,
    /// Black and white filter mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    BLACK_WHITE_FILTER_MODE,
    /// Filter mode. Value depends on particular camera controller.
    FILTER_MODE,
    /// NUC mode.
    /// Default values:
    /// 0 - Manual.
    /// 1 - Auto.
    NUC_MODE,
    /// Auto NUC interval. Value in milliseconds from 0 (Off) to 100000.
    AUTO_NUC_INTERVAL_MSEC,
    /// Image flip.
    /// Default values:
    /// 0 - Off,
    /// 1 - Horizontal,
    /// 2 - Vertical,
    /// 3 - Horizontal and vertical.
    IMAGE_FLIP,
    /// DDE mode.
    /// Default values:
    /// 0 - Off.
    /// 1 - On.
    DDE_MODE,
    /// DDE level. Value depends on particular camera controller.
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
    /// ALC gate. Value depends on particular camera controller.
    ALC_GATE,
    /// Sensor sensitivity. Value depends on particular camera controller.
    SENSETIVITY,
    /// Changing mode (day / night). Value depends on particular camera controller.
    CHANGING_MODE,
    /// Changing level (day / night). Value depends on particular camera controller.
    CHANGING_LEVEL,
    /// Chroma level. Values: 0% - 100%.
    CHROMA_LEVEL,
    /// Details, enhancement. Values: 0% - 100%.
    DETAIL,
    /// Camera settings profile. Value depends on particular camera controller.
    PROFILE,
    /// Connection status (read only). Shows if we have respons from camera. Value:
    /// 0 - not connected, 1 - connected.
    IS_CONNECTED,
    /// Open status (read only): 1 - camera control port open, 0 - not open.
    IS_OPEN,
    /// Lens type. Value depends on implementation.
    TYPE,
    /// Camera custom param 1. Value depends on implementation.
    CUSTOM_1,
    /// Camera custom param 2. Value depends on implementation.
    CUSTOM_2,
    /// Camera custom param 3. Value depends on implementation.
    CUSTOM_3
};



/**
 * @brief Camera controller interface class.
 */
class Camera
{
public:

    /**
     * @brief Get Camera class version.
     * @return String of current class version.
     */
    static std::string getVersion();

    /**
     * @brief Open camera controller.
     * @param initString Init string. Format depends on camera controller.
     * @return TRUE if the camera controller is init or FALSE.
     */
    virtual bool openCamera(std::string initString) = 0;

    /**
     * @brief Init camera controller by structure. Can be used instead
     * openCamera(...) method.
     * @param initString Init string. Format depends on camera controller.
     * @return TRUE if the camera controller init or FALSE if not.
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
     * @brief Get camera open status.
     * @return TRUE if the camera is open or FALSE.
     */
    virtual bool isCameraConnected() = 0;

    /**
     * @brief Set the camers controller param.
     * @param id Param ID.
     * @param value Param value.
     * @return TRUE if the property set or FALSE.
     */
    virtual bool setParam(CameraParam id, float value) = 0;

    /**
     * @brief Get the camera controller param.
     * @param id Param ID.
     * @return int Param value or -1 of the param not exists.
     */
    virtual float getParam(CameraParam id) = 0;

    /**
     * @brief Get the camera controller params.
     * @param id Param ID.
     * @return Lens params structure.
     */
    virtual CameraParams getParams() = 0;

    /**
     * @brief Execute camera controller command.
     * @param id Command ID.
     * @return TRUE if the command executed or FALSE.
     */
    virtual bool executeCommand(CameraCommand id) = 0;

    /**
     * @brief Encode set param command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Camera parameter id.
     * @param value Camera parameter value.
     */
    static void encodeSetParamCommand(
            uint8_t* data, int& size, CameraParam id, float value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Camera command ID.
     */
    static void encodeCommand(
            uint8_t* data, int& size, CameraCommand id);

    /**
     * @brief Decode command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @param paramId Output command ID.
     * @param commandId Output command ID.
     * @param value Param or command value.
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             CameraParam& paramId,
                             CameraCommand& commandId,
                             float& value);
};
}
}
