/**
 * Two shoppers adding garlic and potatoes to a shared notepad
 *  parallel-concurrent-programming-c-1-video.rar/Barron Stone,5/2020 
 *  *M* Try to usd one thread and see if the program deadlock
 */
#include <thread>
#include <mutex>

unsigned int garlic_count = 0;
unsigned int potato_count = 0;
//std::recursive_mutex pencil;
std::mutex pencil;   

void add_garlic() {
    pencil.lock();
    garlic_count++;
    pencil.unlock();
}

void add_potato() {
    pencil.lock();
    potato_count++;
    add_garlic();
    pencil.unlock();
}

void shopper() {
    for (int i=0; i<10000; i++) {
        add_garlic();
        add_potato();
    }
}

int main() {
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic.\n", garlic_count);
    printf("We should buy %u potatoes.\n", potato_count);
}