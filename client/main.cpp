
#include "client.hpp"
#include "message.hpp"
#include "photo_editor.hpp"

#include <iostream>
#include <thread>

int main() {    
    std::cout << "Client\n";

    client::Client client;

    std::shared_ptr<client::Stream> stream = client.make_stream();
    stream->start();
    stream->send_chat_msg("hi to all");
    stream->send_chat_msg("hi to all");
    sleep(5);

    stream->stop();


/*    
    std::shared_ptr<client::PhotoEditor> photo_editor = client.make_photo_editor();

    photo_editor->upload("funy_cat.bmp");
    photo_editor->rotate(90);
    auto photo_editor_info = photo_editor->info();
    printf("Photo Editor info: %s %d\n",
        photo_editor_info->image.c_str(),
         photo_editor_info->degree);
*/    
    return 0;
}
