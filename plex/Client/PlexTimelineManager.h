#ifndef PLEXTIMELINEMANAGER_H
#define PLEXTIMELINEMANAGER_H

#include "StdString.h"
#include "FileItem.h"
#include "Utility/PlexTimer.h"
#include "threads/Event.h"
#include "UrlOptions.h"
#include "FileItem.h"
#include "Remote/PlexRemoteSubscriberManager.h"

#include <map>
#include <boost/shared_ptr.hpp>

class CPlexTimelineManager
{
  public:
    enum MediaType {
      MUSIC,
      PHOTO,
      VIDEO,
      UNKNOWN
    };

    enum MediaState {
      MEDIA_STATE_STOPPED,
      MEDIA_STATE_PLAYING,
      MEDIA_STATE_BUFFERING,
      MEDIA_STATE_PAUSED
    };

    CPlexTimelineManager();

    void ReportProgress(CFileItemPtr currentItem, MediaState state, uint64_t currentPosition=0);
    std::vector<CUrlOptions> GetCurrentTimeLines(int commandID = -1);
    CStdString GetCurrentTimeLinesXML(int commandID = -1);
    CUrlOptions GetCurrentTimeline(CPlexTimelineManager::MediaType type, bool forServer=true);

    static std::string StateToString(MediaState state);
    static std::string MediaTypeToString(CPlexTimelineManager::MediaType type);
    CPlexTimelineManager::MediaType GetMediaType(CFileItemPtr item);
    CPlexTimelineManager::MediaType GetMediaType(const CStdString &typestr);
    CStdString WaitForTimeline(int commandID = -1);
    uint64_t GetItemDuration(CFileItemPtr item);

    void SendTimelineToSubscriber(CPlexRemoteSubscriberPtr subscriber);
    void SendTimelineToSubscribers();

    void SetTextFieldFocused(bool focused);

    void Stop();

  private:
    std::map<MediaType, CFileItemPtr> m_currentItems;
    std::map<MediaType, MediaState> m_currentStates;

    CPlexTimer m_subTimer;
    CPlexTimer m_serverTimer;

    CEvent m_pollEvent;

    bool m_stopped;
    bool m_textfieldfocused;
};

typedef boost::shared_ptr<CPlexTimelineManager> CPlexTimelineManagerPtr;

#endif // PLEXTIMELINEMANAGER_H
