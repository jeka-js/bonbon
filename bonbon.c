#include "page_connection.h"
#include "page_keyboard.h"
#include "grab_keyboard.h"
#include "preferences.h"
#include "page_shell.h"
#include "connection.h"
#include "errors.h"
#include "funcs.h"
#include "bonbon.h"

#include <gtk/gtk.h>

/*************************************************************************************************
 * Entry point.                                                                                   *
 **************************************************************************************************
 *  Initializing, loading interface from file and connecting signals.                             *
  *************************************************************************************************/

int main( int argc, char** argv )
{
    /* GTK initialization */
    gdk_threads_init();
    gtk_init( &argc, &argv );

    /* Loading widows forms from XML (Glade) file */
    GtkBuilder* builder = gtk_builder_new();

    if( !gtk_builder_add_from_file( builder, GLADE_FILE_NAME, &global.error_msg ) ) {
        g_warning( "%s\n", global.error_msg->message );
        global.error_msg = NULL;
        return( BUILDER_LOAD_FAIL );
    }

    /* Bindings objects */
    page_connection_bind( builder );
    page_keyboard_bind( builder );
    page_shell_bind( builder );
    grab_window_bind( builder );
    preferences_window_bind( builder );

    /* Signals */
    gtk_builder_connect_signals( builder, NULL );

    /* Starting */
    show_in_statusbar( READY_MESSAGE );
    g_object_unref( builder );
    gtk_main();

    return( SUCCESS );
}

