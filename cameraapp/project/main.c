/* Copyright (c) 2020 Alpine Electronics (China) Co. LTD.All Rights Reserved.*/
/* File Name   :main.c                                                       */
/* Date        :2020/09/04                                                   */
/* Author      :tsong                                                        */
/* Model       :Camera                                                       */
/* Description :camera main source file                                      */
/*---------------------------------------------------------------------------*/
/*Revision History                                                           */
/*No       Date        Revised by            Function Name                   */
/*0001     20200904    tsong[CHS]            NEW                             */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <math.h>
#include <sys/time.h>
#include <signal.h>
#include <termios.h>

#include <execinfo.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/select.h>

//#include "model.h"

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_drv_conf.h"
#include "lv_demos/lv_demo.h"

#include "lvgl/tests/lv_test_core/lv_test_core.h"

//static int slog_level = -1;
//static int log_level = -1;
//static int debug_cmd = 0;

//#define DISP_BUF_SIZE (80 * LV_HOR_RES_MAX)

void out_stack(char *sig);

/* Function Name :signal_handler                                             */
/* Date          :20201102                                                   */
/* Author        :tsong[CHS]                                                 */
/* Description   :                                                           */
/* Argument      :                                                           */
/* Return Code   :void                                                       */
/*---------------------------------------------------------------------------*/
/*Revision History                                                           */
/*No       Date        Revised by            Function Name                   */
/*---------------------------------------------------------------------------*/
void signal_handler(int sig)
{

    char signal_str6[] = "SIGABRT(6)";
    char signal_str11[] = "SIGSEGV(11)";
    switch (sig) {
    case SIGABRT: /* 6 */
        {
            out_stack(signal_str6);
        }
        break;
    case SIGSEGV: /* 11 */
        {
            out_stack(signal_str11);
        }
        break;

//    default:
//        camera_debug("signal is wrong");
//        break;
    }
    exit(0);
}

void out_stack(char *sig)
{
    void *array[128];
    int size;
    char **ncpstrings;
    int i;

    printf("%s\n", sig);
    size = backtrace (array, 128);
    ncpstrings = backtrace_symbols (array, size);
    if (NULL == ncpstrings)
    {
        printf("backtrace_symbols\n");
        return ;
    }

    for (i = 0; i < size; i++)
    {
        printf("======>>>>> %s\n",ncpstrings[i]);
    }

    free(ncpstrings);
}

/* Function Name :parse_args                                                 */
/* Date          :20201102                                                   */
/* Author        :tsong[CHS]                                                 */
/* Description   :                                                           */
/* Argument      :                                                           */
/* Return Code   :void                                                       */
/*---------------------------------------------------------------------------*/
/*Revision History                                                           */
/*No       Date        Revised by            Function Name                   */
/*---------------------------------------------------------------------------*/
int32_t parse_args(int32_t argc, char *argv[])
{
    static struct option        long_opt[]  = {
        // long-name, param, variable, short-name or init-val
        {"slog",     1,  NULL,   (int32_t)'s'},
        {"log",      1,  NULL,   (int32_t)'l'},
        {"debug",    1,  NULL,   (int32_t)'d'},
    };
    int32_t             ret     = 0;

//    while (1) {
//        int32_t     c       = 0;
//        int32_t     option_idx  = 0;
//        const char  *name       = NULL;
//        int32_t     arg     = 0;
//
//        c = getopt_long(argc, argv, "s:l:d:u:t", long_opt,
//            &option_idx);
//        if (c == -1) {
//            break;
//        }
//
//        switch ((int32_t)c) {
//        case (int32_t)'s':
//            if (optarg == NULL) {
////                camera_debug("optarg is NULL");
//                ret = -1;
//            } else {
//                slog_level = atoi(optarg);
//            }
//            break;
//        case (int32_t)'l':
//            if (optarg == NULL) {
////                camera_debug("optarg is NULL");
//                ret = -1;
//            } else {
//                log_level = atoi(optarg);
//            }
//            break;
//        case (int32_t)'d':
//            if (optarg == NULL) {
////                camera_debug("optarg is NULL");
//                ret = -1;
//            } else {
//                debug_cmd = 1;
//            }
//            break;
//        default:
////            camera_debug("invalid argument: optarg[%s]", optarg);
//            ret = -1;
//            break;
//        }
//    }

    return ret;
}

