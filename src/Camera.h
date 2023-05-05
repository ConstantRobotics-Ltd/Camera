#pragma once
#include <string>
#include <cstdint>



namespace cr
{
namespace camera
{

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
    /// White dynamic range mode.
    /// Default values:
    /// 0 - Off,
    /// 1 - On.
    WHITE_DINAMIC_RANGE_MODE,
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
    AUTO_NUC_INTERVAL,
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
    PROFILE
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
     * @brief Init camera controller.
     * @param initString Init string. Format depends on camera controller.
     * @return TRUE if the camera controller is init or FALSE.
     */
    virtual bool openCamera(std::string initString) = 0;

    /**
     * @brief Close camera connection.
     */
    virtual void closeCamera() = 0;

    /**
     * @brief Get camera connection status.
     * @return TRUE if the camera is open or FALSE.
     */
    virtual bool isCameraOpen() = 0;

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
     * @brief Execute camera controller command.
     * @param id Command ID.
     * @param arg Command argument.
     * @return TRUE if the command executed or FALSE.
     */
    virtual bool executeCommand(CameraCommand id, float arg = 0.0f) = 0;
};
}
}
