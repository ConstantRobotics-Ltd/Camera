#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include "Camera.h"



namespace rapidpixel
{
/**
 * @brief Custom camera controller class.
 *
 * The class doesn't control any camera equipment: it stores the params and
 * shows how to implement the Camera interface. All methods are thread-safe.
 */
class CustomCamera: public Camera
{
public:

    /**
     * @brief Class constructor.
     */
    CustomCamera();

    /**
     * @brief Class destructor.
     */
    ~CustomCamera() override;

    /**
     * @brief Copy constructor is deleted: the class owns a mutex.
     */
    CustomCamera(const CustomCamera&) = delete;

    /**
     * @brief Move constructor is deleted: the class owns a mutex.
     */
    CustomCamera(CustomCamera&&) = delete;

    /**
     * @brief Copy assignment is deleted: the class owns a mutex.
     * @return Reference to this object.
     */
    CustomCamera& operator= (const CustomCamera&) = delete;

    /**
     * @brief Move assignment is deleted: the class owns a mutex.
     * @return Reference to this object.
     */
    CustomCamera& operator= (CustomCamera&&) = delete;

    /**
     * @brief Get class version.
     * @return String of current class version.
     */
    static std::string getVersion();

    /**
     * @brief Open camera controller. All params are set to default values.
     * @param initString Init string. Must not be longer than 256 bytes.
     * @return TRUE if the camera controller is init or FALSE if not (the init
     * string is too long).
     */
    bool openCamera(std::string initString) override;

    /**
     * @brief Init camera controller by structure. Can be used instead
     * openCamera(...) method.
     * @param params Camera params. The init string must not be longer than
     * 256 bytes and the values must be inside the ranges accepted by
     * setParam(...).
     * @return TRUE if the camera controller init or FALSE if not.
     */
    bool initCamera(CameraParams& params) override;

    /**
     * @brief Close camera connection.
     */
    void closeCamera() override;

    /**
     * @brief Get camera open status.
     * @return TRUE if the camera is open or FALSE.
     */
    bool isCameraOpen() override;

    /**
     * @brief Get camera connection status.
     * @return TRUE if the camera is connected or FALSE.
     */
    bool isCameraConnected() override;

    /**
     * @brief Set the camera controller param.
     * @param id Param ID.
     * @param value Param value. NaN, infinity and values outside the range of
     * the param are rejected.
     * @return TRUE if the property set or FALSE.
     */
    bool setParam(CameraParam id, float value) override;

    /**
     * @brief Get the camera controller param.
     * @param id Param ID.
     * @return Param value or -1 if the param doesn't exist.
     */
    float getParam(CameraParam id) override;

    /**
     * @brief Get the camera controller params.
     * @param params Reference to CameraParams object.
     */
    void getParams(CameraParams& params) override;

    /**
     * @brief Execute camera controller command.
     * @param id Command ID.
     * @return TRUE if the command executed or FALSE.
     */
    bool executeCommand(CameraCommand id) override;

    /**
     * @brief Decode and execute command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @return TRUE if command decoded and executed or FALSE if not.
     */
    bool decodeAndExecuteCommand(uint8_t* data, int size) override;

private:

    /// Camera params. Protected by m_paramsMutex.
    CameraParams m_params;
    /// Mutex to protect m_params.
    std::mutex m_paramsMutex;
};
}