//#define HOR_RES 1280
#define HOR_RES 1920
#define VER_RES 720

static void hal_init(void);
static void dummy_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

//lv_color_t test_fb[HOR_RES * VER_RES];
#define DISP_BUF_SIZE (HOR_RES * VER_RES)
#define LV_BUF_SIZE DISP_BUF_SIZE

static lv_color_t lvbuf1[LV_BUF_SIZE];
static lv_color_t lvbuf2[LV_BUF_SIZE];

// lvgl 7.0
//static lv_disp_buf_t disp_buf;
// lvgl 8.0
static lv_disp_draw_buf_t disp_buf;

/* Function Name :main                                                       */
/* Date          :20200904                                                   */
/* Author        :tsong[CHS]                                                 */
/* Description   :camera main entry                                          */
/* Argument      :                                                           */
/* Return Code   :                                                           */
/*---------------------------------------------------------------------------*/
/*Revision History                                                           */
/*No       Date        Revised by            Function Name                   */
/*---------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{

    signal(SIGABRT, signal_handler);
    signal(SIGSEGV, signal_handler);

    /*LittlevGL init*/
    lv_init();

#ifdef USE_FBDEV
    /*Linux frame buffer device init*/
    fbdev_init();
#endif


    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    //hal_init();

//    //lv_color_t * disp_buf1 = (lv_color_t *)malloc(LV_HOR_RES * LV_VER_RES * sizeof(lv_color_t));
//    lv_color_t disp_buf1[HOR_RES * VER_RES];
//
//    static lv_disp_draw_buf_t draw_buf;
//    //lv_disp_draw_buf_init(&draw_buf, disp_buf1, NULL, LV_HOR_RES * LV_VER_RES);
//    lv_disp_draw_buf_init(&draw_buf, disp_buf1, NULL, HOR_RES * VER_RES);
//
//    static lv_disp_drv_t disp_drv;
//    lv_disp_drv_init(&disp_drv);
//    disp_drv.draw_buf = &draw_buf;
//    disp_drv.flush_cb = dummy_flush_cb;
//    disp_drv.hor_res = HOR_RES;
//    disp_drv.ver_res = VER_RES;
//    disp_drv.full_refresh = 1;
//    lv_disp_drv_register(&disp_drv);
//
//    LV_LOG_INFO(" ========   disp_drv====  %p    ========================== ", &disp_drv);
//    LV_LOG_INFO(" ========   draw_buf====  %p    ========================== ", &draw_buf);




