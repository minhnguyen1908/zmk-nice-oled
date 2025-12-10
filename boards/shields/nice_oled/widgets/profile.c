#include "profile.h"
// use custom_fonts.h only for the draw_active_profile_text function
#include "../assets/custom_fonts.h"
#include <stdio.h>
#include <zephyr/kernel.h>

LV_IMAGE_DECLARE(profiles);

static void draw_inactive_profiles(lv_obj_t *canvas,
                                   const struct status_state *state) {
  /*lv_draw_image_dsc_t img_dsc;*/
  /*lv_draw_image_dsc_init(&img_dsc);*/

  /*lv_canvas_draw_img(canvas, 0, 137, &profiles, &img_dsc);*/
  // lv_canvas_draw_img(canvas, 18, 129, &profiles, &img_dsc);
    //Fix: New Layer Logic for Image.
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &profiles;

    lv_area_t coords = {0, 137, 0 + profiles.header.w - 1, 137 + profiles.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
}

static void draw_active_profile(lv_obj_t *canvas,
                                const struct status_state *state) {
  lv_draw_rect_dsc_t rect_white_dsc;
  init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

  int offset = state->active_profile_index * 7;

  /*lv_canvas_draw_rect(canvas, 0 + offset, 137, 3, 3, &rect_white_dsc);*/
  // lv_canvas_draw_rect(canvas, 18 + offset, 129, 3, 3, &rect_white_dsc);
    // FIX: new Layer logic for Rectangle
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_color = lv_color_white(); // Assuming foreground is white

    int offset = state->active_profile_index * 7;

    // Draw a 3x3 rectangle
    lv_area_t coords = {0 + offset, 137, 0 + offset + 3, 137 + 3};
    lv_draw_rect(&layer, &rect_dsc, &coords);
}

// MC: mejor implementación
static void draw_active_profile_text(lv_obj_t *canvas,
                                     const struct status_state *state) {
  // new label_dsc
  lv_draw_label_dsc_t label_dsc;
  init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_8,
                 LV_TEXT_ALIGN_LEFT);

  // buffer size should be enough for largest number + null character
  char text[14] = {};
  snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);

  /*lv_canvas_draw_text(canvas, 25, 32, 35, &label_dsc, text);*/
    //FIX: New Layer Logic for Text
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_8, LV_TEXT_ALIGN_LEFT);

    char text[14] = {};
    snprintf(text, sizeof(text), "%d", state->active_profile_index + 1);

    label_dsc.text = text;
    lv_area_t coords = {25, 32, 25 + 35, 32 + 20}; // Approx height
    lv_draw_label(&layer, &label_dsc, &coords);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
  draw_active_profile_text(canvas, state);
  draw_inactive_profiles(canvas, state);
  draw_active_profile(canvas, state);
}
