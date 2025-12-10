#include "layer.h"
#include "../assets/custom_fonts.h"
#include <ctype.h>
#include <zephyr/kernel.h>
#include <stdio.h>

// FIX: Removed 'static' to match the header file
void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[14] = {};
    int result;

    if (state->layer_label == NULL) {
        result = snprintf(text, sizeof(text), "Layer %i", state->layer_index);
    } else {
        result = snprintf(text, sizeof(text), "%s", state->layer_label);
        for (int i = 0; text[i] != '\0'; i++) {
            text[i] = toupper(text[i]);
        }
    }

    // FIX: New LVGL 9 Layer Drawing Logic
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    label_dsc.text = text;
    
    // Coords: x=0, y=146, width=68
    lv_area_t coords = {0, 146, 68, 146 + 20}; 
    lv_draw_label(&layer, &label_dsc, &coords);

    // CRITICAL: Finish the layer to prevent crash
    lv_canvas_finish_layer(canvas, &layer);
}
