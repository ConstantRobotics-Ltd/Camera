



![logo](_static/camera_logo.png)

# **Camera interface C++ library**

**v1.0.0**

------

# Table of contents

- [Overview](#Overview)
- [Versions](#Versions)
- [Lens interface class description](#Lens-interface-class-description)
  - [Class declaration](#Class-declaration)
  - [getVersion method](#getVersion-method)
  - [init method](#init-method)
  - [close method](#close-method)
  - [isOpen method](#isOpen-method)
  - [setParam method](#setParam-method)
  - [getParam method](#getParam-method)
  - [executeCommand method](#executeCommand-method)
  - [addVideoFrame method](#addVideoFrame-method)
- [Data structures](#Data-structures)
  - [LensCommand enum](#LensCommand-enum)
  - [LensParam enum](#LensParam-enum)

# Overview

**Lens** C++ library provides standard interface as well defines data structures and rules for different lens controllers. **Lens** interface class doesn't do anything, just provides interface. Different lens controller classes inherit form **Lens** C++ class to provide standard control interface. **Lens.h** file contains list of data structures (**LensCommand** enum and **LensParam** enum) and **Lens** class declaration. **Lens** enum contains IDs of commands supported by **Lens** class. **LensParam** enum contains IDs of params supported by **Lens** class. All lens controller should include params and commands listed in **Lens.h** file.

# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | 21.10.2022   | First version                                                |
| 2.0.0   | 17.03.2023   | - Subrepository LensControllerDataStrctures excluded.<br />- Data structures moved to Lens.h file.<br />- New parameters IDs added.<br />- Description updated. |

# Lens interface class description

## Class declaration

**Lens** interface class declared in **Lens.h** file. Class declaration:

```cpp
namespace cr
{
namespace lens
{
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
```

## getVersion method

**getVersion()** method return string of current version **Lens** class. Particular lens controller can have it's own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **Lens** class instance:

```cpp
std::cout << "Lens controller version: " << Lens::getVersion() << std::endl;
```

## init method

**init(...)** method designed to initialize lens controller. Method declaration:

```cpp
virtual bool init(std::string initString) = 0;
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| initString | Initialization string. Particular lens controller can have unique format. It is recommended to use ';' symbol to divide part of initialization string. Example of lens controller initialization which user serial port: "/dev/ttyUSB0;9600;100" ("/dev/ttyUSB0" - serial port name, "9600" - baudrate, "100" - serial port read timeout). |

**Returns:** TRUE if the lens controller initialized or FALSE if not.

## close method

**close()** method designed to close connection to lens. Method declaration:

```cpp
virtual void close() = 0;
```

## isOpen method

**isOpen()** method designed to obtain lens connection status. Method declaration:

```cpp
virtual bool isOpen() = 0;
```

**Returns:** TRUE is the lens connected or FALSE if not.

## setParam method

**setParam(...)** method designed to set new lens controller parameters value. Method declaration:

```cpp
virtual bool setParam(LensParam id, int value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Lens controller parameter ID according to LensParam enum (see description of [LensParam](#LensParam-enum) enum). |
| value     | Lens controller parameter value. Value depends on parameter ID (see description of [LensParam](#LensParam-enum) enum). |

**Returns:** TRUE is the parameter was set or FALSE if not.

## getParam method

**getParam(...)** method designed to obtain lens controller parameter value. Method declaration:

```cpp
virtual int getParam(LensParam id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Lens controller parameter ID according to LensParam enum (see description of [LensParam](#LensParam-enum) enum). |

**Returns:** parameter value or -1 of the parameters doesn't exist in particular lens controller.

## executeCommand method

**executeCommand(...)** method designed to execute lens controller command. Method declaration:

```cpp
virtual bool executeCommand(LensCommand id, int arg = 0) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Lens controller command ID according to LensCommand enum (see description of [LensCommand](#LensCommand-enum) enum). |
| arg       | Lens controller command argument. Value depends on command ID (see description of [LensCommand](#LensCommand-enum) enum). |

**Returns:** TRUE is the command was executed or FALSE if not.

## addVideoFrame method

**addVideoFrame(...)** method designed to copy video frame data to lens controller to perform autofocus algorithm. Particular lens controller can support autofocus algorithms. To perform autofocus lens controller calculates focus factor in autofocus ROI (focus factor can be obtained with methos [getParam(...)](#getParam(...) method) and parameters ID **FOCUS_FACTOR**). To calculate focus factor lens controller needs video frame. If particular lens controller supports autofocus algorithms the method **addVideoFrame(...)** should be called for each captured video frame. Method declaration:

```cpp
virtual bool addVideoFrame(uint8_t* frame, int width, int height) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| frame     | Pinter to video frame data. Video frame data must have Mono8 format (GRAYSCALE, 1 byte per pixel). |
| width     | Video frame width in pixels.                                 |
| height    | Video frame height in pixels.                                |

**Returns:** TRUE is the video frame accepted or FALSE if not.

# Data structures

Lens.h file defines IDs for parameters (**LensParam** enum) and IDs for commands (**LensCommand** enum). **LensParam** enum and **LensCommand** enum declared in **Lens.h** file.

## LensCommand enum

Enum declaration:

```cpp
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
```

**Table 2** - Lens commands description. Some commands maybe unsupported by particular lens controller.

| Command      | Description                                                  |
| ------------ | ------------------------------------------------------------ |
| ZOOM_TELE    | Move zoom tele (in). Command doesn't have arguments.         |
| ZOOM_WIDE    | Move zoom wide (out). Command doesn't have arguments.        |
| ZOOM_TO_POS  | Move zoom to position. Lens controller should have zoom range from 0 (full wide) to 65535 (full tele) regardless of the hardware value of the zoom position. If the minimum and maximum zoom position limits are set by the user in the lens parameters, the range of the hardware zoom position must be scaled to the user space 0-65535 range. Command argument: zoom position 0-65535. |
| ZOOM_STOP    | Stop zoom moving including stop zoom to position command.    |
| FOCUS_FAR    | Move focus far. Command doesn't have arguments.              |
| FOCUS_NEAR   | Move focus near. Command doesn't have arguments.             |
| FOCUS_TO_POS | Move focus to position. Lens controller should have focus range from 0 (full near) to 65535 (full far) regardless of the hardware value of the focus position. If the minimum and maximum focus position limits are set by the user in the lens parameters, the range of the hardware focus position must be scaled to the 0-65535 user space range. Command argument: focus position 0-65535. |
| FOCUS_STOP   | Stop focus moving including stop focus to position command.  |
| IRIS_OPEN    | Move iris open. Command doesn't have arguments.              |
| IRIS_CLOSE   | Move iris close. Command doesn't have arguments.             |
| IRIS_TO_POS  | Move iris to position. Lens controller should have iris range from 0 (full close) to 65535 (full far) regardless of the hardware value of the iris position. If the minimum and maximum iris position limits are set by the user in the lens parameters, the range of the hardware iris position must be scaled to the 0-65535 user space range. Command argument: iris position 0-65535. |
| IRIS_STOP    | Stop iris moving including stop iris to position command. Command doesn't have arguments. |
| AF_START     | Start autofocus.  Command doesn't have arguments.            |
| AF_STOP      | Stop autofocus.  Command doesn't have arguments.             |
| RESTART      | Restart lens controller.                                     |

## LensParam enum

Enum declaration:

```cpp
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
```

**Table 3** - Lens params description. Some params maybe unsupported by particular lens controller.

| Parameter              | Access       | Description                                                  |
| ---------------------- | ------------ | ------------------------------------------------------------ |
| ZOOM_POS               | read / write | Zoom position. Setting a parameter is equivalent to the command ZOOM_TO_POS. Lens controller should have zoom range from 0 (full wide) to 65535 (full tele) regardless of the hardware value of the zoom position. If the minimum and maximum zoom position limits are set by the user in the lens parameters, the range of the hardware zoom position must be scaled to the user space 0-65535 range. Parameter value: zoom position 0-65535. |
| ZOOM_HW_POS            | read / write | Hardware zoom position. Parameter value depends on particular lens controller. |
| FOCUS_POS              | read / write | Focus position. Setting a parameter is equivalent to the command FOCUS_TO_POS. Lens controller should have focus range from 0 (full near) to 65535 (full far) regardless of the hardware value of the focus position. If the minimum and maximum focus position limits are set by the user in the lens parameters, the range of the hardware focus position must be scaled to the user space 0-65535 range. Parameter value: focus position 0-65535. |
| FOCUS_HW_POS           | read / write | Hardware focus position. Parameter value depends on particular lens controller. |
| IRIS_POS               | read / write | Iris position. Setting a parameter is equivalent to the command IRIS_TO_POS. Lens controller should have iris range from 0 (full close) to 65535 (full open) regardless of the hardware value of the iris position. If the minimum and maximum iris position limits are set by the user in the lens parameters, the range of the hardware iris position must be scaled to the user space 0-65535 range. Parameter value: iris position 0-65535. |
| IRIS_HW_POS            | read / write | Hardware iris position. Parameter value depends on particular lens controller. |
| FOCUS_MODE             | read / write | Focus mode. Parameter value depends on particular lens controller. Default values: 0 - Manual focus control, 1 - Auto focus control. |
| FILTER_MODE            | read / write | Filter mode. Parameter value depends on particular lens controller. Default values: 0 - Filter on, 1 - Filter off. |
| AF_ROI_X0              | read / write | Autofocus ROI top-left corner horizontal position in pixels. Autofocus ROI is rectangle. |
| AF_ROI_Y0              | read / write | Autofocus ROI top-left corner vertical position in pixels. Autofocus ROI is rectangle. |
| AF_ROI_X1              | read / write | Autofocus ROI bottom-right corner horizontal position in pixels. Autofocus ROI is rectangle. |
| AF_ROI_Y1              | read / write | Autofocus ROI bottom-right corner vertical position in pixels. Autofocus ROI is rectangle. |
| ZOOM_SPEED             | read / write | Zoom speed. Lens controller should have zoom speed range from 0 to 100% of max hardware zoom speed (parameter ZOOM_HW_MAX_SPEED). If the user sets a new parameter value of the ZOOM_HW_SPEED parameter the parameter ZOOM_SPEED must be updated automatically by lens controller. Formula for calculating speed: ZOOM_SPEED = ( ZOOM_HW_SPEED / ZOOM_HW_MAX_SPEED) * 100. |
| ZOOM_HW_SPEED          | read / write | Zoom hardware speed. Value depends on particular lens controller. The value of the parameters must be <= ZOOM_HW_MAX_SPEED parameter. If the user sets a new parameter value of the ZOOM_SPEED parameter the parameter ZOOM_HW_SPEED must be updated automatically by lens controller. Formula for calculating hardware speed: ZOOM_HW_SPEED = ( ZOOM_SPEED / 100 ) * ZOOM_HW_MAX_SPEED. |
| ZOOM_HW_MAX_SPEED      | read / write | Maximum zoom hardware speed. Value depends on particular lens controller. If user sets new ZOOM_HW_MAX_SPEED value the parameters ZOOM_SPEED and ZOOM_HW_SPEED must be updated by lens controller automatically. If new value of ZOOM_HW_MAX_SPEED parameter will be less than ZOOM_HW_SPEED the parameter ZOOM_HW_SPEED must be reduced automatically. |
| FOCUS_SPEED            | read / write | Focus speed. Lens controller should have focus speed range from 0 to 100% of max hardware focus speed (parameter FOCUS_HW_MAX_SPEED). If the user sets a new parameter value of the FOCUS_HW_SPEED parameter the parameter FOCUS_SPEED must be updated automatically by lens controller. Formula for calculating speed: FOCUS_SPEED = ( FOCUS_HW_SPEED / FOCUS_HW_MAX_SPEED) * 100. |
| FOCUS_HW_SPEED         | read / write | Focus hardware speed. Value depends on particular lens controller. The value of the parameters must be <= FOCUS_HW_MAX_SPEED parameter. If the user sets a new parameter value of the FOCUS_SPEED parameter the parameter FOCUS_HW_SPEED must be updated automatically by lens controller. Formula for calculating hardware speed: FOCUS_HW_SPEED = ( FOCUS_SPEED / 100 ) * FOCUS_HW_MAX_SPEED. |
| FOCUS_HW_MAX_SPEED     | read / write | Maximum focus hardware speed. Value depends on particular lens controller. If user sets new FOCUS_HW_MAX_SPEED value the parameters FOCUS_SPEED and FOCUS_HW_SPEED must be updated by lens controller automatically. If new value of FOCUS_HW_MAX_SPEED parameter will be less than FOCUS_HW_SPEED the parameter FOCUS_HW_SPEED must be reduced automatically. |
| IRIS_SPEED             | read / write | Iris speed. Lens controller should have iris speed range from 0 to 100% of max hardware iris speed (parameter IRIS_HW_MAX_SPEED). If the user sets a new parameter value of the IRIS_HW_SPEED parameter the parameter IRIS_SPEED must be updated automatically by lens controller. Formula for calculating speed: IRIS_SPEED = ( IRIS_HW_SPEED / IRIS_HW_MAX_SPEED) * 100. |
| IRIS_HW_SPEED          | read / write | Iris hardware speed. Value depends on particular lens controller. The value of the parameters must be <= IRIS_HW_MAX_SPEED parameter. If the user sets a new parameter value of the IRIS_SPEED parameter the parameter IRIS_HW_SPEED must be updated automatically by lens controller. Formula for calculating hardware speed: IRIS_HW_SPEED = ( IRIS_SPEED / 100 ) * IRIS_HW_MAX_SPEED. |
| IRIS_HW_MAX_SPEED      | read / write | Maximum iris hardware speed. Value depends on particular lens controller. If user sets new IRIS_HW_MAX_SPEED value the parameters IRIS_SPEED and IRIS_HW_SPEED must be updated by lens controller automatically. If new value of IRIS_HW_MAX_SPEED parameter will be less than IRIS_HW_SPEED the parameter IRIS_HW_SPEED must be reduced automatically. |
| ZOOM_HW_TELE_LIMIT     | read / write | Zoom hardware tele limit. Value depends on particular lens controller. Lens controller should control zoom position. Lens controller should stop zoom moving if hardware zoom position will be our of limits. |
| ZOOM_HW_WIDE_LIMIT     | read / write | Zoom hardware wide limit. Value depends on particular lens controller. Lens controller should control zoom position. Lens controller should stop zoom moving if hardware zoom position will be our of limits. |
| FOCUS_HW_FAR_LIMIT     | read / write | Focus hardware far limit. Value depends on particular lens controller. Lens controller should control focus position. Lens controller should stop focus moving if hardware focus position will be our of limits. |
| FOCUS_HW_NEAR_LIMIT    | read / write | Focus hardware near limit. Value depends on particular lens controller. Lens controller should control focus position. Lens controller should stop focus moving if hardware focus position will be our of limits. |
| IRIS_HW_OPEN_LIMIT     | read / write | Iris hardware open limit. Value depends on particular lens controller. Lens controller should control iris position. Lens controller should stop iris moving if hardware iris position will be our of limits. |
| IRIS_HW_CLOSE_LIMIT    | read / write | Iris hardware close limit. Value depends on particular lens controller. Lens controller should control iris position. Lens controller should stop iris moving if hardware iris position will be our of limits. |
| FOCUS_FACTOR           | read only    | Focus factor if it was calculated. If not the values must be -1. Value depends on particular lens controller. |
| IS_CONNECTED           | read only    | Lens connection status. Value: 0 - not connected. 1 - connected. |
| FOCUS_HW_AF_SPEED      | read / write | Focus hardware speed in autofocus mode. Value depends on particular lens controller. |
| FOCUS_FACTOR_THRESHOLD | read / write | Threshold for changes of focus factor to start refocus. Value: threshold %: 0 - no check, 100 - changing x2. |
| REFOCUS_TIMEOUT_SEC    | read / write | Timeout for automatic refocus in seconds. Value: 0 - no automatic refocus, 100000 - maximum value. |
| AF_IS_ACTIVE           | read only    | Flag about active autofocus algorithm. Value: 0 - autofocus not working, 1 - working. |
| IRIS_MODE              | read / write | Iris mode. Value depends on particular lens controller. Default values: 0 - manual iris control, 1 - auto iris control. |
| DEBUG_INFO_MODE        | read / write | Flag to allow printing debug information in terminal. Value: 0 - no debug info printing, 1 - printing debug info. |
| AUTO_AF_ROI_WIDTH      | read / write | ROI width (pixels) for autofocus algorithm when lens controller detects ROI position automatically. Value: from 8 to (video frame width - AUTO_AF_ROI_BORDER * 2). |
| AUTO_AF_ROI_HEIGHT     | read / write | ROI height (pixels) for autofocus algorithm when lens controller detects ROI position automatically. Value: from 8 to (video frame width - AUTO_AF_ROI_BORDER * 2). |
| AUTO_AF_ROI_BORDER     | read / write | Video frame border size (along vertical and horizontal axes). Value: border size from 0 to video frame min(video frame width/height) / 2. |
| AF_ROI_MODE            | read / write | AF ROI mode (write/read). Value: 0 - Manual position, 1 - Auto position. |
| EXTENDER_MODE          | read / write | Lens extender mode. Value depends on particular lens controller. Default values: 0 - no extender, 1 - x2 extender. |
| STABILIZER_MODE        | read / write | Lens stabilization mode. Value depends on particular lens controller. Default values: 0 - no stabilization, 1 - stabilization. |
| AF_RANGE               | read / write | Autofocus range. Value depends on particular lens controller. |
| ZOOM_FULL_WIDE_FOV_GED | read / write | Lens field of view (degree) when zoom full wide. Depends on combination lens + camera (sensor size) the field of view value can be different from technical characteristics of lens. The lens should calculate FOV_DEG automatically when zoom changes according to values of ZOOM_FULL_WIDE_FOV_GED and ZOOM_FULL_TELE_FOV_DEG by linear approximation. |
| ZOOM_FULL_TELE_FOV_DEG | read / write | Lens field of view (degree) when zoom full tele. Depends on combination lens + camera (sensor size) the field of view value can be different from technical characteristics of lens. The lens should calculate FOV_DEG automatically when zoom changes according to values of ZOOM_FULL_WIDE_FOV_GED and ZOOM_FULL_TELE_FOV_DEG by linear approximation. |
| FOV_DEG                |              | Current field of view (degree) calculated according to values of ZOOM_FULL_WIDE_FOV_GED and ZOOM_FULL_TELE_FOV_DEG and ZOOM_HW_POS  by linear approximation. Particular lens controller can consider also FOCUS_HW_POS for more precise calculation. |



