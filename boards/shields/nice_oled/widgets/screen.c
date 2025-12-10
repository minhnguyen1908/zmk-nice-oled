#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/keymap.h>
#include <zmk/usb.h>
#include <zmk/wpm.h>

#include "battery.h"
#include "layer.h"
#include "output.h"
#include "profile.h"
#include "screen.h"
#include "wpm.h"

// Temporarily disable extra widgets until we confirm stability
// #include "luna.h"
// #include "modifiers.h"
// #include "hid_indicators.h"

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

static void draw_canvas(lv_obj_t *widget, lv_color_t cbuf[], const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);

    draw_background(canvas);
    draw_output_status(canvas, state);
    draw_battery_status(canvas, state);
    draw_wpm_status(canvas, state);
    draw_profile_status(canvas, state);
    draw_layer_status(canvas, state);

    // FIX: Wrap buffer for safe rotation (Prevents Crash!)
    lv_image_dsc_t temp_img = {
        .header.cf = LV_COLOR_FORMAT_NATIVE,
        .header.w = CANVAS_WIDTH,
        .header.h = CANVAS_HEIGHT,
        .data = (const uint8_t *)cbuf,
        .data_size = CANVAS_WIDTH * CANVAS_HEIGHT * sizeof(lv_color_t),
    };

    rotate_canvas(canvas, &temp_img);
}

// ... (Keep your existing Setters: set_battery_status, set_layer_status, etc.) ...
// PLEASE COPY THE SETTERS FROM YOUR PREVIOUS FILE OR ASK ME IF YOU NEED THEM RE-PASTED

// --- Init ---
int zmk_widget_screen_init(struct zmk_widget_screen *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, CANVAS_HEIGHT, CANVAS_WIDTH); // Physical Dimensions

    lv_obj_t *canvas = lv_canvas_create(widget->obj);
    lv_obj_align(canvas, LV_ALIGN_TOP_LEFT, 0, 0);
    
    // FIX: Use NATIVE format
    lv_canvas_set_buffer(canvas, widget->cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_NATIVE);

    sys_slist_append(&widgets, &widget->node);
    
    // Init widgets
    widget_battery_status_init();
    widget_layer_status_init();
    widget_output_status_init();
    widget_wpm_status_init();

    return 0;
}

lv_obj_t *zmk_widget_screen_obj(struct zmk_widget_screen *widget) { return widget->obj; }
