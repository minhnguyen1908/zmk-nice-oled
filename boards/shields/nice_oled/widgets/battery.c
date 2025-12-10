#include "battery.h"
#include "../assets/custom_fonts.h"
#include <zephyr/kernel.h>
#include <stdio.h>

LV_IMAGE_DECLARE(bolt);

static void draw_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[10] = {};
    sprintf(text, "%i%%", state->battery);
    label_right_dsc.text = text;

    lv_area_t coords = {0, 50, 42, 50 + 20}; 
    lv_draw_label(&layer, &label_right_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

static void draw_charging_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    init_image_dsc(&img_dsc, &bolt);

    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[10] = {};
    sprintf(text, "%i", state->battery);
    label_right_dsc.text = text;

    lv_area_t text_coords = {0, 50, 35, 70};
    lv_draw_label(&layer, &label_right_dsc, &text_coords);

    lv_area_t img_coords = {25, 50, 25 + bolt.header.w - 1, 50 + bolt.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &img_coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    if (state->charging) {
        draw_charging_level(canvas, state);
    } else {
        draw_level(canvas, state);
    }
}