/*
    static lv_fs_drv_t drv;
    lv_fs_drv_init(&drv);                     Basic initialization

    drv.letter = 'F';                         An uppercase letter to identify the drive
    drv.open_cb = open_cb;                 Callback to open a file
    drv.close_cb = close_cb;               Callback to close a file
    drv.read_cb = read_cb;                 Callback to read a file
    drv.seek_cb = seek_cb;                 Callback to seek in a file (Move cursor)
    drv.tell_cb = tell_cb;                 Callback to tell the cursor position

    lv_fs_drv_register(&drv);                 Finally register the drive
*/




    /*A small buffer for LittlevGL to draw the screen's content*/
    //static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    //static lv_disp_buf_t disp_buf;
    //static lv_disp_draw_buf_t disp_buf;
    //lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    //lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    //lv_disp_drv_t disp_drv;
    //lv_disp_drv_init(&disp_drv);

    //disp_drv.hor_res = HOR_RES;
    //disp_drv.ver_res = VER_RES;

    //disp_drv.buffer   = &disp_buf;
    //disp_drv.draw_buf   = &disp_buf;
    //disp_drv.flush_cb = fbdev_flush;
    //lv_disp_drv_register(&disp_drv);

    // Initialize `disp_buf` with the display buffer(s)
    // lvgl 7.0
    //lv_disp_buf_init(&disp_buf, lvbuf1, lvbuf2, LV_BUF_SIZE);
    // lvgl 8.0
    lv_disp_draw_buf_init(&disp_buf, lvbuf1, lvbuf2, LV_BUF_SIZE);

    // Initialize and register a display driver
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = HOR_RES;
    disp_drv.ver_res = VER_RES;

    disp_drv.flush_cb = fbdev_flush;    // flushes the internal graphical buffer to the frame buffer
    // lvgl 7.0
    //disp_drv.buffer = &disp_buf;        // set teh display buffere reference in the driver
    // lvgl 8.0
    disp_drv.draw_buf   = &disp_buf;

    lv_disp_drv_register(&disp_drv);



    evdev_init();


    // Initialize and register a pointer device driver
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;    // defined in lv_drivers/indev/evdev.h
    lv_indev_drv_register(&indev_drv);

    //lv_indev_t *mouse = lv_indev_next(NULL);
    lv_indev_t *mouse = lv_indev_get_next(NULL);
//    lv_obj_t *cursor = lv_label_create(lv_scr_act(), NULL);
//    lv_label_set_recolor(cursor, true);
//    lv_label_set_text(cursor, "#ff0000 .cursor");
//    lv_indev_set_cursor(mouse, cursor);

    LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    //lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    //lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
    lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

    /*
      * Demos, benchmarks, and tests.
      *
      * Uncomment any one (and only one) of the functions below to run that
      * item.
      */
    LV_LOG_WARN("demo start.");
     //lv_test_core();
     lv_demo_widgets();
     //lv_demo_keypad_encoder();
     //lv_demo_benchmark();
     //lv_demo_stress();
     //lv_demo_music();
     //lv_demo_printer();

     //lv_ex_get_started_1();
     //lv_ex_get_started_2();
     //lv_ex_get_started_3();

     //lv_ex_style_1();
     //lv_ex_style_2();
     //lv_ex_style_3();
     //lv_ex_style_4();
     //lv_ex_style_5();
     //lv_ex_style_6();
     //lv_ex_style_7();
     //lv_ex_style_8();
     //lv_ex_style_9();
     //lv_ex_style_10();
     //lv_ex_style_11();

     /*
      * There are many examples of individual widgets found under the
      * lv_examples/src/lv_ex_widgets directory.  Here are a few sample test
      * functions.  Look in that directory to find all the rest.
      */
      //lv_ex_arc_1();
      //lv_ex_cpicker_1();
      //lv_ex_gauge_1();
      //lv_ex_img_1();
      //lv_ex_tileview_1();

     //=======================================
     //  lv_example_switch_1();
     //  lv_example_calendar_1();
     //  lv_example_btnmatrix_2();
     //  lv_example_checkbox_1();
     //  lv_example_colorwheel_1();
     //  lv_example_chart_6();
     //  lv_example_table_2();
     //  lv_example_scroll_2();
     //  lv_example_textarea_1();
     //  lv_example_msgbox_1();
     //  lv_example_dropdown_2();
     //  lv_example_btn_1();
     //  lv_example_scroll_1();
     //  lv_example_tabview_1();
     //  lv_example_tabview_1();
     //  lv_example_flex_3();
     //  lv_example_label_1();

     LV_LOG_WARN("demo end.");

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {

        LV_LOG_INFO("main while --->> ");
        //lv_tick_inc(10); /*Tell LittelvGL that 5 milliseconds were elapsed*/
        lv_timer_handler();

        usleep(100000);
        //sleep(1);

        LV_LOG_INFO("main sleep 100ms --->> ");
    }

    return 0;
}


