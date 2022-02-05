#include "Profile.h"

//comment satırları var
Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const
{
    return this->username;
}

const std::string &Profile::getEmail() const
{
    return this->email;
}

SubscriptionPlan Profile::getPlan() const
{
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists()
{
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings()
{
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers()
{
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan)
{
    this->plan = plan;
}

void Profile::followProfile(Profile *profile)
{
    /* TODO */
    following.insertAtTheEnd(profile);
    profile->getFollowers().insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile)
{
    /* TODO */
    following.removeNode(profile);
    profile->getFollowers().removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName)
{

    /* TODO */
    Playlist newPl(playlistName);
    playlists.insertAtTheEnd(newPl);
}

void Profile::deletePlaylist(int playlistId)
{
    /* TODO */
    Node<Playlist> *curPlaylistNode = getPlaylists().getFirstNode();
    for (int i = 0; i < getPlaylists().getSize(); i++)
    {
        if (playlistId == curPlaylistNode->data.getPlaylistId())
        {
            break;
        }
        curPlaylistNode = curPlaylistNode->next;
    }
    playlists.removeNode(curPlaylistNode);
}

void Profile::addSongToPlaylist(Song *song, int playlistId)
{
    /* TODO */
    Playlist *wantedPl = getPlaylist(playlistId);
    wantedPl->addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId)
{
    /* TODO */

    Playlist *wantedPl = getPlaylist(playlistId);
    wantedPl->dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId)
{
    /* TODO */
    int sz = playlists.getSize();
    Node<Playlist> *wantedPl = playlists.getFirstNode();
    for (int i = 0; i < sz; i++)
    {
        if (playlistId == wantedPl->data.getPlaylistId())
        {
            break;
        }
        wantedPl = wantedPl->next;
    }
    return &(wantedPl->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists()
{
    /* TODO */
    LinkedList<Playlist *> sharedPl;
    Node<Profile *> *curNodeProf = following.getFirstNode();
    for (int i = 0; i < following.getSize(); i++)
    {
        LinkedList<Playlist> curPl = curNodeProf->data->getPlaylists();
        Node<Playlist> *curNodePl = curPl.getFirstNode();
        for (int j = 0; j < curPl.getSize(); j++)
        {
            if (curNodePl->data.isShared())
            {
                sharedPl.insertAtTheEnd(curNodeProf->data->getPlaylist(curNodePl->data.getPlaylistId()));
            }
            curNodePl = curNodePl->next;
        }
        curNodeProf = curNodeProf->next;
    }

    return sharedPl;
}

void Profile::shufflePlaylist(int playlistId, int seed)
{
    /* TODO */
    Playlist *wantedPl = getPlaylist(playlistId);
    wantedPl->shuffle(seed);
}

void Profile::sharePlaylist(int playlistId)
{
    /* TODO */
    Playlist *wantedPl = getPlaylist(playlistId);
    wantedPl->setShared(true);
    /*
    Node<Playlist> *curPlaylistNode = getPlaylists().getFirstNode();
    for (int i = 0; i < getPlaylists().getSize(); i++)
    {
        if (playlistId == curPlaylistNode->data.getPlaylistId())
        {
            break;
        }
        curPlaylistNode = curPlaylistNode->next;
    }
    curPlaylistNode->data.setShared(true);*/
}

void Profile::unsharePlaylist(int playlistId)
{
    /* TODO */
    Playlist *wantedPl = getPlaylist(playlistId);
    wantedPl->setShared(false);
    /*
    Node<Playlist> *curPlaylistNode = getPlaylists().getFirstNode();
    for (int i = 0; i < getPlaylists().getSize(); i++)
    {
        if (playlistId == curPlaylistNode->data.getPlaylistId())
        {
            break;
        }
        curPlaylistNode = curPlaylistNode->next;
    }
    curPlaylistNode->data.setShared(false);*/
}

bool Profile::operator==(const Profile &rhs) const
{
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const
{
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile)
{
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge)
    {
        os << " plan: "
           << "free_of_charge"
           << " |";
    }
    else if (profile.plan == premium)
    {
        os << " plan: "
           << "premium"
           << " |";
    }
    else
    {
        os << " plan: "
           << "undefined"
           << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode)
    {
        do
        {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode)
                os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode)
    {
        do
        {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode)
                os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode)
    {
        do
        {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode)
                os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
