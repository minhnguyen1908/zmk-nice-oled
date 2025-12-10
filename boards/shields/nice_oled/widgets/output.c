#include "output.h"
#include "../assets/custom_fonts.h"
#include <zephyr/kernel.h>

LV_IMAGE_DECLARE(bt_no_signal);
LV_IMAGE_DECLARE(bt_unbonded);
LV_IMAGE_DECLARE(bt);
LV_IMAGE_DECLARE(usb);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &usb;

    lv_area_t coords = {0, 34, 0 + usb.header.w - 1, 34 + usb.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
}

static void draw_ble_unbonded(lv_obj_t *canvas) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &bt_unbonded;

    lv_area_t coords = {-1, 32, -1 + bt_unbonded.header.w - 1, 32 + bt_unbonded.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &bt_no_signal;

    lv_area_t coords = {4, 32, 4 + bt_no_signal.header.w - 1, 32 + bt_no_signal.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
}

static void draw_ble_connected(lv_obj_t *canvas) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &bt;

    lv_area_t coords = {4, 32, 4 + bt.header.w - 1, 32 + bt.header.h - 1};
    lv_draw_image(&layer, &img_dsc, &coords);
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
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
