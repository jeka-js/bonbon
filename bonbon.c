#include "bonbon.h"
#include "funcs.h"
#include "connection.h"
#include "page_connection.h"
#include "page_keyboard.h"
#include "page_shell.h"

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    /* GTK initialization */

    gdk_threads_init();
    gtk_init(&argc, &argv);

    /* Loading widows forms from XML (Glade) file */

    GtkBuilder * builder = gtk_builder_new();

    if (!gtk_builder_add_from_file(builder, GLADE_FILE_NAME, &global.error_msg))
    {
        g_warning("%s\n", global.error_msg->message);
        return EXIT_FAILURE;
    }

    /* Bindings objects */

    page_connection_bind(builder);
    page_keyboard_bind(builder);
    page_shell_bind(builder);

    /* Signals */

    gtk_builder_connect_signals(builder, NULL);

    /* Starting */

    gtk_widget_show_all(GTK_WIDGET(global.main_window));
    g_object_unref(G_OBJECT(builder));
    show_in_statusbar(READY_MESSAGE);
    gtk_main();

    return EXIT_SUCCESS;
}

