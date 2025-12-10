/*
#include "util.h"
#include <ctype.h>
#include <zephyr/kernel.h>

void to_uppercase(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
  }
}

/*void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[]) {*/
  /*static lv_color_t cbuf_tmp[CANVAS_HEIGHT * CANVAS_HEIGHT];*/
  /*memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));*/

  /*lv_img_dsc_t img;*/
  /*img.data = (void *)cbuf_tmp;*/
  /*img.header.cf = LV_COLOR_FORMAT_NATIVE; //LV_IMG_CF_TRUE_COLOR; change to matched with new version 4.1.0.*/
  /*img.header.w = CANVAS_HEIGHT;*/
  /*img.header.h = CANVAS_HEIGHT;*/

  /*lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);*/
  /*[>lv_canvas_transform(canvas, &img, 900, LV_SCALE_NONE, -1, 0,<]*/
                      /*[>CANVAS_HEIGHT / 2, CANVAS_HEIGHT / 2, false);<]*/
/*}

void rotate_canvas(lv_obj_t *canvas, lv_image_dsc_t *img) {
    (void)canvas;
    (void)img;
}

void draw_background(lv_obj_t *canvas) {
  lv_draw_rect_dsc_t rect_black_dsc;
  init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

  /*lv_canvas_draw_rect(canvas, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT,*/
                      /*&rect_black_dsc);
    // 1. Declare and Init the descriptor
    lv_draw_rect_dsc_t draw_dsc;
    init_rect_dsc(&draw_dsc, LVGL_BACKGROUND);

    // 2. Setup Layer
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // 3. Define Area
    lv_area_t coords = {0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1};

    // 4. Draw using the variable 'draw_dsc'
    lv_draw_rect(&layer, &draw_dsc, &coords);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color,
                    const lv_font_t *font, lv_text_align_t align) {
  lv_draw_label_dsc_init(label_dsc);
  label_dsc->color = color;
  label_dsc->font = font;
  label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
  lv_draw_rect_dsc_init(rect_dsc);
  rect_dsc->bg_color = bg_color;
}

/*void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color,*/
                   /*uint8_t width) {*/
  /*lv_draw_line_dsc_init(line_dsc);*/
  /*line_dsc->color = color;*/
  /*line_dsc->width = width;*/
/*}

// FIX: New helper for image descriptors
void init_image_dsc(lv_draw_image_dsc_t *image_dsc, const void *src) {
    lv_draw_image_dsc_init(image_dsc);
    image_dsc->src = src;
}*/

#include "util.h"
#include <ctype.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void rotate_canvas(lv_obj_t *canvas, lv_image_dsc_t *img) {
    // LVGL 9 removed direct canvas transformation.
    (void)canvas;
    (void)img;
}

void draw_background(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t draw_dsc;
    init_rect_dsc(&draw_dsc, LVGL_BACKGROUND);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_area_t coords = {0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1};
    lv_draw_rect(&layer, &draw_dsc, &coords);
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

// THIS WAS MISSING!
void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
    line_dsc->round_start = 1;
    line_dsc->round_end = 1;
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color,
                    const lv_font_t *font, lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_image_dsc(lv_draw_image_dsc_t *image_dsc, const void *src) {
    lv_draw_image_dsc_init(image_dsc);
    image_dsc->src = src;
}
