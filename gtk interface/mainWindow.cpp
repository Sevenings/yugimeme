#include "mainWindow.h"
#include "glibmm/ustring.h"
#include "gtkmm/enums.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>

MainWindow::MainWindow() : 
    create_card_button("Create"),
    select_input_image_button("Select Image"),
    card_preview_frame(Gtk::Align::END, Gtk::Align::CENTER, 0.6858),
    card_picture("template.jpg")
{
    // Create Card Button
    create_card_button.set_margin(10);
    create_card_button.signal_clicked().connect(sigc::mem_fun(*this,
                                            &MainWindow::on_create_card_button_clicked));

    // Select input image button
    select_input_image_button.signal_clicked().connect(sigc::mem_fun(*this,
                                            &MainWindow::on_select_input_image_button_clicked));

    // Realizando a composição
    set_child(layout);
    layout.append(entry);
    layout.append(create_card_button);
    layout.append(select_input_image_button);
    layout.append(card_preview_frame);
        card_preview_frame.set_child(card_picture);
}

void MainWindow::on_create_card_button_clicked()
{
    Glib::ustring content = entry.get_text();
    std::cout << content << std::endl;
}

void MainWindow::on_select_input_image_button_clicked()
{
    std::cout << "Choose a card" << std::endl;
}
