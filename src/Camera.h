#pragma once
#include <string>
#include <cstdint>



namespace cr
{
namespace lens
{

/// Lens commands enum.
enum class LensCommand
{
    /// Zoom tele. No arguments.
    ZOOM_TELE = 1,
    /// Zoom wide. No arguments.
    ZOOM_WIDE,
    /// Zoom to position. Argument:
    /// zoom position 0(full wide) - 65535(full tele).
    ZOOM_TO_POS,
    /// Stop zoom. No arguments.
    ZOOM_STOP,
    /// Focus far. No arguments.
    FOCUS_FAR,
    /// Focus near. No arguments.
    FOCUS_NEAR,
    /// Focus to position. Argument:
    /// focus position 0(full near) - 65535(full far).
    FOCUS_TO_POS,
    /// Focus stop. No arguments.
    FOCUS_STOP,
    /// Iris open. No arguments.
    IRIS_OPEN,
    /// Iris close. No arguments.
    IRIS_CLOSE,
    /// Iris to position. Argument:
    /// iris position 0(full close) - 65535(full open).
    IRIS_TO_POS,
    /// Iris stop. No arguments.
    IRIS_STOP,
    /// Autofocus start. No arguments.
    AF_START,
    /// Autofocus stop. No arguments.
    AF_STOP,
    /// Restart lens controller. No arguments.
    RESTART
};



/// Lens params.
enum class LensParam
{
    /// Zoom position (write/read). Value:
    /// zoom position 0(full wide) - 65535(full tele).
    ZOOM_POS = 1,
    /// Hardware zoom position (write/read). Argument:
    /// zoom position. Value depends on particular lens controller.
    ZOOM_HW_POS,
    /// Focus position (write/read). Value:
    /// focus position 0(full near) - 65535(full far).
    FOCUS_POS,
    /// Hardware focus position (write/read). Value:
    /// focus position. Value depends on particular lens controller.
    FOCUS_HW_POS,
    /// Iris position (write/read). Value:
    /// iris position 0(full close) - 65535(full open).
    IRIS_POS,
    /// Hardware iris position (write/read). Value:
    /// iris position. Value depends on particular lens controller.
    IRIS_HW_POS,
    /// Focus mode (write/read). Value:
    /// Value depends on particular lens controller.
    FOCUS_MODE,
    /// Filter mode (write/read).  Value:
    /// Value depends on particular lens controller.
    FILTER_MODE,
    /// Auto focus ROI top-left coordinate (write/read). Value:
    /// ROI top-left horizontal coordinate in pixels.
    AF_ROI_X0,
    /// Auto focus ROI top-left coordinate (write/read). Value:
    /// ROI top-left vertical coordinate in pixels.
    AF_ROI_Y0,
    /// Auto focus ROI bottom-right coordinate (write/read). Value:
    /// ROI bottom-right horizontal coordinate in pixels.
    AF_ROI_X1,
    /// Auto focus ROI bottom-right coordinate (write/read). Value:
    /// ROI bottom-right vertical coordinate in pixels.
    AF_ROI_Y1,
    /// Zoom speed (write/read). Value:
    /// zoom speed 0 to 100 %.
    ZOOM_SPEED,
    /// Hardware zoom speed (write/read). Value:
    /// zoom speed. Value depends on particular lens controller.
    ZOOM_HW_SPEED,
    /// Max hardware zoom speed (write/read). Value:
    /// zoom speed. Value depends on particular lens controller.
    ZOOM_HW_MAX_SPEED,
    /// Focus speed (write/read). Value:
    /// focus speed 0 to 100 %.
    FOCUS_SPEED,
    /// Hardware focus speed (write/read). Value:
    /// focus speed. Value depends on particular lens controller.
    FOCUS_HW_SPEED,
    /// Max hardware focus speed (write/read). Argument:
    /// focus speed. Value depends on particular lens controller.
    FOCUS_HW_MAX_SPEED,
    /// Iris speed (write/read). Value:
    /// iris speed 0 to 100 %.
    IRIS_SPEED,
    /// Hardware iris speed (write/read). Value:
    /// iris speed. Value depends on particular lens controller.
    IRIS_HW_SPEED,
    /// Max hardware iris speed (write/read). Value:
    /// iris speed. Value depends on particular lens controller.
    IRIS_HW_MAX_SPEED,
    /// Hardware zoom tele limit (write/read). Value:
    /// hardware zoom position. Value depends on particular lens controller.
    ZOOM_HW_TELE_LIMIT,
    /// Hardware zoom wide limit (write/read). Value:
    /// hardware zoom position. Value depends on particular lens controller.
    ZOOM_HW_WIDE_LIMIT,
    /// Hardware focus far limit (write/read). Value:
    /// hardware focus position. Value depends on particular lens controller.
    FOCUS_HW_FAR_LIMIT,
    /// Hardware focus near limit (write/read). Value:
    /// hardware focus position. Value depends on particular lens controller.
    FOCUS_HW_NEAR_LIMIT,
    /// Hardware iris open limit (write/read). Value:
    /// hardware iris position. Value depends on particular lens controller.
    IRIS_HW_OPEN_LIMIT,
    /// Hardware iris close limit (write/read). Value:
    /// hardware iris position. Value depends on particular lens controller.
    IRIS_HW_CLOSE_LIMIT,
    /// Focus factor value (read only). Value:
    /// Value depends on particular lens controller.
    FOCUS_FACTOR,
    /// Connection status (read only). Value:
    /// 0 - not connected, 1 - connected.
    IS_CONNECTED,
    /// Hardware focus speed in AF mode (write/read). Value:
    /// hardware focus speed. Value depends on particular lens controller.
    FOCUS_HW_AF_SPEED,
    /// Threshold for focus factor to start refocus (write/read). Value:
    /// threshold %: 0 - no check, 100 - changing x2.
    FOCUS_FACTOR_THRESHOLD,
    /// Refocus timeout, sec (write/read). Value:
    /// 0 - no refocus, to 100000 sec.
    REFOCUS_TIMEOUT_SEC,
    /// AF process mode (read only). Value: 0 - not active, 1 - active.
    AF_IS_ACTIVE,
    /// Iris mode. (write/read). Value:
    /// Value depends on particular lens controller.
    IRIS_MODE,
    /// Debug info in terminal mode (write/read). Value: 0 - off, 1 - on.
    DEBUG_INFO_MODE,
    /// Auto ROI width (write/read). Value: 0 to video frame size, pxl.
    AUTO_AF_ROI_WIDTH,
    /// Auto ROI height (write/read). Value: 0 to video frame size, pxl.
    AUTO_AF_ROI_HEIGHT,
    /// Auto ROI frame border in pixels (write/read). Value:
    /// border size from 0 to video frame min(width/height) / 2.
    AUTO_AF_ROI_BORDER,
    /// AF ROI mode (write/read). Value:
    /// 0 - Manual position, 1 - Auto position.
    AF_ROI_MODE,
    /// Optical extender mode (write/read). Value:
    /// Value depends on particular lens controller. Default: 0 -Off, 1 -On.
    EXTENDER_MODE,
    /// Stabilizer mode (write/read). Value:
    /// 0 - Off, 1 - On.
    STABILIZER_MODE,
    /// AF range (write/read). Value:
    /// Value depends on particular lens controller.
    AF_RANGE,
    /// Zoom full wide field of view (write/read). Value: FOV degree.
    ZOOM_FULL_WIDE_FOV_DEG,
    /// Zoom full tele field of view (write/read). Value: FOV degree.
    ZOOM_FULL_TELE_FOV_DEG,
    /// Fiels of view, degree (write/read). Value: FOV degree.
    FOV_DEG
};



/**
 * @brief Lens controller interface class.
 */
class Lens
{
public:

