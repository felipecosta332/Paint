#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *chooserPPM;
GtkWidget *description;
GtkWidget *image;
GtkBuilder *builder;

int main(int argc, char *argv[])
{

  gtk_init(&argc, &argv); //starting the gtk

  builder = gtk_builder_new_from_file("visualInterface.glade");

  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  chooserPPM = GTK_WIDGET(gtk_builder_get_object(builder, "chooserPPM"));
  description = GTK_WIDGET(gtk_builder_get_object(builder, "description"));
  image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

  char file[] = "../files/japan.ppm";
  image = gtk_image_new_from_file("file");

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

void on_chooserPPM_file_set(GtkFileChooserButton *f)
{
  printf("file name = %s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
  printf("folder name = %s\n", gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(f)));
}