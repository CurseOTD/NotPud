//gcc main.c -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char* argv[]) {
	GtkWidget *window;

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(window), "NotPud");

	gtk_widget_show(window);
	
	gtk_main();

	return 0;
}