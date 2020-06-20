// Defines all issues cogs may raise
#ifndef COGS_ISSUES_HPP_SEEN
#define COGS_ISSUES_HPP_SEEN

#include "ers/ers.h"


ERS_DECLARE_ISSUE(cogs, bad_file,
                  "Can not open file: " << filename,
                  ((std::string)filename))


ERS_DECLARE_ISSUE(cogs, unsupported_uri,
                  "URI unsupported: " << uri,
                  ((std::string)uri))

ERS_DECLARE_ISSUE(cogs, stream_exhausted,
                  "Stream exhausted: " << name,
                  ((std::string)name))

ERS_DECLARE_ISSUE(cogs, stream_corrupt,
                  "Stream corrupt: " << name << " err: " << err,
                  ((std::string)name)
                  ((std::string)err))                  

#endif
