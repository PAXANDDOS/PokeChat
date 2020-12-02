#include "../inc/client.h"

char* avatar_random() {
    srand(time(NULL));                  // Initialization, should only be called once.
    int pick = rand() % 45;         // Returns a pseudo-random integer between 0 and RAND_MAX.

    char *avatar = "client/data/avatars/luna_PAXANDDOS.png";
    switch(pick) {
        case 1: avatar = "client/data/avatars/Arbok.png"; break;
        case 2: avatar = "client/data/avatars/Coffing.png"; break;
        case 3: avatar = "client/data/avatars/Cresselia.png"; break;
        case 4: avatar = "client/data/avatars/Delcatty.png"; break;
        case 5: avatar = "client/data/avatars/Deoxys.png"; break;
        case 6: avatar = "client/data/avatars/Dewgong.png"; break;
        case 7: avatar = "client/data/avatars/Dialga.png"; break;
        case 8: avatar = "client/data/avatars/Dragonair.png"; break;
        case 9: avatar = "client/data/avatars/Dratini.png"; break;
        case 10: avatar = "client/data/avatars/Eevee.png"; break;
        case 11: avatar = "client/data/avatars/Ekans.png"; break;
        case 12: avatar = "client/data/avatars/Espeon.png"; break;
        case 13: avatar = "client/data/avatars/Flareon.png"; break;
        case 14: avatar = "client/data/avatars/Ghastly.png"; break;
        case 15: avatar = "client/data/avatars/Glaceon.png"; break;
        case 16: avatar = "client/data/avatars/Gyrados.png"; break;
        case 17: avatar = "client/data/avatars/Haunter.png"; break;
        case 18: avatar = "client/data/avatars/Iggybuff.png"; break;
        case 19: avatar = "client/data/avatars/Jigglypuff.png"; break;
        case 20: avatar = "client/data/avatars/Jolteon.png"; break;
        case 21: avatar = "client/data/avatars/Kyogre.png"; break;
        case 22: avatar = "client/data/avatars/Latias.png"; break;
        case 23: avatar = "client/data/avatars/Latios.png"; break;
        case 24: avatar = "client/data/avatars/Leafeon.png"; break;
        case 25: avatar = "client/data/avatars/Lugia.png"; break;
        case 26: avatar = "client/data/avatars/Luxray.png"; break;
        case 27: avatar = "client/data/avatars/Meowth.png"; break;
        case 28: avatar = "client/data/avatars/Mew.png"; break;
        case 29: avatar = "client/data/avatars/Milotic.png"; break;
        case 30: avatar = "client/data/avatars/Mudkip.png"; break;
        case 31: avatar = "client/data/avatars/Ninetails.png"; break;
        case 32: avatar = "client/data/avatars/Palkia.png"; break;
        case 33: avatar = "client/data/avatars/Persian.png"; break;
        case 34: avatar = "client/data/avatars/Rayquaza.png"; break;
        case 35: avatar = "client/data/avatars/Sealeo.png"; break;
        case 36: avatar = "client/data/avatars/Skitty.png"; break;
        case 37: avatar = "client/data/avatars/Spheal.png"; break;
        case 38: avatar = "client/data/avatars/Suicune.png"; break;
        case 39: avatar = "client/data/avatars/Swampert.png"; break;
        case 40: avatar = "client/data/avatars/Totodile.png"; break;
        case 41: avatar = "client/data/avatars/Umbreon.png"; break;
        case 42: avatar = "client/data/avatars/Vaporeon.png"; break;
        case 43: avatar = "client/data/avatars/Vulpix.png"; break;
        case 44: avatar = "client/data/avatars/Weezing.png"; break;
        default: avatar = "client/data/avatars/luna_PAXANDDOS.png"; break;
    }
    return avatar;
}

static GdkPixbuf *create_pixbuf(const gchar *filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    
    if (!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

static GdkPixbuf *get_pixbuf_with_size(char *path, int w, int h) {
    GdkPixbuf *pixbuf = create_pixbuf(path);
    GdkPixbuf *result = gdk_pixbuf_scale_simple(GDK_PIXBUF(pixbuf), w, h, GDK_INTERP_BILINEAR);
    g_object_unref(G_OBJECT(pixbuf));
    return result;
}

gboolean draw_event_avatar(GtkWidget *widget, cairo_t *cr, int size) {
    GdkPixbuf *pixbuf = get_pixbuf_with_size(avatar_generated, size, size);  // Добавить сюда функцию в которой указан конкретный аватар для аккаунта. Сейчас - рандом
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = size,
        height = size,
        aspect = 1.0,                       /* aspect ratio */
        corner_radius = height / 2.0;       /* and corner curvature radius */
    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_fill(cr);
    if (widget) {}
    return FALSE;
}

gboolean draw_event_homebg(GtkWidget *widget, cairo_t *cr) {
    GdkPixbuf *pixbuf = get_pixbuf_with_size("client/data/images/messangerBG.png", CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}