    /**
     * @brief Lens data structure.
     * @return String of current class version.
     */
    static std::string getVersion();

    /**
     * @brief Init lens controller.
     * @param initString Init string. Format depends on lens controller.
     * @return TRUE if the lens controller is init or FALSE.
     */
    virtual bool init(std::string initString) = 0;

    /**
     * @brief Close connection.
     */
    virtual void close() = 0;

    /**
     * @brief Get lens connection status.
     * @return TRUE if the lens is open or FALSE.
     */
    virtual bool isOpen() = 0;

    /**
     * @brief Set the lens controller param.
     * @param id Param ID.
     * @param value Param value.
     * @return TRUE if the property set or FALSE.
     */
    virtual bool setParam(LensParam id, int value) = 0;

    /**
     * @brief Get the lens controller param.
     * @param id Param ID.
     * @return int Param value or -1 of the param not exists.
     */
    virtual int getParam(LensParam id) = 0;

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @param arg Command argument.
     * @return TRUE if the command executed or FALSE.
     */
    virtual bool executeCommand(LensCommand id, int arg = 0) = 0;

    /**
     * @brief Add video frame to calculate focus factor.
     * @param frame Pointer to frame data in Mono8 format.
     * @param width Frame width.
     * @param height Frame height.
     * @return TRUE If the video frame was added or FALSE.
     */
    virtual bool addVideoFrame(uint8_t* frame, int width, int height) = 0;
};
}
}
