#include "page_shell.h"
#include "connection.h"
#include "strings.h"
#include "funcs.h"

#include <stdlib.h>
#include <string.h>

extern global_t global;

static GtkEntry* e_Shell = NULL;
static GtkTextView* text_Shell = NULL;
static GtkTextBuffer* text_buffer_Shell = NULL;
char* command = NULL;

void page_shell_bind( GtkBuilder* builder )
{
    e_Shell = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_COMMAND_NAME ) );
    text_Shell = GTK_TEXT_VIEW( gtk_builder_get_object( builder, TEXT_VIEW_SHELL_NAME ) );
    text_buffer_Shell = GTK_TEXT_BUFFER( gtk_builder_get_object( builder, TEXT_BUFFER_SHELL_NAME ) );

    g_signal_connect( e_Shell, "changed", G_CALLBACK( entry_edited ), &command );
}

void b_Execute_clicked( GtkWidget* widget, gpointer data )
{
    /// FIXME: Works, but not so good
    if( !global.is_connected )
    {
        show_in_statusbar( OFFLINE_MESSAGE );
        return;
    }

    GtkTextIter iter;
    gtk_text_buffer_get_end_iter( text_buffer_Shell, &iter );

    if( isempty( command ) )
    {
        show_in_statusbar( ENTER_DATA_MESSAGE );
        return;
    }

    show_in_statusbar_ext( "Executing command: \"%s\".", command );
    gtk_text_buffer_insert( text_buffer_Shell, &iter, command, -1 );
    gtk_text_buffer_insert( text_buffer_Shell, &iter, "\n", -1 );

    char* result;
    execute_command( command, &result );
    gtk_text_buffer_insert( text_buffer_Shell, &iter, result, -1 );
    free( result );
    gtk_text_view_scroll_to_iter( text_Shell, &iter, 0.0, FALSE, 0.0, 0.0 );
    gtk_entry_buffer_delete_text( gtk_entry_get_buffer( e_Shell ), 0, -1 );
}

void on_page_select( GtkNotebook* notebook, gpointer data )
{
    if( gtk_notebook_get_current_page( notebook ) == 3 )
    {
        gtk_widget_grab_focus( GTK_WIDGET( e_Shell ) );
    }
}

