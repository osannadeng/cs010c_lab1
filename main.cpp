#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  //initializing title
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  cout << endl;

  Playlist P;

  while(true) {
    P.PrintMenu(title);

    string command;
    if (!(cin >> command)) break;

    string id;
    string song;
    string artist;
    int length;

    if (command == "a") {
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> id;
      cout << "Enter song's name:" << endl;
      cin.ignore();
      getline(cin, song);
      cout << "Enter artist's name:" << endl;
      getline(cin, artist);
      cout << "Enter song's length (in seconds):" << endl;
      cin >> length;
      cout << endl;
      P.AddSong(id, song, artist, length);
    } else if (command == "d") {
      P.RemoveSong();
    } else if (command == "c") {
      P.ChangePositionSong();
    } else if (command == "s") {
      P.OutputSongsByArtist();
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" << endl;
      P.OutputFullPlaylist();
    } else if (command == "q") {
      break;
    }
  }

  P.~Playlist();

  // If cin is in an error state (even end-of-file), then
  // something went wrong
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }

  return 0;
}
