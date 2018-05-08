/**
 *  Camera related class and structu
 */
#ifndef _CAMERA_H_INCLUDED
#define _CAMERA_H_INCLUDED

static constexpr float CAMERA_FOV_RESET = 60.0f;

enum class CAMERA_MODES
{
    CAM_LOCKED,
    CAM_FREE,
    CAM_DEBUG
};

typedef struct
{
    float x;        /** x pos of camera */
    float y;        /** y pos of camera */
    float z;        /** z pos of camera */
    float fov;      /**< The camera's field of view */

    float pitch;
    float yaw;

    CAMERA_MODES mode;
} camera_t;

/**
 *  Initialise the camera
 */
void cam_init(camera_t& cam, int width, int height);

/**
 *  Refresh the camera's perspective matrix
 */
void cam_refresh(camera_t& cam);

/**
 *  Translate the camera
 */
void cam_translate(camera_t& cam, float dx, float dy, float dz);

/**
 *  Pitch the camera up and down
 */
void cam_pitch(camera_t& cam, float ang);

/**
 *  Yaw the camera left and right
 */
void cam_yaw(camera_t& cam, float ang);

#endif