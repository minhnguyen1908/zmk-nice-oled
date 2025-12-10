#include "output.h"
#include "../assets/custom_fonts.h"
#include <zephyr/kernel.h>

LV_IMG_DECLARE(bt_no_signal);
LV_IMG_DECLARE(bt_unbonded);
LV_IMG_DECLARE(bt);
LV_IMG_DECLARE(usb);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
  /*lv_draw_image_dsc_t img_dsc;*/
  /*lv_draw_image_dsc_init(&img_dsc);*/

  /*lv_canvas_draw_image(canvas, 0, 34, &usb, &img_dsc);*/
  // lv_canvas_draw_image(canvas, 45, 2, &usb, &img_dsc);
    // 1. Layer
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    // 2. Descriptor
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &usb;

    // 3. Coords (10x20 size)
    lv_area_t coords = {0, 34, 0 + 10 - 1, 34 + 20 - 1};

    // 4. Draw (Use lv_draw_image, NOT lv_canvas_draw_image)
    lv_draw_image(&layer, &img_dsc, &coords);
}

static void draw_ble_unbonded(lv_obj_t *canvas) {
  lv_draw_image_dsc_t img_dsc;
  lv_draw_image_dsc_init(&img_dsc);

  // 36 - 39
  lv_canvas_draw_image(canvas, -1, 32, &bt_unbonded, &img_dsc);
  // lv_canvas_draw_image(canvas, 44, 0, &bt_unbonded, &img_dsc);
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
  lv_draw_image_dsc_t img_dsc;
  lv_draw_image_dsc_init(&img_dsc);

  lv_canvas_draw_image(canvas, 4, 32, &bt_no_signal, &img_dsc);
  // lv_canvas_draw_image(canvas, 49, 0, &bt_no_signal, &img_dsc);
}

static void draw_ble_connected(lv_obj_t *canvas) {
  lv_draw_image_dsc_t img_dsc;
  lv_draw_image_dsc_init(&img_dsc);

  lv_canvas_draw_image(canvas, 4, 32, &bt, &img_dsc);
  // lv_canvas_draw_image(canvas, 49, 0, &bt, &img_dsc);
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
  /*
   * WHITOUT BACKGROUND
  lv_draw_rect_dsc_t rect_white_dsc;
  init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
  lv_canvas_draw_rect(canvas, -3, 32, 24, 15, &rect_white_dsc);
  */

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  switch (state->selected_endpoint.transport) {
  case ZMK_TRANSPORT_USB:
    draw_usb_connected(canvas);
    break;

  case ZMK_TRANSPORT_BLE:
    if (state->active_profile_bonded) {
      if (state->active_profile_connected) {
        draw_ble_connected(canvas);
      } else {
        draw_ble_disconnected(canvas);
      }
    } else {
      draw_ble_unbonded(canvas);
    }
    break;
  }
#else
  if (state->connected) {
    draw_ble_connected(canvas);
  } else {
    draw_ble_disconnected(canvas);
  }
#endif
}
