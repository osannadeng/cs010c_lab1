#include "Playlist.h"

PlaylistNode & PlaylistNode::operator=(const PlaylistNode &rhs) {
  uniqueID = rhs.uniqueID;
  songName = rhs.songName;
  artistName = rhs.artistName;
  songLength = rhs.songLength;
  nextNodePtr = rhs.nextNodePtr;
  return *this;
}

void PlaylistNode::SetNext(PlaylistNode* nextNode) {
  nextNodePtr = nextNode;
}

void PlaylistNode::InsertAfter(PlaylistNode* nextNode) {
  PlaylistNode* tempNext = nextNodePtr;
  nextNodePtr = nextNode;
  nextNode->nextNodePtr = tempNext;
}

Playlist::~Playlist() {
  PlaylistNode* next = nullptr;
  while (head) {  //iterates through list to delete
    next = head->GetNext();
    delete head;
    head = next;
  }
  head = tail = nullptr;
}

void Playlist::PrintMenu(const string& title) const {
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl << endl;
  cout << "Choose an option:" << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  PlaylistNode* newSong = new PlaylistNode(id, song, artist, length);
  if (head == nullptr) {  //if empty
    head = tail = newSong;
  } else {
    tail->InsertAfter(newSong);
    tail = newSong;
  }
}
    
void Playlist::RemoveSong() {
  string id;
  cout << "REMOVE SONG" << endl;
  cout << "Enter song's unique ID:" << endl;
  cin >> id;
  PlaylistNode* delSong = nullptr;

  if (head == nullptr) {  //empty list, do nothing
    cout << "Playlist is empty" << endl;
    return;
  }
  
  //check head and remove
  if (head->GetID() == id) {
    cout << "\"" << head->GetSongName() << "\" removed." << endl << endl;
    delSong = head->GetNext();
    delete head;
    head = delSong;
    return;
  }
  PlaylistNode* prev = head;
  delSong = head->GetNext();
  //iterate through rest of loop (until found) and remove
  while (delSong) {
    if (delSong->GetID() == id) {
      cout << "\"" << delSong->GetSongName() << "\" removed." << endl << endl;
      prev->SetNext(delSong->GetNext());
      delete delSong;
      if (prev->GetNext() == nullptr) { //tail case
        tail = prev;
      }
      return;
    }
    prev = delSong;
    delSong = delSong->GetNext();
  }
}
    
void Playlist::ChangePositionSong() {
  int currPos;
  int newPos;
  //user input
  cout << "CHANGE POSITION OF SONG" << endl;
  cout << "Enter song's current position:" << endl;
  cin >> currPos;
  cout << "Enter new position for song:" << endl;
  cin >> newPos;

  if (head == nullptr) {  //empty list, do nothing
    cout << "Playlist is empty" << endl;
    return;
  }
  
  if (head->GetNext() == nullptr) { //if only one song in list
    cout << "\"" << head->GetSongName() << "\" moved to position 1" << endl << endl;
    return;
  }

  //look for song
  PlaylistNode* curr = head;
  PlaylistNode* prev = nullptr;
  int index;
  //first find and remove song
  if (currPos <= 1) { //override input invalidity, takes head
    head = head->GetNext();
  } else {
    curr = head->GetNext();
    prev = head;
    index = 2;
    while (curr->GetNext() && index < currPos) { //ends if value found or end of list, overrides input invalidity
      curr = curr->GetNext();
      prev = prev->GetNext();
      ++index;
    }
    if (curr->GetNext() == nullptr) {  //tail case
      tail = prev;
    } else {
      prev->SetNext(curr->GetNext());
    }
  }
  curr->SetNext(nullptr);

  //reinsert song
  if (newPos <= 1) {  //head for position 1 or below bounds
    curr->SetNext(head);
    head = curr;
    cout << "\"" << curr->GetSongName() << "\" moved to position 1" << endl << endl;
    return;
  }
  PlaylistNode* insAfter = head;
  index = 1;
  while (insAfter && index < newPos - 1) {  //gets node before new position
    ++index;
    insAfter = insAfter->GetNext();
  }
  if (insAfter == nullptr) {  //appends at end if new position is >= end
    tail->SetNext(curr);
    tail = curr;
    cout << "\"" << curr->GetSongName() << "\" moved to position " << index << endl << endl;
    return;
  }
  insAfter->InsertAfter(curr);
  if (curr->GetNext() == nullptr) { //adjusts tail if changed
    tail = curr;
  }
  cout << "\"" << curr->GetSongName() << "\" moved to position " << newPos << endl << endl;
}
    
void Playlist::OutputSongsByArtist() const {
  string name;
  cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
  cout << "Enter artist's name:" << endl;
  cin.ignore();
  getline(cin, name);
  cout << endl;
  PlaylistNode* curr = head;
  int count = 1;
  while (curr) {
    //check artists for every song, output if matches
    if (curr->GetArtistName() == name) {
      cout << count << "." << endl;
      cout << "Unique ID: " << curr->GetID() << endl;
      cout << "Song Name: " << curr->GetSongName() << endl;
      cout << "Artist Name: " << curr->GetArtistName() << endl;
      cout << "Song Length (in seconds): " << curr->GetSongLength() << endl << endl;
    }
    curr = curr->GetNext();
    ++count;
  }
}
    
void Playlist::OutputTotalTime() const {
  int total = 0;
  //iterates through list, adds times to total
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    total += curr->GetSongLength();
  }
  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  cout << "Total time: " << total << " seconds" << endl << endl;
}

void Playlist::OutputFullPlaylist() const {
  if (head == nullptr) {  //if empty, do nothing
    cout << "Playlist is empty" << endl;
  }
  PlaylistNode* curr = head;
  int count = 1;  //for numbering
  while (curr) {  //iterate through playlist
    cout << count << "." << endl;
    cout << "Unique ID: " << curr->GetID() << endl;
    cout << "Song Name: " << curr->GetSongName() << endl;
    cout << "Artist Name: " << curr->GetArtistName() << endl;
    cout << "Song Length (in seconds): " << curr->GetSongLength() << endl;
    curr = curr->GetNext();
    if (curr) { //extra space between songs, except at end
      cout << endl;
    }
    ++count;
  }
  cout << endl;
}