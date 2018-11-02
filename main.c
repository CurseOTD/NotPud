// For compile use
// gcc main.c -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <gtk/gtk.h>

GtkWidget *view;
GtkTextBuffer *buffer;
GtkTextIter start, end;
gchar *content, *filename;

static void menu_response (GtkWidget* menu_item, gpointer data) {
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Exit") == 0){
		gtk_main_quit();
	}
}

static void about_us(GtkWidget* menu_item, GtkWindow *window) {
    const gchar *authors[] = {"Ilya Baryko","Maksim Kuntsevich", "Nadezhda Sinkevich", "David Gulkevich", NULL };
    GdkPixbuf *logo = gdk_pixbuf_new_from_file("./source/logo.png", NULL);
    gtk_show_about_dialog(window,
                            "authors", authors,
                            "logo", logo,
                            "program-name", "NotPud - the best notepad",
                            "version", "v1.0",
                            "comments", "Remember this application. It will remain forever. ;)",
                            "website", "https://vk.com/levelup_bsuir", "website-label", "Application Homepage",
                            "copyright", "(C) 2018 lvlup.c", NULL);
}

static void open_dialog(GtkWidget* menu_item, GtkWidget* window) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open file",
                                        GTK_WINDOW(window),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        GTK_STOCK_OK, GTK_RESPONSE_OK,
                                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                        NULL);
    gtk_widget_show_all(dialog);
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_OK) {
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_file_get_contents(filename, &content, NULL, NULL);
        content = g_locale_to_utf8(content, -1, NULL, NULL, NULL);
        gtk_text_buffer_set_text(buffer, content, -1);
        g_free(content);
    }
    gtk_widget_destroy(dialog);
}

static void saveas_dialog(GtkWidget* menu_item, GtkWidget* window) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new("Save file",
	 									 GTK_WINDOW(window),
	 									 GTK_FILE_CHOOSER_ACTION_SAVE,
	 									 GTK_STOCK_OK, GTK_RESPONSE_OK,
                                       	 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	 									 NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
	gtk_widget_show_all(dialog);
	gint res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_OK) {
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_text_buffer_get_start_iter(buffer, &start);
		gtk_text_buffer_get_end_iter(buffer, &end);
		content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
		g_file_set_contents(filename, content, -1, NULL);
		g_free(content);
	}
	gtk_widget_destroy(dialog);
}

static void save_dialog(GtkWidget* menu_item, GtkWidget* window) {
	if (filename != NULL) {
		gtk_text_buffer_get_start_iter(buffer, &start);
		gtk_text_buffer_get_end_iter(buffer, &end);
		content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
		g_file_set_contents(filename, content, -1, NULL);
		g_free(content);
	} else {
		GtkWidget *dialog;
		dialog = gtk_file_chooser_dialog_new("Save file",
		 									 GTK_WINDOW(window),
		 									 GTK_FILE_CHOOSER_ACTION_SAVE,
		 									 GTK_STOCK_OK, GTK_RESPONSE_OK,
    	                                   	 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		 									 NULL);
		gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
		gtk_widget_show_all(dialog);
		gint res = gtk_dialog_run(GTK_DIALOG(dialog));
		if (res == GTK_RESPONSE_OK) {
			filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			gtk_text_buffer_get_start_iter(buffer, &start);
			gtk_text_buffer_get_end_iter(buffer, &end);
			content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
			g_file_set_contents(filename, content, -1, NULL);
			g_free(content);
		}
		gtk_widget_destroy(dialog);
	}
}

static void text_wrap(GtkWidget* menu_item, GtkWidget* window) {
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item))) {
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD_CHAR);
	} else {
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD);
	}
}

int main(int argc, char* argv[]) {
	GtkWidget *window, *box, *scrolled_window,
	*menu_item, *menu_bar, *file_menu, *help_menu,
	*edit_menu, *settings_menu;
	GdkPixbuf *icon = gdk_pixbuf_new_from_file("./source/icon.png", NULL);

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	gtk_window_set_default_size(GTK_WINDOW(window), 1152, 768);
	gtk_window_set_title(GTK_WINDOW(window), "NotPud");
	gtk_window_set_icon(GTK_WINDOW(window), icon);

	buffer = gtk_text_buffer_new(NULL);
	view = gtk_text_view_new_with_buffer(buffer);

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window), 
                                   GTK_POLICY_AUTOMATIC, 
                                   GTK_POLICY_AUTOMATIC);
								   
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD_CHAR);
	
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
	g_signal_connect(menu_item, "activate", G_CALLBACK(open_dialog), NULL);

	menu_item = gtk_menu_item_new_with_label("Save");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(save_dialog), NULL);

	menu_item = gtk_menu_item_new_with_label("Save as");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(saveas_dialog), NULL);

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

	menu_item = gtk_check_menu_item_new_with_label("Text wrap");
	gtk_menu_shell_append(GTK_MENU_SHELL(settings_menu), menu_item);
	g_signal_connect(menu_item, "toggled", G_CALLBACK(text_wrap), NULL);

	menu_item = gtk_menu_item_new_with_label("About Us");
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(about_us), NULL);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), menu_bar, 0, 0, 0);

	gtk_container_add(GTK_CONTAINER(scrolled_window), view);
	gtk_container_set_border_width (GTK_CONTAINER(scrolled_window), 5);
	
	gtk_box_pack_start(GTK_BOX(box), scrolled_window, 100, 100, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}