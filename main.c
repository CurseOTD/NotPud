// For compile use
// gcc main.c -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static void menu_response (GtkWidget* menu_item, gpointer data){
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Exit") == 0){
		gtk_main_quit();
	}
}

static void about_us(GtkWidget* menu_item, GtkWindow *window)
{
    const gchar *authors[] = { "Ilya Baryko","Maxim Kuntsevich", "Nadezhda Sinkevich", "David Gulkevich", NULL };
    const gchar *license = "inc...";
    GdkPixbuf *logo = gdk_pixbuf_new_from_file("./png/logo.png", NULL);

    gtk_show_about_dialog(window,
                            "authors", authors, "license", license, "license-type", GTK_LICENSE_CUSTOM,
                            "logo", logo,
                            "program-name", "NotPud - the best notepad",
                            "version", "v. 1.0",
                            "comments", "Remember this application. It will remain forever. ;)",
                            "website", "https://vk.com/levelup_bsuir", "website-label", "Application Homepage",
                            "copyright", "(C) 2018 lvlup.c",
                            "wrap-license", TRUE, NULL);
}

int main(int argc, char* argv[]) {
	GtkWidget *window, *box, *notebook, *scrolled_window,
	*menu_bar, *file_menu, *help_menu, *help_item, *buffer,
	*multiline_text, *menu_item, *edit_menu, *settings_menu, *view;

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	int width, height;
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(window), "NotPud");
	
	menu_bar = gtk_menu_bar_new();

	file_menu = gtk_menu_new();
	edit_menu = gtk_menu_new();
	settings_menu = gtk_menu_new();
	help_menu = gtk_menu_new();

	menu_item = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("Edit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), edit_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("Settings");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), settings_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("Help");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("New");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Save");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Save as");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Exit");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

	menu_item = gtk_menu_item_new_with_label("Copy");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Paste");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Cut");
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Font");
	gtk_menu_shell_append(GTK_MENU_SHELL(settings_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("Text wrap");
	gtk_menu_shell_append(GTK_MENU_SHELL(settings_menu), menu_item);

	menu_item = gtk_menu_item_new_with_label("About Us");
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
	    g_signal_connect(menu_item, "activate", G_CALLBACK(about_us), NULL);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), menu_bar, 0, 0, 0);

	view = gtk_text_view_new();

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window), 
                                   GTK_POLICY_AUTOMATIC, 
                                   GTK_POLICY_AUTOMATIC);

	gtk_container_add(GTK_CONTAINER(scrolled_window), view);
	gtk_container_set_border_width (GTK_CONTAINER(scrolled_window), 5);
	
	gtk_box_pack_start(GTK_BOX(box), scrolled_window, 100, 100, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD_CHAR);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}