static void * open_cb(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    (void) drv;
    (void) mode;

    FILE * fp = fopen(path, "rb"); // only reading is supported

    return fp;
}

static lv_fs_res_t close_cb(lv_fs_drv_t * drv, void * file_p)
{
    (void) drv;

    fclose(file_p);
    return LV_FS_RES_OK;
}

static lv_fs_res_t read_cb(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    (void) drv;

    *br = fread(buf, 1, btr, file_p);
    return (*br <= 0) ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t seek_cb(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t w)
{
    (void) drv;

    uint32_t w2;
    switch(w) {
    case LV_FS_SEEK_SET:
        w2 = SEEK_SET;
        break;
    case LV_FS_SEEK_CUR:
        w2 = SEEK_CUR;
        break;
    case LV_FS_SEEK_END:
        w2 = SEEK_END;
        break;
    default:
        w2 = SEEK_SET;
    }

    fseek (file_p, pos, w2);

    return LV_FS_RES_OK;
}

static lv_fs_res_t tell_cb(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    (void) drv;

    *pos_p = ftell(file_p);

    return LV_FS_RES_OK;
}


static void hal_init(void)
{
    static lv_disp_draw_buf_t draw_buf;
    //lv_color_t * disp_buf1 = (lv_color_t *)malloc(LV_HOR_RES * LV_VER_RES * sizeof(lv_color_t));
    lv_color_t * disp_buf1 = (lv_color_t *)malloc(HOR_RES * VER_RES * sizeof(lv_color_t));

    //lv_disp_draw_buf_init(&draw_buf, disp_buf1, NULL, LV_HOR_RES * LV_VER_RES);
    lv_disp_draw_buf_init(&draw_buf, disp_buf1, NULL, HOR_RES * VER_RES);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = dummy_flush_cb;
    disp_drv.hor_res = HOR_RES;
    disp_drv.ver_res = VER_RES;
    //disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);

    LV_LOG_INFO(" ========   disp_drv====  %p    ========================== ", &disp_drv);
    LV_LOG_INFO(" ========   draw_buf====  %p    ========================== ", &draw_buf);


    static lv_fs_drv_t drv;
    lv_fs_drv_init(&drv);                     /*Basic initialization*/

    drv.letter = 'F';                         /*An uppercase letter to identify the drive*/
    drv.open_cb = open_cb;                 /*Callback to open a file*/
    drv.close_cb = close_cb;               /*Callback to close a file*/
    drv.read_cb = read_cb;                 /*Callback to read a file*/
    drv.seek_cb = seek_cb;                 /*Callback to seek in a file (Move cursor)*/
    drv.tell_cb = tell_cb;                 /*Callback to tell the cursor position*/

    lv_fs_drv_register(&drv);                 /*Finally register the drive*/
}
#include <stdio.h>

static void dummy_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
//    LV_UNUSED(area);
//    LV_UNUSED(color_p);
//
//    memcpy(test_fb, color_p, lv_area_get_size(area) * sizeof(lv_color_t));
//
//    lv_disp_flush_ready(disp_drv);
}

uint32_t custom_tick_get(void)
{

//    static uint64_t start_ms = 0;
//    if(start_ms == 0) {
//        struct timeval tv_start;
//        gettimeofday(&tv_start, NULL);
//        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
//    }
//
//    struct timeval tv_now;
//    gettimeofday(&tv_now, NULL);
//    uint64_t now_ms;
//    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;
//
//    uint32_t time_ms = now_ms - start_ms;

    long nslSrtAbsTime_usec = 0;

    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    nslSrtAbsTime_usec = ts.tv_sec*1000000 + ts.tv_nsec/1000;

    uint32_t time_ms = nslSrtAbsTime_usec;

    return time_ms;
}
