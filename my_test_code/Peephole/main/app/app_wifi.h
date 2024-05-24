/*
 * @Author: 都建民
 * @Date: 2024-03-20 02:16:59
 * @Last Modified by: dujianmin qq群 26875961
 * @Last Modified time: 2024-03-21 13:52:36
 */

#ifndef _APP_WIFI_H_
#define _APP_WIFI_H_

#define WIFI_CONNECTED_BIT_G (1 << 0) 
#define WIFI_STOP_BIT_G (1 << 1) 
#define WIFI_STANDBY_BIT_G (1 << 2) 
#ifdef __cplusplus
extern "C"
{
#endif

    // void app_wifi_main();
    void wifi_task(void *pvParameters);
#ifdef __cplusplus
}
#endif

#endif
