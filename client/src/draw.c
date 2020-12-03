#include "../inc/client.h"

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
    GdkPixbuf *result = gdk_pixbuf_scale_simple(GDK_PIXBUF(pixbuf), w, h, GDK_INTERP_HYPER);
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

gboolean draw_event_pokemon(GtkWidget *widget, cairo_t *cr, int size) {
    GdkPixbuf *pixbuf = get_pixbuf_with_size(pokemon_fact_image, size, size);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}
