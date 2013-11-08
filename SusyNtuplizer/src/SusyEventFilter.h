#ifndef SusyEventFilter_h
#define SusyEventFilter_h

#include "SusyEvent.h"
#include "SusyTriggerEvent.h"

#include <string>
#include <map>

namespace susy {

  typedef bool (*EventFilter)(Event const&);

  class EventFilterDictionary {
  public:
    EventFilterDictionary(std::string const& _name, EventFilter _pFilter)
    {
      dictionary_[_name] = _pFilter;
    };

    static EventFilter getEventFilter(std::string const& _name)
    {
      std::map<std::string, EventFilter>::iterator fItr(dictionary_.find(_name));
      if(fItr == dictionary_.end()) return 0;
      else return fItr->second;
    };

  private:
    static std::map<std::string, EventFilter> dictionary_;
  };

}

#define DEFINE_SUSYEVENTFILTER(FILTER) \
  EventFilterDictionary FILTER##Dictionary(#FILTER, FILTER)

#endif
