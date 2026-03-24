#include <iostream>
#include <string>

using namespace std;

// Phase 1: The Template Node

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val) {
        data = val;
        next = nullptr;
    }
};
// that above holds the actual song and the pointer which is required
// ok now going to the next task which is the Simple Song class to test the list
class Song {
public:
    string title;
    string artist;

    Song(string t, string a) : title(t), artist(a) {}
    
    void play() {
        cout << "Now playing: " << title << " by " << artist << endl;
    }
};

// Phase 1 and 2: The Templated Circular List
template <typename T>
class Playlist {
private:
    Node<T>* head;
    Node<T>* tail;    // I am going to need this for the circular logic also explained in the video
    Node<T>* current; // now for the playNext feature

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // Phase 2: Circular Insertion
    void addSong(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // Point to itself to make it circular
        } else {
            // Standard append but with the circular "link back"
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // The "wrap-around" link
        }
    }

    // Simple display - common mistake: using while(curr != nullptr)
    // We use a do-while so it doesn't stop immediately at the head
    void showAll() {
        if (!head) return;
        
        Node<T>* temp = head;
        cout << "--- Playlist Items ---" << endl;
        do {
            // Assuming the type T has a title or some way to print
            cout << " - " << temp->data->title << endl;
            temp = temp->next;
        } while (temp != head); 
    }

    // Phase 2: playNext logic
    void playNext() {
        if (head == nullptr) return;

        if (current == nullptr) {
            current = head;
        } else {
            current = current->next; // Moves to next, wraps naturally
        }
        current->data->play();
    }

    // Phase 2: Destructor for circular cleanup
    ~Playlist() {
        if (head == nullptr) return;

        // Common mistake is trying to delete a circle. 
        // We break the circle first by making it linear.
        tail->next = nullptr; 

        Node<T>* n = head;
        while (n != nullptr) {
            Node<T>* nextNode = n->next;
            delete n->data; // Clean up the Song object
            delete n;       // Clean up the Node itself
            n = nextNode;
        }
        head = nullptr;
    }
};

int main() {
    // Testing the templated list with Song pointers
    Playlist<Song*> myMusic;

    myMusic.addSong(new Song("Starman", "David Bowie"));
    myMusic.addSong(new Song("Blinding Lights", "The Weeknd"));
    myMusic.addSong(new Song("Hotel California", "Eagles"));

    myMusic.showAll();
    
    cout << "\nStarting playback..." << endl;
    myMusic.playNext();
    myMusic.playNext();
    myMusic.playNext();
    myMusic.playNext(); // This will wrap back to the first song!

    return 0;
}
