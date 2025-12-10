/*#include "layer.h"*/
/*#include "../assets/custom_fonts.h"*/
/*#include <ctype.h> // Para toupper()*/
/*#include <zephyr/kernel.h>*/

/*// MC: better implementation*/
/*void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {*/
  /*[>lv_draw_label_dsc_t label_dsc;<]*/
  /*[>init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono,<]*/
                 /*[>LV_TEXT_ALIGN_LEFT);<]*/

  /*char text[14] = {};*/
  /*int result;*/

  /*if (state->layer_label == NULL) {*/
    /*result = snprintf(text, sizeof(text), "Layer %i", state->layer_index);*/
  /*} else {*/
    /*result = snprintf(text, sizeof(text), "%s", state->layer_label);*/
    /*for (int i = 0; text[i] != '\0'; i++) {*/
      /*// toupper( ... ): This function, found in the ctype.h library, takes a*/
      /*// character as an argument and converts it to its uppercase equivalent.*/
      /*// If the character is already uppercase or not a letter, the function*/
      /*// returns it unchanged.*/
      /*text[i] = toupper(text[i]);*/
    /*}*/
  /*}*/

  /*if (result >= sizeof(text)) {*/
    /*LV_LOG_WARN("truncated");*/
  /*}*/

  /*[>lv_canvas_draw_text(canvas, 0, 146, 68, &label_dsc, text);<]*/
    /*lv_draw_label_dsc_t label_dsc;*/
    /*init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);*/

    /*char text[10] = {};*/
    /*snprintf(text, sizeof(text), "LAYER: %s", state->layer_label ? state->layer_label : "BASE");*/

    /*// NEW LAYER LOGIC*/
    /*lv_layer_t layer;*/
    /*lv_canvas_init_layer(canvas, &layer);*/
    
    /*label_dsc.text = text;*/
    /*lv_area_t coords = {0, 146, 68, 146 + 20}; // Width 68 matches canvas width*/
    /*lv_draw_label(&layer, &label_dsc, &coords);*/
/*}*/

#include "layer.h"
#include "../assets/custom_fonts.h"
#include <stdio.h>
#include <zephyr/kernel.h>

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);

    char text[40] = {}; // Increased size to be safe
    const char *label = state->layer_label ? state->layer_label : "BASE";
    snprintf(text, sizeof(text), "LAYER: %s", label);
    
    label_dsc.text = text;
    lv_area_t coords = {0, 146, 68, 146 + 20};
    lv_draw_label(&layer, &label_dsc, &coords);
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_layer_status_screen(lv_obj_t *canvas, const struct status_state *state) {
    draw_layer_status(canvas, state);
}
