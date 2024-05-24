/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-05-16 23:30:13
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 00:14:43
 */

#ifndef __MAIN__
#define __MAIN__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        VOICE_RECOGNITION_STATE,
        FACE_RECOGNITION_STATE,
        RECORDING_STATE,
        VOICE_RECOGNITION_STOP,
        FACE_RECOGNITION_STOP,
        RECORDING_STOP
    } SystemState;

    void switch_event_status(int state);

#ifdef __cplusplus
}
#endif

#endif
