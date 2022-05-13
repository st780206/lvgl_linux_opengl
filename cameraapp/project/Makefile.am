ACLOCAL_AMFLAGS = -I m4
CC = @CC@
CPP = @CPP@
AM_CFLAGS = @CFLAGS@ \
	-Iswitch \
	-lm \
	-lEGL \
	-lGLESv2 \
	-Icamera \
	-Icamera/util \
	-DLV_BUILD_TEST=1 \
	-I${top_srcdir}/project/include \
	-I@KERNEL_DIR@/include/uapi \
	-I@KERNEL_DIR@/include \
	-I@KERNEL_DIR@/include/video/tcc \
	-I@KERNEL_DIR@/drivers/staging/android/uapi
	
#	-lopencv_core \
#	-lopencv_imgproc \
#
	
AM_CPPFLAGS = $(AM_CFLAGS) -rdynamic -g
AM_CXXFLAGS = $(AM_CFLAGS) -rdynamic -g
LIBS = @LIBS@
DEFS = @DEFS@ 
AM_LDFLAGS = -rdynamic -g -Wl,-Map=cameraapp.map

bin_PROGRAMS = cameraapp
cameraapp_SOURCES = main.c

cameraapp_SOURCES += mouse_cursor_icon.c

cameraapp_SOURCES += lvgl/src/core/lv_disp.c 
cameraapp_SOURCES += lvgl/src/core/lv_group.c 
cameraapp_SOURCES += lvgl/src/core/lv_indev.c 
cameraapp_SOURCES += lvgl/src/core/lv_indev_scroll.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_class.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_draw.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_pos.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_scroll.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_style.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_style_gen.c 
cameraapp_SOURCES += lvgl/src/core/lv_obj_tree.c 
cameraapp_SOURCES += lvgl/src/core/lv_event.c 
cameraapp_SOURCES += lvgl/src/core/lv_refr.c 
cameraapp_SOURCES += lvgl/src/core/lv_theme.c 


cameraapp_SOURCES += lvgl/src/draw/lv_draw_arc.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_blend.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_img.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_label.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_line.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_mask.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_rect.c 
cameraapp_SOURCES += lvgl/src/draw/lv_draw_triangle.c 
cameraapp_SOURCES += lvgl/src/draw/lv_img_buf.c 
cameraapp_SOURCES += lvgl/src/draw/lv_img_cache.c 
cameraapp_SOURCES += lvgl/src/draw/lv_img_decoder.c 


cameraapp_SOURCES += lvgl/src/font/lv_font.c 
cameraapp_SOURCES += lvgl/src/font/lv_font_fmt_txt.c 
cameraapp_SOURCES += lvgl/src/font/lv_font_loader.c 

cameraapp_SOURCES += lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_8.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_10.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_12.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_12_subpx.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_14.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_16.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_18.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_20.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_22.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_24.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_26.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_28.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_28_compressed.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_30.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_32.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_34.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_36.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_38.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_40.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_42.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_44.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_46.c
cameraapp_SOURCES += lvgl/src/font/lv_font_montserrat_48.c
cameraapp_SOURCES += lvgl/src/font/lv_font_simsun_16_cjk.c
cameraapp_SOURCES += lvgl/src/font/lv_font_unscii_8.c
cameraapp_SOURCES += lvgl/src/font/lv_font_unscii_16.c


cameraapp_SOURCES += lvgl/src/extra/layouts/flex/lv_flex.c 
cameraapp_SOURCES += lvgl/src/extra/layouts/grid/lv_grid.c 
cameraapp_SOURCES += lvgl/src/extra/themes/default/lv_theme_default.c 
cameraapp_SOURCES += lvgl/src/extra/widgets/spinner/lv_spinner.c
cameraapp_SOURCES += lvgl/src/extra/widgets/keyboard/lv_keyboard.c
cameraapp_SOURCES += lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c
cameraapp_SOURCES += lvgl/src/extra/widgets/tabview/lv_tabview.c
cameraapp_SOURCES += lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c
cameraapp_SOURCES += lvgl/src/extra/widgets/calendar/lv_calendar.c
cameraapp_SOURCES += lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c
cameraapp_SOURCES += lvgl/src/extra/widgets/span/lv_span.c
cameraapp_SOURCES += lvgl/src/extra/widgets/tileview/lv_tileview.c
cameraapp_SOURCES += lvgl/src/extra/widgets/list/lv_list.c
cameraapp_SOURCES += lvgl/src/extra/widgets/msgbox/lv_msgbox.c
cameraapp_SOURCES += lvgl/src/extra/widgets/animimg/lv_animimg.c
cameraapp_SOURCES += lvgl/src/extra/widgets/spinbox/lv_spinbox.c
cameraapp_SOURCES += lvgl/src/extra/widgets/win/lv_win.c
cameraapp_SOURCES += lvgl/src/extra/widgets/led/lv_led.c
cameraapp_SOURCES += lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c
cameraapp_SOURCES += lvgl/src/extra/widgets/meter/lv_meter.c
cameraapp_SOURCES += lvgl/src/extra/widgets/chart/lv_chart.c
cameraapp_SOURCES += lvgl/src/extra/lv_extra.c 


