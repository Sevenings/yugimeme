#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/picture.h>

class MainWindow : public Gtk::Window 
{
    public:
        MainWindow();

    protected:
        //Signal handlers:
        void on_create_card_button_clicked();
        void on_select_input_image_button_clicked();

        //Member widgets:
        Gtk::Button create_card_button;
        Gtk::Entry entry;
        Gtk::FlowBox layout;
        Gtk::Button select_input_image_button;
        Gtk::AspectFrame card_preview_frame;
        Gtk::Picture card_picture;
};

#endif 
