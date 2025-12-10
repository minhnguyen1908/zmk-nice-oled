#include "layer.h"
#include "../assets/custom_fonts.h"
#include <stdio.h>
#include <zephyr/kernel.h>

static void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[40] = {};
    const char *label = state->layer_label ? state->layer_label : "BASE";
    snprintf(text, sizeof(text), "LAYER: %s", label);
    
    label_dsc.text = text;
    lv_area_t coords = {0, 146, 68, 146 + 20};
    lv_draw_label(&layer, &label_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer); // <--- CRITICAL FIX
}

void draw_layer_status_screen(lv_obj_t *canvas, const struct status_state *state) {
    draw_layer_status(canvas, state);
}
