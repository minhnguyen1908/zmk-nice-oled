#include "wpm.h"
#include "../assets/custom_fonts.h"
#include <math.h>
#include <zephyr/kernel.h>
#include <stdio.h>

LV_IMAGE_DECLARE(gauge);
LV_IMAGE_DECLARE(grid);

static void draw_gauge(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    init_image_dsc(&img_dsc, &gauge);

    lv_area_t coords = {0, 70, 0 + gauge.header.w - 1, 70 + gauge.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

static void draw_needle(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 1);

    int centerX = 12; 
    int centerY = 90; 
    int offset = 5;   
    int value = state->wpm[9];

    float max = 0;
    for (int i = 0; i < 10; i++) {
        if (state->wpm[i] > max) max = state->wpm[i];
    }
    if (max == 0) max = 100;
    if (value > max) value = max;

    // Fix float/double warnings by using 225.0f etc
    float angleDeg = 225.0f + ((float)value / max) * 90.0f;
    float angleRad = angleDeg * (3.14159f / 180.0f);

    int needleStartX = centerX + (int)(offset * cosf(angleRad));
    int needleStartY = centerY + (int)(offset * sinf(angleRad));
    int needleEndX = centerX + (int)(25.45585f * cosf(angleRad));
    int needleEndY = centerY + (int)(25.45585f * sinf(angleRad));

    line_dsc.p1.x = needleStartX;
    line_dsc.p1.y = needleStartY;
    line_dsc.p2.x = needleEndX;
    line_dsc.p2.y = needleEndY;
    
    lv_draw_line(&layer, &line_dsc);
    
    lv_canvas_finish_layer(canvas, &layer);
}

#if !IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
static void draw_grid(lv_obj_t *canvas) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    init_image_dsc(&img_dsc, &grid);

    lv_area_t coords = {-1, 95, -1 + grid.header.w - 1, 95 + grid.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

static void draw_graph(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 2);
    lv_point_t points[10];

    int max = 0;
    int min = 256;
    for (int i = 0; i < 10; i++) {
        if (state->wpm[i] > max) max = state->wpm[i];
        if (state->wpm[i] < min) min = state->wpm[i];
    }
    int range = max - min;
    if (range == 0) range = 1;

    for (int i = 0; i < 10; i++) {
        points[i].x = 0 + i * 7;
        points[i].y = 97 - (state->wpm[i] - min) * 32 / range;
    }

    for(int i = 0; i < 9; i++) {
        line_dsc.p1 = points[i];
        line_dsc.p2 = points[i+1];
        lv_draw_line(&layer, &line_dsc);
    }
    
    lv_canvas_finish_layer(canvas, &layer);
}
#endif

static void draw_label(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &pixel_operator_mono_12, LV_TEXT_ALIGN_LEFT);

    char wpm_text[10] = {};
    snprintf(wpm_text, sizeof(wpm_text), "%d", state->wpm[9]);
    label_dsc.text = wpm_text;

    // Kept your positioning logic
    int x_pos;
    if (state->wpm[9] < 10) x_pos = 12;
    else if (state->wpm[9] < 100) x_pos = 9;
    else x_pos = 7;
    
    lv_area_t coords = {x_pos, 75, x_pos + 50, 75 + 20};
    lv_draw_label(&layer, &label_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_wpm_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_gauge(canvas, state);
    draw_needle(canvas, state);
#if !IS_ENABLED(CONFIG_NICE_OLED_WIDGET_WPM_LUNA)
    draw_grid(canvas);
    draw_graph(canvas, state);
#endif
    draw_label(canvas, state);
}
