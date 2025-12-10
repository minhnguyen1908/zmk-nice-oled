#include "util.h"
#include <ctype.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void rotate_canvas(lv_obj_t *canvas, lv_image_dsc_t *img) {
    // 1. Create a layer for the canvas
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // 2. Configure drawing descriptor for rotation
    lv_draw_image_dsc_t draw_dsc;
    lv_draw_image_dsc_init(&draw_dsc);
    draw_dsc.src = img;
    
    // Rotation is in 0.1 degree units (900 = 90 degrees)
    draw_dsc.rotation = 900; 
    
    // Set pivot point to the center of the destination area
    // Adjust these based on your specific screen offsets if needed
    draw_dsc.pivot.x = CANVAS_HEIGHT / 2; 
    draw_dsc.pivot.y = CANVAS_WIDTH / 2;

    // 3. Define the destination area
    // Note: We are drawing onto the physical horizontal screen now
    lv_area_t coords = {0, 0, CANVAS_HEIGHT - 1, CANVAS_WIDTH - 1};

    // 4. Draw and Finish
    lv_draw_image(&layer, &draw_dsc, &coords);
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_background(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t draw_dsc;
    init_rect_dsc(&draw_dsc, LVGL_BACKGROUND);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_area_t coords = {0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1};
    lv_draw_rect(&layer, &draw_dsc, &coords);
    
    // CRITICAL FIX: Finish the layer!
    lv_canvas_finish_layer(canvas, &layer);
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

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
