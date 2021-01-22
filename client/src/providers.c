#include "../inc/client.h"

void load_providers()
{
    t_providers.styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(t_providers.styles, "client/data/css/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    if(t_account.theme == 1) {
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_light.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    else if(t_account.theme == 2) {
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_default.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    else if(t_account.theme == 3) {
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_dark.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4){
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
}
