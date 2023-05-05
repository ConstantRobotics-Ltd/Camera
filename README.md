



![logo](_static/camera_logo.png)

# **Camera interface C++ library**

**v1.0.0**

------

# Table of contents

- [Overview](#Overview)
- [Versions](#Versions)
- [Camera interface class description](#Camera-interface-class-description)
  - [Class declaration](#Class-declaration)
  - [getVersion method](#getVersion-method)
  - [openCamera method](#openCamera-method)
  - [closeCamera method](#closeCamera-method)
  - [isCameraOpen-method](#isCameraOpen-method)
  - [setParam method](#setParam-method)
  - [getParam method](#getParam-method)
  - [executeCommand method](#executeCommand-method)
- [Data structures](#Data-structures)
  - [CameraCommand enum](#CameraCommand-enum)
  - [CameraParam enum](#CameraParam-enum)

# Overview

**Camera** C++ library provides standard interface as well defines data structures and rules for different camera controllers. **Camera** interface class doesn't do anything, just provides interface. Different camera controller classes inherit form **Camera** C++ class to provide standard control interface. **Camera.h** file contains list of data structures (**CameraCommand** enum and **CameraParam** enum) and **Camera** class declaration. **CameraCommand** enum contains IDs of commands supported by **Camera** class. **CameraParam** enum contains IDs of params supported by **Camera** class. All camera controller should include params and commands listed in **Camera.h** file.

# Versions

**Table 1** - Library versions.

| Version | Release date | What's new    |
| ------- | ------------ | ------------- |
| 1.0.0   | 05.05.2025   | First version |

# Camera interface class description

## Class declaration

**Camera** interface class declared in **Camera.h** file. Class declaration:

```cpp
namespace cr
{
namespace camera
{
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
```

## getVersion method

**getVersion()** method return string of current version **Camera** class. Particular camera controller can have it's own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **Camera** class instance:

```cpp
std::cout << "Camera class version: " << Camera::getVersion() << std::endl;
```

## openCamera method

**openCamera(...)** method designed to initialize camera controller. Method declaration:

```cpp
virtual bool openCamera(std::string initString) = 0;
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| initString | Initialization string. Particular camera controller can have unique format. It is recommended to use ';' symbol to divide part of initialization string. Example of camera controller initialization which user serial port: "/dev/ttyUSB0;9600;100" ("/dev/ttyUSB0" - serial port name, "9600" - baudrate, "100" - serial port read timeout). |

**Returns:** TRUE if the camera controller initialized or FALSE if not.

## closeCamera method

**closeCamera()** method designed to close connection to camera. Method declaration:

```cpp
virtual void closeCamera() = 0;
```

## isCameraOpen method

**isCameraOpen()** method designed to obtain camera connection status. Method declaration:

```cpp
virtual bool isCameraOpen() = 0;
```

**Returns:** TRUE is the camera connected or FALSE if not.

## setParam method

**setParam(...)** method designed to set new camera controller parameters value. Method declaration:

```cpp
virtual bool setParam(CameraParam id, float value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera controller parameter ID according to CameraParam enum (see description of [CameraParam](#CameraParam-enum) enum). |
| value     | Camera controller parameter value. Value depends on parameter ID (see description of [CameraParam](#CameraParam-enum) enum). |

**Returns:** TRUE is the parameter was set or FALSE if not.

## getParam method

**getParam(...)** method designed to obtain camera controller parameter value. Method declaration:

```cpp
virtual float getParam(CameraParam id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera controller parameter ID according to CameraParam enum (see description of [CameraParam](#CameraParam-enum) enum). |

**Returns:** parameter value or -1 of the parameters doesn't exist in particular camera controller.

## executeCommand method

**executeCommand(...)** method designed to execute camera controller command. Method declaration:

```cpp
virtual bool executeCommand(CameraCommand id, float arg = 0.0f) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera controller command ID according to CameraCommand enum (see description of [CameraCommand](#CameraCommand-enum) enum). |
| arg       | Camera controller command argument. Value depends on command ID (see description of [CameraCommand](#CameraCommand-enum) enum). |

**Returns:** TRUE is the command was executed or FALSE if not.

# Data structures

**Camera.h** file defines IDs for parameters (**CameraParam** enum) and IDs for commands (**CameraCommand** enum). **CameraParam** enum and **CameraCommand** enum declared in **Camera.h** file.

## CameraCommand enum

Enum declaration:

```cpp
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
```

**Table 2** - Camera commands description. Some commands maybe unsupported by particular camera controller.

| Command      | Description                   |
| ------------ | ----------------------------- |
| RESTART      | Restart camera controller.    |
| NUC          | Do NUC. For thermal cameras.  |
| APPLY_PARAMS | Apply settings.               |
| SAVE_PARAMS  | Save params in camera memory. |
| MENU_ON      | Menu on.                      |
| MENU_OFF     | Menu off.                     |
| MENU_SET     | Menu set.                     |
| MENU_UP      | Menu move up.                 |
| MENU_DOWN    | Menu move down.               |
| MENU_LEFT    | Menu move left.               |
| MENU_RIGHT   | Menu move right.              |
| FREEZE       | Freeze image.                 |
| DEFREEZE     | Defreeze image.               |

## CameraParam enum

Enum declaration:

```cpp
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
```

**Table 3** - Camera params description. Some params maybe unsupported by particular camera controller.

| Parameter                      | Access       | Description                                                  |
| ------------------------------ | ------------ | ------------------------------------------------------------ |
| WIDTH                          | read / write | Video frame width. Value from 0 to 16384.                    |
| HEIGHT                         | read / write | Video frame height Value from 0 to 16384.                    |
| DISPLAY_MODE                   | read / write | Display menu mode. Values: 0 - Off. 1 - On.                  |
| VIDEO_OUTPUT                   | read / write | Video output type. Value depends on particular camera controller. |
| LOG_MODE                       | read / write | /Logging mode. Default values:<br />0 - Disable.<br />1 - Only file.<br />2 - Only terminal.<br />3 - File and terminal. |
| EXPOSURE_MODE                  | read / write | Exposure mode. Value depends on particular camera controller. Default values:<br />0 - Manual,<br />1 - Auto (default),<br />2 - Shutter priority.<br />3 - Aperture priority. |
| EXPOSURE_TIME                  | read / write | Exposure time of the camera sensor. The exposure time is limited by the frame interval. Camera controller should interpret the values as 100 µs units, where the value 1 stands for 1/10000th of a second, 10000 for 1 second and 100000 for 10 seconds. |
| WHITE_BALANCE_MODE             | read / write | White balance mode. Default values:<br />0 - Manual,<br />1 - Auto. |
| WHITE_BALANCE_AREA             | read / write | White balance area.                                          |
| WHITE_DINAMIC_RANGE_MODE       | read / write | White dynamic range mode. Default values:<br />0 - Off.<br />1 - On. |
| STABILIZATION_MODE             | read / write | Image stabilization mode. Default value:<br />0 - Off.<br />1 - On. |
| ISO_SENSITIVITY                | read / write | ISO sensitivity. Value depends on particular camera controller. |
| SCENE_MODE                     | read / write | Scene mode. Value depends on particular camera controller.   |
| FPS                            | read / write | FPS.                                                         |
| BRIGHTNESS_MODE                | read / write | Brightness mode. Default values:<br />0 - Manual.<br />1 - Auto. |
| BRIGHTNESS                     | read / write | Brightness. Value 0-100%.                                    |
| CONTRAST                       | read / write | Contrast. Value 1-100%.                                      |
| GAIN_MODE                      | read / write | Gain mode. Default values:<br />0 - Manual.<br />1 - Auto.   |
| GAIN                           | read / write | Gain. Value 1-100%.                                          |
| SHARPENING_MODE                | read / write | Sharpening mode. Default values:<br />0 - Manual.<br />1 - Auto. |
| SHARPENING                     | read / write | Sharpening. Value 1-100%.                                    |
| PALETTE                        | read / write | Palette. Value depends on particular camera controller.    Default values for thermal cameras:<br />0 - White hot.<br />1 - Black hot. |
| AGC_MODE                       | read / write | Analog gain control mode. Default values:<br />0 - Manual.<br />1 - Auto. |
| SHUTTER_MODE                   | read / write | Shutter mode. Default values:<br />0 - Manual.<br />1 - Auto. |
| SHUTTER_POSITION               | read / write | Shutter position. 0 (full close) - 65535 (full open).        |
| SHUTTER_SPEED                  | read / write | Shutter speed. Value: 0% - 100%.                             |
| DIGITAL_ZOOM_MODE              | read / write | Digital zoom mode. Default values:<br />0 - Off.<br />1 - On. |
| DIGITAL_ZOOM                   | read only    | Digital zoom. Value x1.0 to x20.0.                           |
| EXPOSURE_COMPENSATION_MODE     | read only    | Exposure compensation mode. Default values:<br />0 - Off.<br />1 - On. |
| EXPOSURE_COMPENSATION_POSITION | read / write | Exposure compensation position. Value depends on particular camera controller. |
| DEFOG_MODE                     | read / write | Defog mode. Default values:<br />0 - Off.<br />1 - On.       |
| DEHAZE_MODE                    |              | Dehaze mode. Default values:<br />0 - Off.<br />1 - On.      |
| NOISE_REDUCTION_MODE           | read / write | Noise reduction mode. Default values:<br />0 - Off.<br />1 - 2D.<br />3 - 3D. |
| BLACK_WHITE_FILTER_MODE        | read only    | Black and white filter mode. Default values:<br />0 - Off.<br />1 - On. |
| FILTER_MODE                    | read / write | Filter mode. Value depends on particular camera controller.  |
| NUC_MODE                       | read / write | NUC mode for thermal cameras. Default values:<br />0 - Manual.<br />1 - Auto. |
| AUTO_NUC_INTERVAL              | read / write | Auto NUC interval for thermal cameras. Value in milliseconds from 0 (Off) to 100000. |
| IMAGE_FLIP                     | read / write | Image flip mode. Default values:<br />0 - Off.<br />1 - Horizontal.<br />2 - Vertical.<br />3 - Horizontal and vertical. |
| DDE_MODE                       | read / write | DDE mode. Default values:<br />0 - Off.<br />1 - On.         |
| DDE_LEVEL                      | read / write | DDE level. Value depends on particular camera controller.    |
| ROI_X0                         | read / write | ROI top-left horizontal position, pixels.                    |
| ROI_Y0                         | read / write | ROI top-left vertical position, pixels.                      |
| ROI_X1                         | read / write | ROI bottom-right horizontal position, pixels.                |
| ROI_Y1                         | read / write | ROI bottom-right vertical position, pixels.                  |
| TEMPERATURE                    | read only    | Camera temperature, degree.                                  |
| ALC_GATE                       | read / write | ALC gate. Value depends on particular camera controller.     |
| SENSETIVITY                    | read / write | Sensor sensitivity. Value depends on particular camera controller. |
| CHANGING_MODE                  | read / write | Changing mode (day / night). Value depends on particular camera controller. |
| CHANGING_LEVEL                 | read / write | Changing level (day / night). Value depends on particular camera controller. |
| CHROMA_LEVEL                   | read / write | Chroma level. Values: 0% - 100%.                             |
| DETAIL                         | read / write | Details, enhancement. Values: 0% - 100%.                     |
| PROFILE                        | read / write | Camera settings profile. Value depends on particular camera controller. |



