#include "util.h"
#include <ctype.h>
#include <zephyr/kernel.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

// FIX: Safe Rotation Logic for LVGL 9
void rotate_canvas(lv_obj_t *canvas, lv_image_dsc_t *img) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t draw_dsc;
    lv_draw_image_dsc_init(&draw_dsc);
    draw_dsc.src = img;
    
    draw_dsc.rotation = 900; // 90 degrees
    draw_dsc.pivot.x = CANVAS_WIDTH / 2; 
    draw_dsc.pivot.y = CANVAS_WIDTH / 2;

    lv_area_t coords = {0, 0, CANVAS_HEIGHT - 1, CANVAS_WIDTH - 1};
    lv_draw_image(&layer, &draw_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_background(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_BACKGROUND);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_area_t coords = {0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1};
    lv_draw_rect(&layer, &rect_dsc, &coords);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font, lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
}

void init_image_dsc(lv_draw_image_dsc_t *image_dsc, const void *src) {
    lv_draw_image_dsc_init(image_dsc);
    image_dsc->src = src;
}
