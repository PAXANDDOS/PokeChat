#include "../inc/client.h"

GdkPixbuf *create_pixbuf(const gchar *filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (!pixbuf) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

GdkPixbuf *get_pixbuf_with_size(char *path, int w, int h) {
    GdkPixbuf *pixbuf = create_pixbuf(path);
    GdkPixbuf *result = gdk_pixbuf_scale_simple(GDK_PIXBUF(pixbuf), w, h, GDK_INTERP_BILINEAR);
    g_object_unref(G_OBJECT(pixbuf));
    return result;
}

gboolean draw_event_avatar(GtkWidget *widget, cairo_t *cr, gpointer avatar) {
    char* a = get_avatar_by_number((int)(intptr_t)avatar);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(a, 34, 34, FALSE, NULL); // get_pixbuf_with_size(a, 34, 34);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = 34,
        height = 34,
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

gboolean draw_event_avatar_profile(GtkWidget *widget, cairo_t *cr, gpointer avatar) {
    char* a = get_avatar_by_number((int)(intptr_t)avatar);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(a, 90, 90, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = 90,
        height = 90,
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

gboolean draw_event_avatar_account(GtkWidget *widget, cairo_t *cr, int size) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(t_account.avatar, size, size, FALSE, NULL);
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
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(t_pokefact.pokemon_fact_image, size, size, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}

gboolean draw_event_status(GtkWidget *widget, cairo_t *cr, int size) {
    cairo_set_source_rgb(cr, 0.2, 0.7, 0);

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

gboolean draw_event_avatar_list(GtkWidget *widget, cairo_t *cr, char* path) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 80, 80, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}

gboolean draw_event_sticker_list(GtkWidget *widget, cairo_t *cr, char* path) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 70, 70, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}

gboolean draw_event_sticker(GtkWidget *widget, cairo_t *cr, char* path) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 200, 200, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
    cairo_paint(cr);

    if (widget) {}
    return FALSE;
}

gboolean draw_event_embedded(GtkWidget *widget, cairo_t *cr, char* path) {
    if (!path)
        return 0;

    GdkPixbuf *pb = gdk_pixbuf_new_from_file(path, NULL);
    int a = gdk_pixbuf_get_width(pb), b = gdk_pixbuf_get_height(pb);
    int old_b = b;
    if(b > 200) b = 200;
    a = b * a / old_b;
    g_object_unref(G_OBJECT(pb));
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, a, b, FALSE, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = a,
        height = b,
        aspect = 1.0,                        /* aspect ratio */
        corner_radius = height / 20.0;       /* and corner curvature radius */
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