cameraapp_SOURCES += lvgl/src/hal/lv_hal_disp.c 
cameraapp_SOURCES += lvgl/src/hal/lv_hal_indev.c 
cameraapp_SOURCES += lvgl/src/hal/lv_hal_tick.c 


cameraapp_SOURCES += lvgl/src/misc/lv_anim.c
cameraapp_SOURCES += lvgl/src/misc/lv_area.c
cameraapp_SOURCES += lvgl/src/misc/lv_async.c
cameraapp_SOURCES += lvgl/src/misc/lv_bidi.c
cameraapp_SOURCES += lvgl/src/misc/lv_color.c
cameraapp_SOURCES += lvgl/src/misc/lv_fs.c
cameraapp_SOURCES += lvgl/src/misc/lv_gc.c
cameraapp_SOURCES += lvgl/src/misc/lv_ll.c
cameraapp_SOURCES += lvgl/src/misc/lv_log.c
cameraapp_SOURCES += lvgl/src/misc/lv_math.c
cameraapp_SOURCES += lvgl/src/misc/lv_mem.c
cameraapp_SOURCES += lvgl/src/misc/lv_printf.c
cameraapp_SOURCES += lvgl/src/misc/lv_style.c
cameraapp_SOURCES += lvgl/src/misc/lv_style_gen.c
cameraapp_SOURCES += lvgl/src/misc/lv_timer.c
cameraapp_SOURCES += lvgl/src/misc/lv_tlsf.c
cameraapp_SOURCES += lvgl/src/misc/lv_txt.c
cameraapp_SOURCES += lvgl/src/misc/lv_txt_ap.c
cameraapp_SOURCES += lvgl/src/misc/lv_utils.c
	
	
cameraapp_SOURCES += lvgl/src/widgets/lv_arc.c
cameraapp_SOURCES += lvgl/src/widgets/lv_bar.c
cameraapp_SOURCES += lvgl/src/widgets/lv_btn.c
cameraapp_SOURCES += lvgl/src/widgets/lv_btnmatrix.c
cameraapp_SOURCES += lvgl/src/widgets/lv_canvas.c
cameraapp_SOURCES += lvgl/src/widgets/lv_checkbox.c
cameraapp_SOURCES += lvgl/src/widgets/lv_dropdown.c
cameraapp_SOURCES += lvgl/src/widgets/lv_img.c
cameraapp_SOURCES += lvgl/src/widgets/lv_label.c
cameraapp_SOURCES += lvgl/src/widgets/lv_line.c
cameraapp_SOURCES += lvgl/src/widgets/lv_roller.c
cameraapp_SOURCES += lvgl/src/widgets/lv_slider.c
cameraapp_SOURCES += lvgl/src/widgets/lv_switch.c
cameraapp_SOURCES += lvgl/src/widgets/lv_table.c
cameraapp_SOURCES += lvgl/src/widgets/lv_textarea.c


#cameraapp_SOURCES += lvgl/tests/lv_test_assert.c
#cameraapp_SOURCES += lvgl/tests/lv_test_core/lv_test_core.c
#cameraapp_SOURCES += lvgl/tests/lv_test_core/lv_test_font_loader.c
#cameraapp_SOURCES += lvgl/tests/lv_test_core/lv_test_obj.c
#cameraapp_SOURCES += lvgl/tests/lv_test_core/lv_test_style.c


cameraapp_SOURCES += lv_drivers/display/fbdev.c

cameraapp_SOURCES += lv_drivers/indev/evdev.c

cameraapp_SOURCES += lv_demos/src/lv_demo_widgets/assets/img_clothes.c
cameraapp_SOURCES += lv_demos/src/lv_demo_widgets/assets/img_demo_widgets_avatar.c
cameraapp_SOURCES += lv_demos/src/lv_demo_widgets/assets/img_lvgl_logo.c
cameraapp_SOURCES += lv_demos/src/lv_demo_widgets/lv_demo_widgets.c

	