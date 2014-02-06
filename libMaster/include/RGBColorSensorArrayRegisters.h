#ifndef _RGB_COLOR_SENSOR_ARRAY_REGISTERS_H_
#define _RGB_COLOR_SENSOR_ARRAY_REGISTERS_H_

/*
 * This 1 byte register is R/W
 * Read:
 *  [0] - 1 if the RGB Color Sensor Array is in free-running
 *  mode and has exclusive control over the LEDS,
 *  0 if free-running mode is disabled and the
 *  user is free to control the LEDS through the LEDS register
 *  [7:1] - Reserved
 * Write:
 *  [0] - 1 to enter free-running mode, 0 to disable(default)
 *  [7:1] - Reserved(Write 0)
 */
#define RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS 0x10

/*
 * This 10 byte register is R
 * ^Data is only valid if free-running mode is enabled
 * Read:
 *  Byte [0] - Sensor #0, Red Channel
 *  Byte [1] - Sensor #0, Green Channel
 *  Byte [2] - Sensor #0, Blue Channel
 *  Byte [3] - Sensor #1, Red Channel
 *  Byte [4] - Sensor #1, Green Channel
 *  Byte [5] - Sensor #1, Blue Channel
 *  Byte [6] - Sensor #2, Red Channel
 *  Byte [7] - Sensor #2, Green Channel
 *  Byte [8] - Sensor #2, Blue Channel
 *  Byte [9] - Defects
      [0] - 1 if Sensor #0 is looking at a defect, 0 looking at surface
      [1] - 1 if Sensor #1 is looking at a defect, 0 looking at surface
      [2] - 1 if Sensor #2 is looking at a defect, 0 looking at surface
 */
#define RGB_COLOR_SENSOR_ARRAY_REGISTER_DATA 0x11

/*
 * This 1 byte register is R/W
 * ^Writes are only valid when free running mode is disabled
 * Read:
 *  [1:0] - 0: led 0 is off, 1: led 0 is on, 2: led 0 500 ms blink, 3 led 0 undefined state
 *  [3:2] - 0: led 1 is off, 1: led 1 is on, 2: led 1 500 ms blink, 3 led 1 undefined state
 *  [5:4] - 0: led 2 is off, 1: led 2 is on, 2: led 2 500 ms blink, 3 led 2 undefined state
 *  [7:6] - Reserved
 * Write:
    [1:0] - 0: turn led 0 off, 1: turn led 0 on, 2: turn led 0 500 ms blink, 3: don't change
    [3:2] - 0: turn led 1 off, 1: turn led 1 on, 2: turn led 1 500 ms blink, 3: don't change
    [5:4] - 0: turn led 2 off, 1: turn led 2 on, 2: turn led 2 500 ms blink, 3: don't change
    [7:6] - Reserved(Write 0)
 */
#define RGB_COLOR_SENSOR_ARRAY_REGISTER_LEDS 0x12

#endif
