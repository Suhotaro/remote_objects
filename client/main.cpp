
#include "client.hpp"
#include "message.hpp"
#include "photo_editor.hpp"

#include <iostream>
#include <thread>

int main() {    
    std::cout << "Client\n";

    client::Client client;

    // async object
    std::shared_ptr<client::Stream> stream = client.make_stream();
    int stream_id = stream->id();
    stream->start();
    stream->send_chat_msg("hello subs");
    stream->send_chat_msg("Today I stream for 10 hours");
    stream->donate(2);
    stream->send_chat_msg("Buy");
    sleep(1); // wait async replys
    stream->stop();

    printf("\n");

    // sync object
    std::shared_ptr<client::PhotoEditor> photo_editor = client.make_photo_editor();
    int photo_editor_id = photo_editor->id();
    photo_editor->upload("funy_cat.bmp");
    photo_editor->rotate(90);
    auto photo_editor_info = photo_editor->info();
    printf("Photo Editor info: %s %d\n",
        photo_editor_info->image.c_str(),
        photo_editor_info->degree);

    printf("\n");

    // bind to previously created async object
    std::shared_ptr<client::Stream> binded_stream = client.make_stream(stream_id);
    binded_stream->start();
    binded_stream->send_chat_msg("hello subs once again");
    binded_stream->send_chat_msg("Today I am going for 20 hours");
    binded_stream->send_chat_msg("Buy!");

    binded_stream->donate(5);
    binded_stream->donate(10);

    sleep(1); // wait async replys
    binded_stream->stop();

    printf("\n");

    // bind to previously created sync object
    std::shared_ptr<client::PhotoEditor> binded_photo_editor = client.make_photo_editor(photo_editor_id);
    auto binded_photo_editor_info = binded_photo_editor->info();
    printf("Binded Photo Editor info: %s %d\n",
        binded_photo_editor_info->image.c_str(),
        binded_photo_editor_info->degree);
    
    return 0;
}
