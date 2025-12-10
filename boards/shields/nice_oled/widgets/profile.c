#include "profile.h"
#include "../assets/custom_fonts.h"
#include <stdio.h>
#include <zephyr/kernel.h>

LV_IMAGE_DECLARE(profiles);

static void draw_inactive_profiles(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    init_image_dsc(&img_dsc, &profiles);

    lv_area_t coords = {0, 137, 0 + profiles.header.w - 1, 137 + profiles.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

static void draw_active_profile(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);

    int offset = state->active_profile_index * 7;
    lv_area_t coords = {0 + offset, 137, 0 + offset + 3, 137 + 3};
    lv_draw_rect(&layer, &rect_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

static void draw_active_profile_text(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_8, LV_TEXT_ALIGN_LEFT);

    char text[14] = {};
    snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);
    
    label_dsc.text = text;
    lv_area_t coords = {25, 32, 25 + 35, 32 + 20}; 
    lv_draw_label(&layer, &label_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_active_profile_text(canvas, state);
    draw_inactive_profiles(canvas, state);
    draw_active_profile(canvas, state);
}
