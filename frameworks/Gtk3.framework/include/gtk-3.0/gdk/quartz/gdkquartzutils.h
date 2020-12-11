/* gdkquartzutils.h
 *
 * Copyright (C) 2005  Imendio AB
 * Copyright (C) 2010  Kristian Rietveld  <kris@gtk.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__GDKQUARTZ_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkquartz.h> can be included directly."
#endif

#ifndef __GDK_QUARTZ_UTILS_H__
#define __GDK_QUARTZ_UTILS_H__

#include <gdk/gdk.h>

G_BEGIN_DECLS

NSImage  *gdk_quartz_pixbuf_to_ns_image_libgtk_only             (GdkPixbuf      *pixbuf);
NSEvent  *gdk_quartz_event_get_nsevent                          (GdkEvent       *event);

G_END_DECLS

#endif /* __GDK_QUARTZ_UTILS_H__ */
