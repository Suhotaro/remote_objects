
#include "client.hpp"
#include "message.hpp"
#include "photo_editor.hpp"

#include <iostream>
#include <thread>

int main() {    
    std::cout << "Client\n";

    client::Client client;
    std::shared_ptr<client::PhotoEditor> photo_editor = client.make_photo_editor();

    photo_editor->upload("funy_cat.bmp");
    photo_editor->rotate(90);
    
    return 0;
}
