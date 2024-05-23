代码需要修改针脚定义

/**
 * @brief LCD SCREEN Function Definition
 */
#define FUNC_LCD_SCREEN_EN          (1)
#define LCD_CTRL_GPIO               BIT(1) // TCA9554_GPIO_NUM_1
#define LCD_RST_GPIO                BIT(2) // TCA9554_GPIO_NUM_2
// #define LCD_CS_GPIO                 BIT(3) // TCA9554_GPIO_NUM_3
// LCD SPI Pins
#define LCD_DC_GPIO                 GPIO_NUM_2
#define LCD_CLK_GPIO                GPIO_NUM_1
#define LCD_MOSI_GPIO               GPIO_NUM_0
#define LCD_CS_GPIO               GPIO_NUM_46
// The LCD pixel number in horizontal and vertical
#define LCD_H_RES                   320
#define LCD_V_RES                   240
#define LCD_SWAP_XY                 (true)
#define LCD_MIRROR_X                (true)
#define LCD_MIRROR_Y                (true)
#define LCD_COLOR_INV               (false)