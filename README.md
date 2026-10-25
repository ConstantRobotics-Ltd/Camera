![camera_web_logo](./static/camera_web_logo.png)



# **Camera interface C++ library**

**v2.5.5**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [Camera interface class description](#camera-interface-class-description)
  - [Camera class declaration](#camera-class-declaration)
  - [getVersion method](#getversion-method)
  - [openCamera method](#opencamera-method)
  - [initCamera method](#initcamera-method)
  - [closeCamera method](#closecamera-method)
  - [isCameraOpen method](#iscameraopen-method)
  - [isCameraConnected method](#iscameraconnected-method)
  - [setParam method](#setparam-method)
  - [getParam method](#getparam-method)
  - [getParams method](#getparams-method)
  - [executeCommand method](#executecommand-method)
  - [encodeSetParamCommand method](#encodesetparamcommand-method)
  - [encodeCommand method](#encodecommand-method)
  - [decodeCommand method](#decodecommand-method)
  - [decodeAndExecuteCommand method](#decodeandexecutecommand-method)
- [Data structures](#data-structures)
  - [CameraCommand enum](#cameracommand-enum)
  - [CameraParam enum](#cameraparam-enum)
- [CameraParams class description](#cameraparams-class-description)
  - [CameraParams class declaration](#cameraparams-class-declaration)
  - [Serialize camera params](#serialize-camera-params)
  - [Deserialize camera params](#deserialize-camera-params)
  - [Read params from JSON file and write to JSON file](#read-params-from-json-file-and-write-to-json-file)
- [Build and connect to your project](#build-and-connect-to-your-project)
  - [Build stand alone](#build-stand-alone)
  - [CMake options](#cmake-options)
  - [Connect to your project](#connect-to-your-project)
- [How to make custom implementation](#how-to-make-custom-implementation)
- [Portability](#portability)



# Overview

**Camera** C++ library provides standard interface as well defines data structures and rules for different camera controllers. **Camera** interface class does nothing, just provides interface and provides methods to encode / decode commands and encode / decode params. Different camera controller classes inherit interface from **Camera** C++ class. **Camera.h** file contains list of data structures ([CameraCommand](#cameracommand-enum) enum, [CameraParam](#cameraparam-enum) enum and [CameraParams](#cameraparams-class-description) class) and **Camera** class declaration. [CameraCommand](#cameracommand-enum) enum contains IDs of action commands supported by **Camera** class. [CameraParam](#cameraparam-enum) enum contains IDs of params supported by **Camera** class. All camera controllers should include params and commands listed in **Camera.h** file. Camera interface class only depends on [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library (provides methods to read / write JSON config files). The repository doesn't contain the source code of **ConfigReader**: the library must be placed next to the **Camera** repository (see [Build stand alone](#build-stand-alone)). It uses C++17 standard.



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | 05.05.2023   | First version                                                |
| 1.1.0   | 08.05.2023   | - Added new parameter.                                       |
| 1.2.0   | 10.05.2023   | - Parameters list changed.                                   |
| 2.0.0   | 30.06.2023   | - Added new parameters.<br />- Added new methods to encode/decode commands.<br />- Added new class CameraParams to store camera parameters.<br />- Added license.<br />- Repository made public. |
| 2.1.0   | 12.07.2023   | - Added CameraParamsMask structure.<br />- Names of params updated.<br />- Updated encode(...) and decode(...) methods of CameraParams. |
| 2.2.0   | 20.09.2023   | - Updated encode(...) and decode(...) methods of CameraParams.<br />- Added decodeAndExecuteCommand(...) method.<br />- Added example of camera controller implementation. |
| 2.2.1   | 22.09.2023   | - Fixed mistakes in documentation.                           |
| 2.3.0   | 26.09.2023   | - Changed getParams method return type.                      |
| 2.4.0   | 13.12.2023   | - Virtual destructor added.                                  |
| 2.5.0   | 08.01.2024   | - Name of parameters updated.                                |
| 2.5.1   | 25.03.2024   | - ConfigReader class updated. <br />- Documentation updated. |
| 2.5.2   | 21.05.2024   | - ConfigReader class updated. <br />- Documentation updated. |
| 2.5.3   | 23.07.2024   | - CMake updated.                                             |
| 2.5.4   | 03.09.2024   | - Documentation updated. |
| 2.5.5   | 16.10.2026   | - Git submodule removed: **ConfigReader** library must be placed next to the **Camera** repository.<br />- Compiler warnings, exploit mitigation flags and standard C++ mode added to CMake files of the library, the example and the test application.<br />- **CameraParams::decode(...)** accepts data without fields (empty mask) and doesn't change the object if the data is rejected.<br />- **CameraParams::encode(...)**, **Camera::encodeCommand(...)** and **Camera::encodeSetParamCommand(...)** reject nullptr and set the size to 0, **CameraParams::encode(...)** sets the size to 0 if the buffer is too small.<br />- **Camera::decodeCommand(...)** checks the pointer, the exact size of both commands and the range of command and param IDs, returns -1 for any error (a set param command of wrong size was reported as decoded) and doesn't change the output arguments in case of error.<br />- Special member functions of **CameraParams** and **Camera** classes declared (defaulted).<br />- Example of camera controller made thread-safe, it validates the values.<br />- Test application rewritten.<br />- Documentation corrected. |



# Library files

The library supplied by source code only. The user would be given a set of files in the form of a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ---------------- Main CMake file of the library.
example ----------------------- Folder with custom camera controller example.
    CMakeLists.txt ------------ CMake file of example.
    CustomCamera.cpp ---------- C++ implementation file.
    CustomCamera.h ------------ Header with class declaration.
    CustomCameraVersion.h ----- Header file which include class version.
    CustomCameraVersion.h.in -- CMake service file to generate version file.
test -------------------------- Folder with test application.
    CMakeLists.txt ------------ CMake file for test application.
    main.cpp ------------------ Source code file of test application.
src --------------------------- Folder with source code of the library.
    CMakeLists.txt ------------ CMake file of the library.
    Camera.cpp ---------------- C++ implementation file.
    Camera.h ------------------ Header file which includes Camera class declaration.
    CameraVersion.h ----------- Header file which includes version of the library.
    CameraVersion.h.in -------- CMake service file to generate version header.
```



# Camera interface class description



## Camera class declaration

**Camera** interface class declared in **Camera.h** file. Class declaration:

```cpp
namespace rapidpixel
{
/// Camera controller interface class.
class Camera
{
public:

    /// Class destructor.
    virtual ~Camera();

    /// Get Camera class version.
    static std::string getVersion();

    /// Open camera controller.
    virtual bool openCamera(std::string initString) = 0;

    /// Init camera controller by set of parameters.
    virtual bool initCamera(CameraParams& params) = 0;

    /// Close camera connection.
    virtual void closeCamera() = 0;

    /// Get camera open status.
    virtual bool isCameraOpen() = 0;

    /// Get camera connection status.
    virtual bool isCameraConnected() = 0;

    /// Set the camera controller parameter.
    virtual bool setParam(CameraParam id, float value) = 0;

    /// Get the camera controller parameter.
    virtual float getParam(CameraParam id) = 0;

    /// Get all camera controller parameters.
    virtual void getParams(CameraParams& params) = 0;

    /// Execute camera controller action command.
    virtual bool executeCommand(CameraCommand id) = 0;

    /// Encode set param command.
    static void encodeSetParamCommand(
            uint8_t* data, int& size, CameraParam id, float value);

    /// Encode command.
    static void encodeCommand(
            uint8_t* data, int& size, CameraCommand id);

    /// Decode command.
    static int decodeCommand(uint8_t* data,
                             int size,
                             CameraParam& paramId,
                             CameraCommand& commandId,
                             float& value);

    /// Decode and execute command.
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;

protected:

    /// Default constructor. The class can be used as a base only.
    Camera() = default;

    /// Copy constructor.
    Camera(const Camera& src) = default;

    /// Move constructor.
    Camera(Camera&& src) = default;

    /// Copy assignment operator.
    Camera& operator= (const Camera& src) = default;

    /// Move assignment operator.
    Camera& operator= (Camera&& src) = default;
};
}
```



## getVersion method

The **getVersion()** method returns string of current class version. Particular camera controller can have it's own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **Camera** class instance:

```cpp
std::cout << "Camera class v: " << rapidpixel::Camera::getVersion() << std::endl;
```

Console output:

```bash
Camera class v: 2.5.5
```



## openCamera method

The **openCamera(...)** method initializes camera controller. All camera parameters will be initialized by default. This method can be used instead of [initCamera(...)](#initcamera-method) method. Method declaration:

```cpp
virtual bool openCamera(std::string initString) = 0;
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| initString | Initialization string. Particular camera controller can have unique initialization string format. But it is recommended to use '**;**' symbol to divide part of initialization string. Recommended camera controller initialization string for controllers which use serial port: **"/dev/ttyUSB0;9600;100"** ("/dev/ttyUSB0" - serial port name, "9600" - baudrate, "100" - serial port read timeout). |

**Returns:** TRUE if the camera controller is initialized or FALSE if not.



## initCamera method

The **initCamera(...)** method initializes camera controller by set of parameters. This method can be used instead of [openCamera(...)](#opencamera-method) method ([CameraParams](#cameraparams-class-description) class includes **initString**) when you need initialize camera controller with not default parameters values. Method declaration:

```cpp
virtual bool initCamera(CameraParams& params) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| params    | [CameraParams](#cameraparams-class-description) class object. CameraParams class includes initString which used in [openCamera(...)](#opencamera-method) method. |

**Returns:** TRUE if the camera controller is initialized or FALSE if not.



## closeCamera method

The **closeCamera()** method designed to close connection to camera. Method declaration:

```cpp
virtual void closeCamera() = 0;
```



## isCameraOpen method

The **isCameraOpen()** method returns camera initialization status. Open status shows if the camera controller is initialized but doesn't show if camera controller has communication with camera equipment. For example, if camera has serial port and camera controller connected to serial port (opens serial port file in OS) but camera may be not active (no power). In this case open status just shows that camera controller has opened serial port. Method declaration:

```cpp
virtual bool isCameraOpen() = 0;
```

**Returns:** TRUE if the camera controller is initialized or FALSE if not.



## isCameraConnected method

The **isCameraConnected()** method returns camera connection status. Connection status shows if the camera controller has data exchange with camera equipment. For example, if camera has serial port and camera controller connected to serial port (opens serial port file in OS) but camera may be not active (no power). In this case connection status shows that camera controller doesn't have data exchange with camera equipment (method will return FALSE). If camera controller has data exchange with camera equipment the method will return TRUE. If camera controller not initialized the connection status always FALSE. Method declaration:

```cpp
virtual bool isCameraConnected() = 0;
```

**Returns:** TRUE if the camera controller has data exchange with camera equipment or FALSE if not.



## setParam method

The **setParam(...)** method sets new camera controller parameters value. The particular implementation of the camera controller must provide thread-safe **setParam(...)** method call. This means that the **setParam(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool setParam(CameraParam id, float value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera parameter ID according to [CameraParam](#cameraparam-enum) enum. |
| value     | Camera parameter value. Value depends on parameter ID.       |

**Returns:** TRUE if the parameter was set or FALSE if not.



## getParam method

The **getParam(...)** method returns controller parameter value. The particular implementation of the camera controller must provide thread-safe **getParam(...)** method call. This means that the **getParam(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual float getParam(CameraParam id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera controller parameter ID according to [CameraParam](#cameraparam-enum) enum. |

**Returns:** parameter value or **-1** if the parameter doesn't exist in particular camera controller.



## getParams method

The **getParams(...)** method designed to obtain camera parameters. The particular implementation of the camera controller must provide thread-safe **getParams(...)** method call. This means that the **getParams(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual void getParams(CameraParams& params) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| params    | Output [CameraParams](#cameraparams-class-description) class object. |



## executeCommand method

The **executeCommand(...)** method executes camera controller action command. The particular implementation of the camera controller must provide thread-safe **executeCommand(...)** method call. This means that the **executeCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool executeCommand(CameraCommand id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Camera action command ID according to [CameraCommand](#cameracommand-enum) enum. |

**Returns:** TRUE if the command was executed (accepted by controller) or FALSE if not.



## encodeSetParamCommand method

The **encodeSetParamCommand(...)** static method encodes command to change any remote camera parameter. To control a camera remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **Camera** class contains static methods for encoding the control command. The **Camera** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeSetParamCommand(...)** designed to encode SET_PARAM command. Method declaration:

```cpp
static void encodeSetParamCommand(uint8_t* data, int& size, CameraParam id, float value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must not be nullptr and must have size >= 11. |
| size      | Size of encoded data. Will be 11 bytes (0 if data is nullptr). |
| id        | Parameter ID according to [CameraParam](#cameraparam-enum) enum. |
| value     | Parameter value. The value is not checked: it is transported as is (also NaN and infinity). |

The method can't check that the buffer is valid for 11 bytes: this is the contract of the method. If **data** is nullptr nothing is encoded and **size** is set to 0.

**encodeSetParamCommand(...)** is static and used without **Camera** class instance. This method used on client side (control system). Command encoding example:

```cpp
// Buffer for encoded data.
uint8_t data[11];
// Size of encoded data.
int size = 0;
// Parameter value.
float outValue = 5.0f;
// Encode command.
rapidpixel::Camera::encodeSetParamCommand(
    data, size, rapidpixel::CameraParam::ROI_X0, outValue);
```



## encodeCommand method

The **encodeCommand(...)** static method encodes action command for camera remote control. To control a camera remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **Camera** class contains static methods for encoding the control command. The **Camera** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeCommand(...)** designed to encode COMMAND command (action command). Method declaration:

```cpp
static void encodeCommand(uint8_t* data, int& size, CameraCommand id);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must not be nullptr and must have size >= 7. |
| size      | Size of encoded data. Will be 7 bytes (0 if data is nullptr). |
| id        | Command ID according to [CameraCommand](#cameracommand-enum) enum. |

The method can't check that the buffer is valid for 7 bytes: this is the contract of the method. If **data** is nullptr nothing is encoded and **size** is set to 0.

**encodeCommand(...)** is static and used without **Camera** class instance. This method used on client side (control system). Command encoding example:

```cpp
// Buffer for encoded data.
uint8_t data[7];
// Size of encoded data.
int size = 0;
// Encode command.
rapidpixel::Camera::encodeCommand(data, size, rapidpixel::CameraCommand::NUC);
```



## decodeCommand method

The **decodeCommand(...)** static method decodes command on camera controller side encoded by [encodeSetParamCommand(...)](#encodesetparamcommand-method) or [encodeCommand(...)](#encodecommand-method). Method declaration:

```cpp
static int decodeCommand(uint8_t* data, int size, CameraParam& paramId, CameraCommand& commandId, float& value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command. Must not be nullptr.               |
| size      | Size of command. Must be exactly 11 bytes for SET_PARAM and exactly 7 bytes for COMMAND. |
| paramId   | Camera parameter ID according to [CameraParam](#cameraparam-enum) enum. After decoding SET_PARAM command the method will return parameter ID. |
| commandId | Camera command ID according to [CameraCommand](#cameracommand-enum) enum. After decoding COMMAND the method will return command ID. |
| value     | Camera parameter value (after decoding SET_PARAM command) or 0 (after decoding COMMAND). |

The method checks the pointer, the size, the version (major and minor numbers of the command must be equal to the version of the library), the data type and the ID: the ID must be inside the range of the [CameraParam](#cameraparam-enum) or [CameraCommand](#cameracommand-enum) enum. The output arguments are changed only if the command was decoded. The value of SET_PARAM command is not checked: it is transported as is (also NaN and infinity).

**Returns:** **0** - in case decoding COMMAND, **1** - in case decoding SET_PARAM command or **-1** in case errors (data is nullptr, wrong size, version, data type or ID).



## decodeAndExecuteCommand method

The **decodeAndExecuteCommand(...)** method decodes and executes command on camera controller side. The particular implementation of the camera controller must provide thread-safe **decodeAndExecuteCommand(...)** method call. This means that the **decodeAndExecuteCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command.                                    |
| size      | Size of command. Must be 11 bytes for SET_PARAM or 7 bytes for COMMAND. |

**Returns:** TRUE if command decoded (SET_PARAM or COMMAND) and executed (action command or set param command).

Recommended implementation of **decodeAndExecuteCommand(...)** method:

```cpp
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
```



# Data structures



## CameraCommand enum

Enum declaration:

```cpp
namespace rapidpixel
{
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
}
```

**Table 2** - Camera action commands description. Some commands may be unsupported by particular camera controller.

| Command      | Description                                |
| ------------ | ------------------------------------------ |
| RESTART      | Restart camera controller.                 |
| NUC          | Do NUC (Calibration, flat field correction). For thermal cameras. |
| APPLY_PARAMS | Apply settings.                            |
| SAVE_PARAMS  | Save params in camera memory.              |
| MENU_ON      | Menu on.                                   |
| MENU_OFF     | Menu off.                                  |
| MENU_SET     | Menu set.                                  |
| MENU_UP      | Menu move up.                              |
| MENU_DOWN    | Menu move down.                            |
| MENU_LEFT    | Menu move left.                            |
| MENU_RIGHT   | Menu move right.                           |
| FREEZE       | Freeze image.                              |
| DEFREEZE     | Defreeze image.                            |



## CameraParam enum

Enum declaration:

```cpp
namespace rapidpixel
{
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
}
```

**Table 3** - Camera parameters description. Some parameters may be unsupported by particular camera controller.

| Parameter                      | Access       | Description                                                  |
| ------------------------------ | ------------ | ------------------------------------------------------------ |
| WIDTH                          | read / write | Video frame width. Value from 0 to 16384.                    |
| HEIGHT                         | read / write | Video frame height Value from 0 to 16384.                    |
| DISPLAY_MODE                   | read / write | Display menu mode. Value depends on implementation but it is recommended to keep default values: **0** - Off. **1** - On. |
| VIDEO_OUTPUT                   | read / write | Video output type. Value depends on implementation.          |
| LOG_MODE                       | read / write | Logging mode. Values: **0** - Disable, **1** - Only file, **2** - Only terminal (console), **3** - File and terminal. |
| EXPOSURE_MODE                  | read / write | Exposure mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto (default), **2** - Shutter priority, **3** - Aperture priority. |
| EXPOSURE_TIME                  | read / write | Exposure time of the camera sensor. The exposure time is limited by the frame interval. Camera controller should interpret the values as 100 µs units, where the value 1 stands for 1/10000th of a second, 10000 for 1 second and 100000 for 10 seconds. |
| WHITE_BALANCE_MODE             | read / write | White balance mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| WHITE_BALANCE_AREA             | read / write | White balance area. Value depends on implementation.         |
| WIDE_DYNAMIC_RANGE_MODE        | read / write | White dynamic range mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| STABILIZATION_MODE             | read / write | Image stabilization mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| ISO_SENSITIVITY                | read / write | ISO sensitivity. Value depends on implementation.            |
| SCENE_MODE                     | read / write | Scene mode. Value depends on implementation.                 |
| FPS                            | read / write | FPS.                                                         |
| BRIGHTNESS_MODE                | read / write | Brightness mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| BRIGHTNESS                     | read / write | Brightness. Value 0 - 100%.                                  |
| CONTRAST                       | read / write | Contrast. Value 1 - 100%.                                    |
| GAIN_MODE                      | read / write | Gain mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| GAIN                           | read / write | Gain. Value 1 - 100%.                                        |
| SHARPENING_MODE                | read / write | Sharpening mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| SHARPENING                     | read / write | Sharpening. Value 1 - 100%.                                  |
| PALETTE                        | read / write | Palette. Value depends on implementation but it is recommended to keep default values for thermal cameras: **0** - White hot, **1** - Black hot. |
| AGC_MODE                       | read / write | Analog gain control mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| SHUTTER_MODE                   | read / write | Shutter mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| SHUTTER_POSITION               | read / write | Shutter position. 0 (full close) - 65535 (full open).        |
| SHUTTER_SPEED                  | read / write | Shutter speed. Value: 0 - 100%.                              |
| DIGITAL_ZOOM_MODE              | read / write | Digital zoom mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| DIGITAL_ZOOM                   | read / write | Digital zoom. Value 1.0 (x1) - 20.0 (x20).                   |
| EXPOSURE_COMPENSATION_MODE     | read / write | Exposure compensation mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| EXPOSURE_COMPENSATION_POSITION | read / write | Exposure compensation position. Value depends on particular camera controller. |
| DEFOG_MODE                     | read / write | Defog mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| DEHAZE_MODE                    | read / write | Dehaze mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| NOISE_REDUCTION_MODE           | read / write | Noise reduction mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - 2D, **3** - 3D. |
| BLACK_WHITE_FILTER_MODE        | read / write | Black and white filter mode. Value depends on implementation but it is recommended to keep default values: 0 - Off, 1 - On. |
| FILTER_MODE                    | read / write | Filter mode. Value depends on implementation.                |
| NUC_MODE                       | read / write | NUC mode for thermal cameras. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| AUTO_NUC_INTERVAL_MSEC         | read / write | Auto NUC interval for thermal cameras. Value in milliseconds from 0 (Off) to 100000. |
| IMAGE_FLIP                     | read / write | Image flip mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - Horizontal, **2** - Vertical, **3** - Horizontal and vertical. |
| DDE_MODE                       | read / write | DDE mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| DDE_LEVEL                      | read / write | DDE level. Value depends on implementation.                  |
| ROI_X0                         | read / write | ROI top-left horizontal position, pixels.                    |
| ROI_Y0                         | read / write | ROI top-left vertical position, pixels.                      |
| ROI_X1                         | read / write | ROI bottom-right horizontal position, pixels.                |
| ROI_Y1                         | read / write | ROI bottom-right vertical position, pixels.                  |
| TEMPERATURE                    | read only    | Camera temperature, degree.                                  |
| ALC_GATE                       | read / write | ALC gate. Value depends on implementation.                   |
| SENSITIVITY                    | read / write | Sensor sensitivity. Value depends on implementation.         |
| CHANGING_MODE                  | read / write | Changing mode (day / night). Value depends on implementation. |
| CHANGING_LEVEL                 | read / write | Changing level (day / night). Value depends on implementation. |
| CHROMA_LEVEL                   | read / write | Chroma level. Values: 0 - 100%.                              |
| DETAIL                         | read / write | Details, enhancement. Values: 0 - 100%.                      |
| PROFILE                        | read / write | Camera settings profile. Value depends on implementation.    |
| IS_CONNECTED                   | read only    | Connection status. Value: **0** - no camera responses, **1** - connected. |
| IS_OPEN                        | read only    | Open status (read only): **1** - camera control port open, **0** - not open. |
| TYPE                           | read / write | Camera type. Value depends on implementation.                |
| CUSTOM_1                       | read / write | Camera custom param. Value depends on implementation.        |
| CUSTOM_2                       | read / write | Camera custom param. Value depends on implementation.        |
| CUSTOM_3                       | read / write | Camera custom param. Value depends on implementation.        |



# CameraParams class description

**CameraParams** class used for camera controller initialization ([initCamera(...)](#initcamera-method) method) or to get all actual params ([getParams(...)](#getparams-method) method). Also **CameraParams** provide structure to write/read params from JSON files (**JSON_READABLE** macro) and provide methods to encode and decode params.



## CameraParams class declaration

**CameraParams** interface class declared in **Camera.h** file. Class declaration:

```cpp
namespace rapidpixel
{
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

    /// Default constructor. All fields have default values.
    CameraParams() = default;

    /// Copy constructor.
    CameraParams(const CameraParams& src) = default;

    /// Move constructor.
    CameraParams(CameraParams&& src) = default;

    /// Copy assignment operator.
    CameraParams& operator= (const CameraParams& src) = default;

    /// Move assignment operator.
    CameraParams& operator= (CameraParams&& src) = default;

    /// Encode params.
    bool encode(uint8_t* data, int bufferSize, int& size,
                CameraParamsMask* mask = nullptr);

    /// Decode params.
    bool decode(uint8_t* data, int dataSize);
};
}
```

**Table 4** - CameraParams class fields description is equivalent to [CameraParam](#cameraparam-enum) enum description.

| Field                        | type   | Description                                                  |
| ---------------------------- | ------ | ------------------------------------------------------------ |
| initString                   | string | Initialization string. Particular camera controller can have unique init string format. But it is recommended to use '**;**' symbol to divide part of initialization string. Recommended camera controller initialization string for controllers which uses serial port: **"/dev/ttyUSB0;9600;100"** ("/dev/ttyUSB0" - serial port name, "9600" - baudrate, "100" - serial port read timeout). |
| width                        | int    | Video frame width. Value from 0 to 16384.                    |
| height                       | int    | Video frame height Value from 0 to 16384.                    |
| displayMode                  | int    | Display menu mode. Value depends on implementation but it is recommended to keep default values: **0** - Off. **1** - On. |
| videoOutput                  | int    | Video output type. Value depends on implementation.          |
| logMode                      | int    | Logging mode. Values: **0** - Disable, **1** - Only file, **2** - Only terminal (console), **3** - File and terminal. |
| exposureMode                 | int    | Exposure mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto (default), **2** - Shutter priority, **3** - Aperture priority. |
| exposureTime                 | int    | Exposure time of the camera sensor. The exposure time is limited by the frame interval. Camera controller should interpret the values as 100 µs units, where the value 1 stands for 1/10000th of a second, 10000 for 1 second and 100000 for 10 seconds. |
| whiteBalanceMode             | int    | White balance mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| whiteBalanceArea             | int    | White balance area. Value depends on implementation.         |
| wideDynamicRangeMode         | int    | White dynamic range mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| stabilizationMode            | int    | Image stabilization mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| isoSensitivity               | int    | ISO sensitivity. Value depends on implementation.            |
| sceneMode                    | int    | Scene mode. Value depends on implementation.                 |
| fps                          | float  | FPS.                                                         |
| brightnessMode               | int    | Brightness mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| brightness                   | int    | Brightness. Value 0 - 100%.                                  |
| contrast                     | int    | Contrast. Value 1 - 100%.                                    |
| gainMode                     | int    | Gain mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| gain                         | int    | Gain. Value 1 - 100%.                                        |
| sharpeningMode               | int    | Sharpening mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| sharpening                   | int    | Sharpening. Value 1 - 100%.                                  |
| palette                      | int    | Palette. Value depends on implementation but it is recommended to keep default values for thermal cameras: **0** - White hot, **1** - Black hot. |
| agcMode                      | int    | Analog gain control mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| shutterMode                  | int    | Shutter mode. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| shutterPos                   | int    | Shutter position. 0 (full close) - 65535 (full open).        |
| shutterSpeed                 | int    | Shutter speed. Value: 0 - 100%.                              |
| digitalZoomMode              | int    | Digital zoom mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| digitalZoom                  | float  | Digital zoom. Value 1.0 (x1) - 20.0 (x20).                   |
| exposureCompensationMode     | int    | Exposure compensation mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| exposureCompensationPosition | int    | Exposure compensation position. Value depends on particular camera controller. |
| defogMode                    | int    | Defog mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| dehazeMode                   | int    | Dehaze mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| noiseReductionMode           | int    | Noise reduction mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - 2D, **3** - 3D. |
| blackAndWhiteFilterMode      | int    | Black and white filter mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| filterMode                   | int    | Filter mode. Value depends on implementation.                |
| nucMode                      | int    | NUC mode for thermal cameras. Value depends on implementation but it is recommended to keep default values: **0** - Manual, **1** - Auto. |
| autoNucIntervalMsec          | int    | Auto NUC interval for thermal cameras. Value in milliseconds from 0 (Off) to 100000. |
| imageFlip                    | int    | Image flip mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - Horizontal, **2** - Vertical, **3** - Horizontal and vertical. |
| ddeMode                      | int    | DDE mode. Value depends on implementation but it is recommended to keep default values: **0** - Off, **1** - On. |
| ddeLevel                     | float  | DDE level. Value depends on implementation.                  |
| roiX0                        | int    | ROI top-left horizontal position, pixels.                    |
| roiY0                        | int    | ROI top-left vertical position, pixels.                      |
| roiX1                        | int    | ROI bottom-right horizontal position, pixels.                |
| roiY1                        | int    | ROI bottom-right vertical position, pixels.                  |
| temperature                  | float  | Camera temperature, degree.                                  |
| alcGate                      | int    | ALC gate. Value depends on implementation.                   |
| sensitivity                  | float  | Sensor sensitivity. Value depends on implementation.         |
| changingMode                 | int    | Changing mode (day / night). Value depends on implementation. |
| changingLevel                | float  | Changing level (day / night). Value depends on implementation. |
| chromaLevel                  | int    | Chroma level. Values: 0 - 100%.                              |
| detail                       | int    | Details, enhancement. Values: 0 - 100%.                      |
| profile                      | int    | Camera settings profile. Value depends on implementation.    |
| isConnected                  | bool   | Connection status. Value: false - no camera responses, true - connected. |
| isOpen                       | bool   | Open status (read only): true - camera control port open, false - not open. |
| type                         | int    | Camera type. Value depends on implementation.                |
| custom1                      | float  | Camera custom param. Value depends on implementation.        |
| custom2                      | float  | Camera custom param. Value depends on implementation.        |
| custom3                      | float  | Camera custom param. Value depends on implementation.        |

**Note:** *CameraParams class fields listed in Table 4 **must** reflect params set/get by methods setParam(...) and getParam(...).*



## Serialize camera params

[CameraParams](#cameraparams-class-description) class provides method **encode(...)** to serialize camera params (fields of [CameraParams](#cameraparams-class-description) class, see Table 4). Serialization of camera params necessary in case when you have to send camera params via communication channels. Method doesn't encode **initString** field. Method provides options to exclude particular parameters from serialization. To do this method inserts binary mask (8 bytes) where each bit represents particular parameter and **decode(...)** method recognizes it. The encoded data contains the data type, the version of the library (major and minor numbers), the mask and the values of the selected parameters. The values are stored in the byte order of the host (see [Portability](#portability)). Method declaration:

```cpp
bool encode(uint8_t* data, int bufferSize, int& size, CameraParamsMask* mask = nullptr);
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| data       | Pointer to data buffer. Must not be nullptr. Buffer size must be >= 237 bytes. The method can't check that the buffer is valid for **bufferSize** bytes: this is the contract of the method. |
| bufferSize | Data buffer size. Buffer size must be >= 237 bytes (the size of the data with all parameters selected). |
| size       | Size of encoded data. Set to 0 if the method returns FALSE.  |
| mask       | Parameters mask - pointer to **CameraParamsMask** structure. **CameraParamsMask** (declared in Camera.h file) determines flags for each field (parameter) declared in [CameraParams](#cameraparams-class-description) class. All flags are **true** by default. If the user wants to exclude a particular parameter from serialization, he should set the corresponding flag in the **CameraParamsMask** structure to **false** and put a pointer to the mask. If **mask** is nullptr all parameters are encoded. |

**Returns:** TRUE if params encoded (serialized) or FALSE if not (**data** is nullptr or **bufferSize** is less than 237).

**CameraParamsMask** structure declaration:

```cpp
typedef struct CameraParamsMask
{
    bool width{true};
    bool height{true};
    bool displayMode{true};
    bool videoOutput{true};
    bool logMode{true};
    bool exposureMode{true};
    bool exposureTime{true};
    bool whiteBalanceMode{true};
    bool whiteBalanceArea{true};
    bool wideDynamicRangeMode{true};
    bool stabilizationMode{true};
    bool isoSensitivity{true};
    bool sceneMode{true};
    bool fps{true};
    bool brightnessMode{true};
    bool brightness{true};
    bool contrast{true};
    bool gainMode{true};
    bool gain{true};
    bool sharpeningMode{true};
    bool sharpening{true};
    bool palette{true};
    bool agcMode{true};
    bool shutterMode{true};
    bool shutterPos{true};
    bool shutterSpeed{true};
    bool digitalZoomMode{true};
    bool digitalZoom{true};
    bool exposureCompensationMode{true};
    bool exposureCompensationPosition{true};
    bool defogMode{true};
    bool dehazeMode{true};
    bool noiseReductionMode{true};
    bool blackAndWhiteFilterMode{true};
    bool filterMode{true};
    bool nucMode{true};
    bool autoNucIntervalMsec{true};
    bool imageFlip{true};
    bool ddeMode{true};
    bool ddeLevel{true};
    bool roiX0{true};
    bool roiY0{true};
    bool roiX1{true};
    bool roiY1{true};
    bool temperature{true};
    bool alcGate{true};
    bool sensitivity{true};
    bool changingMode{true};
    bool changingLevel{true};
    bool chromaLevel{true};
    bool detail{true};
    bool profile{true};
    bool isConnected{true};
    bool isOpen{true};
    bool type{true};
    bool custom1{true};
    bool custom2{true};
    bool custom3{true};
} CameraParamsMask;
```

Example without parameters mask:

```cpp
// Encode data.
rapidpixel::CameraParams in;
in.profile = 10;
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size))
{
    std::cout << "Can't encode params" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;
```

Example with parameters mask:

```cpp
// Prepare params.
rapidpixel::CameraParams in;
in.profile = 3;

// Prepare mask.
rapidpixel::CameraParamsMask mask;
mask.profile = false; // Exclude profile. Others by default.

// Encode.
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size, &mask))
{
    std::cout << "Can't encode params" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;
```



## Deserialize camera params

[CameraParams](#cameraparams-class-description) class provides method **decode(...)** to deserialize camera params (fields of [CameraParams](#cameraparams-class-description) class, see Table 4). Deserialization of camera params necessary in case when you need to receive params via communication channels. Method automatically recognizes which parameters were serialized by **encode(...)** method. Method doesn't decode **initString** field: it is set to an empty string. Method checks the data type, the version (major and minor numbers of the data must be equal to the version of the library) and the size of the data before reading each parameter. A parameter which is not selected by the mask of the encoded data is set to zero (false). The values of the parameters are not checked against any range. Mask bits which don't belong to any parameter and bytes after the last parameter are ignored. Method declaration:

```cpp
bool decode(uint8_t* data, int dataSize);
```

| Parameter | Value                                                 |
| --------- | ----------------------------------------------------- |
| data      | Pointer to data buffer with serialized camera params. Must not be nullptr. |
| dataSize  | Size of the data, bytes. Must be >= 11 (the size of the data without parameters). |

**Returns:** TRUE if params decoded (deserialized) or FALSE if not. If FALSE is returned the object is not changed.

Example:

```cpp
// Encode data.
rapidpixel::CameraParams in;
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size))
{
    std::cout << "Can't encode params" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;

// Decode data.
rapidpixel::CameraParams out;
if (!out.decode(data, size))
{
    std::cout << "Can't decode data" << std::endl;
    return false;
}
```



## Read params from JSON file and write to JSON file

**Camera** library depends on [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library which provides methods to read params from JSON file and to write params to JSON file. The fields **temperature**, **isConnected** and **isOpen** are not stored in JSON. If the document is invalid, or a stored field is missing or has a wrong type, **get(...)** returns FALSE and the object is not changed (a boolean value of an int field is accepted as 0 or 1). A value of an int field which is outside of the int range is rejected, a number with a fractional part is truncated. Example of writing and reading params to JSON file:

```cpp
// Prepare params.
rapidpixel::CameraParams in;
in.initString = "dfhglsjirhuhjfb";
in.width = 99;
in.fps = 133.0f;
in.digitalZoom = 201.0f;

// Write params to file.
rapidpixel::ConfigReader inConfig;
if (!inConfig.set(in, "cameraParams") ||
    !inConfig.writeToFile("TestCameraParams.json"))
{
    std::cout << "Can't write config file" << std::endl;
    return false;
}

// Read params from file.
rapidpixel::ConfigReader outConfig;
if (!outConfig.readFromFile("TestCameraParams.json"))
{
    std::cout << "Can't open config file" << std::endl;
    return false;
}
rapidpixel::CameraParams out;
if (!outConfig.get(out, "cameraParams"))
{
    std::cout << "Can't read params from config file" << std::endl;
    return false;
}
```

**TestCameraParams.json** will look like (the fields are written in the order of the **CameraParams** declaration):

```json
{
    "cameraParams": {
        "initString": "dfhglsjirhuhjfb",
        "width": 99,
        "height": 0,
        "displayMode": 0,
        "videoOutput": 0,
        "logMode": 0,
        "exposureMode": 1,
        "exposureTime": 0,
        "whiteBalanceMode": 1,
        "whiteBalanceArea": 0,
        "wideDynamicRangeMode": 0,
        "stabilizationMode": 0,
        "isoSensitivity": 0,
        "sceneMode": 0,
        "fps": 133.0,
        "brightnessMode": 1,
        "brightness": 0,
        "contrast": 0,
        "gainMode": 1,
        "gain": 0,
        "sharpeningMode": 0,
        "sharpening": 0,
        "palette": 0,
        "agcMode": 1,
        "shutterMode": 1,
        "shutterPos": 0,
        "shutterSpeed": 0,
        "digitalZoomMode": 0,
        "digitalZoom": 201.0,
        "exposureCompensationMode": 0,
        "exposureCompensationPosition": 0,
        "defogMode": 0,
        "dehazeMode": 0,
        "noiseReductionMode": 0,
        "blackAndWhiteFilterMode": 0,
        "filterMode": 0,
        "nucMode": 0,
        "autoNucIntervalMsec": 0,
        "imageFlip": 0,
        "ddeMode": 0,
        "ddeLevel": 0.0,
        "roiX0": 0,
        "roiY0": 0,
        "roiX1": 0,
        "roiY1": 0,
        "alcGate": 0,
        "sensitivity": 0.0,
        "changingMode": 0,
        "changingLevel": 0.0,
        "chromaLevel": 0,
        "detail": 0,
        "profile": 0,
        "type": 0,
        "custom1": 0.0,
        "custom2": 0.0,
        "custom3": 0.0
    }
}
```



# Build and connect to your project



## Build stand alone

The repository doesn't contain sub-repositories. The **ConfigReader** library which **Camera** depends on must be cloned into the same folder as **Camera**. The folder structure must be:

```bash
<work folder>
    Camera
    ConfigReader
```

Typical commands to build **Camera** library, the test application and the example (use the URLs of the repositories provided to you):

```bash
git clone <Camera repository URL>
git clone <ConfigReader repository URL>
cd Camera
mkdir build
cd build
cmake ..
make
```

On Windows use `cmake --build . --config Release` instead of `make`. If **Camera** is the top-level CMake project, the main CMakeLists.txt file adds the folder ../ConfigReader before the library itself. If the folder doesn't exist CMake stops with an error.



## CMake options

**Table 5** - CMake options of the repository. In the options below ${PARENT} is the prefix defined by the top-level project (empty if **Camera** is the top-level project).

| Option                              | Default                                           | Description                                                  |
| ----------------------------------- | ------------------------------------------------- | ------------------------------------------------------------ |
| ${PARENT}_CAMERA                    | ON                                                | Build the library.                                           |
| ${PARENT}_CAMERA_TEST               | ON (stand alone), OFF (included in other project) | Build the test application.                                  |
| ${PARENT}_CAMERA_EXAMPLE            | ON (stand alone), OFF (included in other project) | Build the example of the camera controller.                  |
| ${PARENT}_SUBMODULE_CACHE_OVERWRITE | ON                                                | Forced rewriting of the options above in the CMake cache. The top-level project sets it to OFF when it includes **Camera** as a sub-repository. |
| CMAKE_BUILD_TYPE                    | Release (if not specified)                        | Build type.                                                  |



## Connect to your project

If you want to connect **Camera** library to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

Create **3rdparty** folder in your repository folder and put the repositories **ConfigReader** and **Camera** there (the repositories can be cloned, copied or added as submodules of your repository, for example `git submodule add <Camera repository URL> 3rdparty/Camera`; **Camera** doesn't contain sub-repositories):

```bash
cd <your repository folder>
mkdir 3rdparty
cd 3rdparty
git clone <ConfigReader repository URL>
git clone <Camera repository URL>
```

New structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    ConfigReader
    Camera
```

Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_CONFIG_READER                   ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_CONFIG_READER)
    SET(${PARENT}_CONFIG_READER                         ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_EXAMPLES                OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_TESTS                   OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_CAMERA                          ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_CAMERA)
    SET(${PARENT}_CAMERA                                ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_CAMERA_TEST                           OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_CAMERA_EXAMPLE                        OFF CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_CONFIG_READER)
    add_subdirectory(ConfigReader)
endif()

if (${PARENT}_SUBMODULE_CAMERA)
    add_subdirectory(Camera)
endif()
```

File **3rdparty/CMakeLists.txt** adds folders **ConfigReader** and **Camera** to your project and excludes test application and example (Camera class test applications and example of custom Camera class implementation) from compiling (by default test application and example excluded from compiling if **Camera** included as subrepository). The folders are added in the order of their dependencies: **Camera** depends on **ConfigReader**. When **Camera** is included in another project it doesn't add **ConfigReader** by itself: your project must add it (before or after **Camera**). If it is not added, the compilation stops with the error "ConfigReader.h: No such file or directory". Your repository new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    ConfigReader
    Camera
```

Next you need include folder 3rdparty in main **CMakeLists.txt** file of your repository. Add string at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next you have to include **Camera** library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} Camera)
```

Done!



# How to make custom implementation

The **Camera** class provides only an interface, data structures, and methods for encoding and decoding commands and params. To create your own implementation of the camera controller, you must include the Camera repository in your project (see [Build and connect to your project](#build-and-connect-to-your-project) section). The catalogue **example** (see [Library files](#library-files) section) includes an example of the design of the custom camera controller. You must implement all the methods of the Camera interface class. The methods which are declared thread-safe in the description above must be thread-safe in the implementation (the example holds a mutex while it reads or changes the params). Custom camera class declaration:

```cpp
namespace rapidpixel
{
/**
 * @brief Custom camera controller class.
 */
class CustomCamera: public Camera
{
public:

    /// Class constructor.
    CustomCamera();

    /// Class destructor.
    ~CustomCamera() override;

    /// Copy constructor is deleted: the class owns a mutex.
    CustomCamera(const CustomCamera&) = delete;

    /// Move constructor is deleted: the class owns a mutex.
    CustomCamera(CustomCamera&&) = delete;

    /// Copy assignment is deleted: the class owns a mutex.
    CustomCamera& operator= (const CustomCamera&) = delete;

    /// Move assignment is deleted: the class owns a mutex.
    CustomCamera& operator= (CustomCamera&&) = delete;

    /// Get class version.
    static std::string getVersion();

    /// Open camera controller.
    bool openCamera(std::string initString) override;

    /// Init camera controller by set of parameters.
    bool initCamera(CameraParams& params) override;

    /// Close camera connection.
    void closeCamera() override;

    /// Get camera open status.
    bool isCameraOpen() override;

    /// Get camera connection status.
    bool isCameraConnected() override;

    /// Set the camera controller param.
    bool setParam(CameraParam id, float value) override;

    /// Get the camera controller param.
    float getParam(CameraParam id) override;

    /// Get the camera controller params.
    void getParams(CameraParams& params) override;

    /// Execute camera controller command.
    bool executeCommand(CameraCommand id) override;

    /// Decode and execute command.
    bool decodeAndExecuteCommand(uint8_t* data, int size) override;

private:

    /// Camera params. Protected by m_paramsMutex.
    CameraParams m_params;
    /// Mutex to protect m_params.
    std::mutex m_paramsMutex;
};
}
```



# Portability

The library and the example use standard C++17 only (no compiler extensions) and have no CPU specific code. The encoded params and commands store values of int and float types as raw 4 bytes values in the byte order of the host: the library doesn't convert the byte order and checks at compile time that int and float have 4 bytes. The library was built and its test application was run on little-endian x86-64 (Windows with MSVC 2022, Linux with GCC 12 and 13, Linux with Clang 15 and 18) and on little-endian aarch64 (Linux, GCC cross compiler, qemu). Data encoded on a host can be decoded only on a host with the same byte order.
