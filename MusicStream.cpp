#include "MusicStream.h"

#include <iostream>

Node<Profile> *MusicStream::getProfileNode(const std::string &email)
{
    Node<Profile> *tmpProfNode = profiles.getFirstNode();

    for (int i = 0; i < profiles.getSize(); i++)
    {
        if (email == tmpProfNode->data.getEmail())
        {
            return tmpProfNode;
            break;
        }
        tmpProfNode = tmpProfNode->next;
    }
}
void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    /* TODO */
    Profile newProf(email, username, plan);
    profiles.insertAtTheEnd(newProf);
}

void MusicStream::deleteProfile(const std::string &email)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    LinkedList<Profile *> *followersofProf = &(tmpProfNode->data.getFollowers());

    while (!followersofProf->isEmpty())
    {
        followersofProf->getLastNode()->data->unfollowProfile(&(tmpProfNode->data));
    }

    LinkedList<Profile *> *followingsofProf = &(tmpProfNode->data.getFollowings());

    while (!followingsofProf->isEmpty())
    {
        tmpProfNode->data.unfollowProfile(followingsofProf->getLastNode()->data);
    }

    profiles.removeNode(tmpProfNode);
}

void MusicStream::addArtist(const std::string &artistName)
{
    /* TODO */
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId)
{
    /* TODO */
    Album newAlbum(albumName);
    albums.insertAtTheEnd(newAlbum);

    Node<Artist> *tmpArtistNode = artists.getFirstNode();
    for (int i = 0; i < artists.getSize(); i++)
    {
        if (tmpArtistNode->data.getArtistId() == artistId)
        {
            tmpArtistNode->data.addAlbum(&(albums.getLastNode()->data));
            break;
        }
        tmpArtistNode = tmpArtistNode->next;
    }
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId)
{
    /* TODO */
    Song newSong(songName, songDuration);
    songs.insertAtTheEnd(newSong);

    Node<Album> *tmpAlbumNode = albums.getFirstNode();
    for (int i = 0; i < albums.getSize(); i++)
    {
        if (tmpAlbumNode->data.getAlbumId() == albumId)
        {
            tmpAlbumNode->data.addSong(&(songs.getLastNode()->data));
            break;
        }
        tmpAlbumNode = tmpAlbumNode->next;
    }
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2)
{
    /* TODO */
    Profile *email1Prof = &(getProfileNode(email1)->data), *email2Prof = &(getProfileNode(email2)->data);
    email1Prof->followProfile(email2Prof);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2)
{
    /* TODO */
    Profile *email1Prof = &(getProfileNode(email1)->data), *email2Prof = &(getProfileNode(email2)->data);
    email1Prof->unfollowProfile(email2Prof);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    Playlist *tmpPlaylist = tmpProfNode->data.getPlaylist(playlistId);
    Node<Song> *tmpSongNode = songs.getFirstNode();

    for (int i = 0; i < songs.getSize(); i++)
    {
        if (songId == tmpSongNode->data.getSongId())
        {
            break;
        }
        tmpSongNode = tmpSongNode->next;
    }
    tmpPlaylist->addSong(&(tmpSongNode->data));
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    Playlist *tmpPlaylist = tmpProfNode->data.getPlaylist(playlistId);
    Node<Song> *tmpSongNode = songs.getFirstNode();

    for (int i = 0; i < songs.getSize(); i++)
    {
        if (songId == tmpSongNode->data.getSongId())
        {
            break;
        }
        tmpSongNode = tmpSongNode->next;
    }
    tmpPlaylist->dropSong(&(tmpSongNode->data));
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);

    if (tmpProfNode->data.getPlan() == premium)
    {
        return playlist->getSongs();
    }
    else
    {
        playlist->getSongs().insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
        LinkedList<Song *> freePlaylist = playlist->getSongs();
        playlist->getSongs().removeEveryKthNode(2);

        return freePlaylist;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    return tmpProfNode->data.getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    return tmpProfNode->data.getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.shufflePlaylist(playlistId, seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email)
{
    /* TODO */
    Node<Profile> *tmpProfNode = getProfileNode(email);
    tmpProfNode->data.setPlan(free_of_charge);
}

void MusicStream::print() const
{
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
