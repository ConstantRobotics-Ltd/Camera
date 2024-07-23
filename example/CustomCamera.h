#pragma once
#include <string>
#include <cstdint>
#include "Camera.h"



namespace cr
{
namespace camera
{
/**
 * @brief Custom camera controller class.
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
    ~CustomCamera();

    /**
     * @brief Get class version.
     * @return String of current class version.
     */
    static std::string getVersion();

    /**
     * @brief Open camera controller.
     * @param initString Init string.
     * @return TRUE if the camera controller is init or FALSE.
     */
    bool openCamera(std::string initString) override;

    /**
     * @brief Init camera controller by structure. Can be used instead
     * openCamera(...) method.
     * @param initString Init string. Format depends on camera controller.
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
     * @brief Get camera open status.
     * @return TRUE if the camera is open or FALSE.
     */
    bool isCameraConnected() override;

    /**
     * @brief Set the camera controller param.
     * @param id Param ID.
     * @param value Param value.
     * @return TRUE if the property set or FALSE.
     */
    bool setParam(CameraParam id, float value) override;

    /**
     * @brief Get the camera controller param.
     * @param id Param ID.
     * @return int Param value or -1 of the param not exists.
     */
    float getParam(CameraParam id) override;

    /**
     * @brief Get the camera controller params.
     * @param params reference to CameraParams object.
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
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    bool decodeAndExecuteCommand(uint8_t* data, int size) override;

private:

    /// Parameters structure (default params).
    CameraParams m_params;
};
}
}