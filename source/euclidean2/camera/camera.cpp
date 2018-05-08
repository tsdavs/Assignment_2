/**
 *  Implementation of camera.hpp
 */
#include "euclidean2/camera/camera.hpp"
#include "euclidean2/math/angle.hpp"

#include "platform.hpp"

void cam_init(camera_t& cam, int width, int height)
{
    // Reset the camera to the origin
    cam.x = 0.0f;
    cam.y = 0.0f;
    cam.z = 0.0f;
    cam.fov = CAMERA_FOV_RESET;

    cam.pitch = 0.0f;
    cam.yaw = 0.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam.fov, static_cast<GLfloat>(width/height), 0.0001, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void cam_refresh(camera_t& cam)
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam.fov, static_cast<GLfloat>(width/height), 0.0001, 1000.0f);
}

void cam_translate(camera_t& cam, float dx, float dy, float dz)
{
    cam.x += dx;
    cam.y += dy;
    cam.z -= dz;
}

void cam_pitch(camera_t& cam, float ang)
{
    cam.pitch += ang;
}

void cam_yaw(camera_t& cam, float ang)
{
    cam.yaw += ang;
}