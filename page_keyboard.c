#include "page_keyboard.h"
#include "connection.h"
#include "funcs.h"

#include <string.h>
#include <unistd.h>

extern global_t global;

char* key1 = NULL;
char* key2 = NULL;
char* key3 = NULL;
char* key_seq = NULL;

void page_keyboard_bind( GtkBuilder* builder )
{
    /* Objects */
    GtkWidget* combo_Key1 = GTK_WIDGET( gtk_builder_get_object( builder, COMBO_KEY1 ) );
    GtkWidget* combo_Key2 = GTK_WIDGET( gtk_builder_get_object( builder, COMBO_KEY2 ) );
    GtkWidget* entry_Key3 = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_KEY3 ) );
    GtkWidget* entry_Key_sequence = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_KEY_SEQ ) );

    /* Signals */
    g_signal_connect( combo_Key1, "changed", G_CALLBACK( combo_changed ), &key1 );
    g_signal_connect( combo_Key2, "changed", G_CALLBACK( combo_changed ), &key2 );
    g_signal_connect( entry_Key3, "changed", G_CALLBACK( entry_edited ), &key3 );
    g_signal_connect( entry_Key_sequence, "changed", G_CALLBACK( entry_edited ), &key_seq);
}

G_MODULE_EXPORT void multiply_keys( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        char key_sequence[100];// = EMPTY_STRING;

        if( key1 != NULL ) { sprintf( key_sequence, "%s+", key1 ); }
        if( key2 != NULL ) { strcat( key_sequence, key2 ); strcat( key_sequence, "+" ); }
        if( key3 != NULL ) { strcat( key_sequence, key3 ); }
        else if( strlen( key_sequence ) != 0 ) {
            key_sequence[ strlen( key_sequence ) - 1 ] = END_OF_STRING;
        }

        send_key( key_sequence );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

G_MODULE_EXPORT void key_sequence( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        char* key_name = strtok( key_seq, " " );

        while( key_name != NULL ) {
            send_key( key_name );
            key_name = strtok( NULL, " " );
            usleep( global.send_delay );
        }
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

G_MODULE_EXPORT void key_pressed( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        const char* type = gtk_button_get_label( button );
        send_key( type );
        show_in_statusbar( type );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

G_MODULE_EXPORT void grab_keys( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        g_print( "Keyboard grab! :D Don't work yet...\n" );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

