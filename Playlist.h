#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  PlaylistNode()
    : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr)
  {}
  PlaylistNode(const string &id, const string &name, const string &artist, int length)
    : uniqueID(id), songName(name), artistName(artist), songLength(length), nextNodePtr(nullptr)
  {}
  PlaylistNode(const PlaylistNode &copy)
    : uniqueID(copy.uniqueID), songName(copy.songName), artistName(copy.artistName), songLength(copy.songLength), nextNodePtr(copy.nextNodePtr)
  {}  //using default destructor
  PlaylistNode & operator=(const PlaylistNode &rhs);
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  void SetNext(PlaylistNode* nextNode);
  void InsertAfter(PlaylistNode* nextNode);
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
  }
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  ~Playlist();
  Playlist(const Playlist &) = delete;
  Playlist & operator=(const Playlist &) = delete;
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

