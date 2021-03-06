#include "window.h"
#include "priv.h"

#include <stdlib.h>
#include <string.h>

#include "ui/root.h"
#include "ui/fonts.h"
#include "backend/computer_manager.h"

static nk_bool nk_filter_ip(const struct nk_text_edit *box, nk_rune unicode);

void _manual_add_window(struct nk_context *ctx)
{
    static char text[64];
    static int text_len;

    const char *message = "Enter the IP address of your GameStream PC:";
    struct nk_borders dec_size = nk_style_window_get_decoration_size(&ctx->style, NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR);
    int dialog_width = 330 * NK_UI_SCALE, message_width = dialog_width - dec_size.l - dec_size.r;
    static int message_height = 0;
    if (!message_height)
    {
        message_height = nk_text_wrap_measure_height(ctx, message_width, message, strlen(message)) + 1;
    }

    int dialog_height = dec_size.t + message_height +
                        ctx->style.window.spacing.y +
                        30 * NK_UI_SCALE +
                        ctx->style.window.spacing.y +
                        5 * NK_UI_SCALE +
                        ctx->style.window.spacing.y +
                        30 * NK_UI_SCALE +
                        dec_size.b;
    struct nk_rect s = nk_rect_centered(ui_display_width, ui_display_height, dialog_width, dialog_height);
    if (nk_begin(ctx, "Add PC Manually", s, NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, message_height, 1);
        nk_label_wrap(ctx, message);
        nk_layout_row_dynamic_s(ctx, 30, 1);
        nk_edit_string(ctx, NK_EDIT_FIELD, text, &text_len, 64, nk_filter_ip);
        nk_layout_row_dynamic_s(ctx, 3, 0);

        nk_layout_row_template_begin_s(ctx, 30);
        nk_layout_row_template_push_variable_s(ctx, 10);
        nk_layout_row_template_push_static_s(ctx, 80);
        nk_layout_row_template_push_static_s(ctx, 80);
        nk_layout_row_template_end(ctx);

        nk_spacing(ctx, 1);
        if (nk_button_label(ctx, "Cancel"))
        {
            _launcher_show_manual_pair = false;
        }
        if (nk_button_label(ctx, "OK"))
        {
            char *addr = malloc(text_len + 1);
            strncpy(addr, text, text_len);
            addr[text_len - 1] = '\0';
            pcmanager_manual_add(addr);
        }
    }
    nk_end(ctx);
}

nk_bool nk_filter_ip(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') &&
        (unicode < 'a' || unicode > 'f') &&
        (unicode < 'A' || unicode > 'F') &&
        unicode != ':' && unicode != '.')
        return nk_false;
    else
        return nk_true;
}

void _pairing_window(struct nk_context *ctx)
{
    const char *message = "Please enter pin below on your GameStream PC. This dialog will close when pairing is completed.";
    struct nk_borders dec_size = nk_style_window_get_decoration_size(&ctx->style, NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR);
    int dialog_width = 330 * NK_UI_SCALE, message_width = dialog_width - dec_size.l - dec_size.r;
    static int message_height = 0;
    if (!message_height)
    {
        message_height = nk_text_wrap_measure_height(ctx, message_width, message, strlen(message)) + 1;
    }
    int dialog_height = dec_size.t + message_height + ctx->style.window.spacing.y + 50 * NK_UI_SCALE + 12 * NK_UI_SCALE + dec_size.b;
    struct nk_rect s = nk_rect_centered(ui_display_width, ui_display_height, dialog_width, dialog_height);
    if (nk_begin(ctx, "Pairing", s, NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, message_height, 1);
        nk_label_wrap(ctx, message);
        nk_layout_row_dynamic_s(ctx, 50, 1);
        nk_style_push_font(ctx, &font_num_40->handle);
        nk_label(ctx, pairing_computer_state.pin, NK_TEXT_CENTERED);
        nk_style_pop_font(ctx);
    }
    nk_end(ctx);
}