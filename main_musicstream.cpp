#include <iostream>

#include "MusicStream.h"
//g++ Album.cpp Artist.cpp main_musicstream.cpp Playlist.cpp Profile.cpp Song.cpp MusicStream.cpp
using namespace std;
int main()
{
    MusicStream ms;

    ms.addProfile("a", "a", free_of_charge);
    ms.addProfile("b", "b", free_of_charge);
    ms.addProfile("c", "c", free_of_charge);
    ms.addProfile("d", "d", free_of_charge);

    ms.followProfile("a", "b");
    ms.followProfile("a", "c");
    ms.followProfile("a", "d");

    ms.followProfile("c", "b");
    ms.followProfile("c", "a");

    ms.createPlaylist("a", "pl1");
    ms.createPlaylist("a", "pl2");
    ms.createPlaylist("b", "pl3");
    // ms.deletePlaylist("a",1);
    // ms.deletePlaylist("b",3);

    ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);

    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.addSongToPlaylist("a", 2, 1);
    ms.addSongToPlaylist("a", 3, 2);
    ms.addSongToPlaylist("b", 4, 3);

    ms.sharePlaylist("a", 1);
    ms.sharePlaylist("b", 3);
    ms.unsharePlaylist("a",1);
    ms.print();
    //ms.getSharedPlaylists("c").print();

    


    return 0;
}
