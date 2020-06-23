#ifndef COGS_STREAM_HPP_SEEN
#define COGS_STREAM_HPP_SEEN

#include "cogs/object.hpp"

namespace cogs {

    /// Abstract interface to a stream of objects.
    struct Stream {
        virtual ~Stream() {}

        /// Remove and return the next object in the stream.  May
        /// throw std::range_error() if called after the stream is
        /// exhausted.
        virtual object pop() = 0;
    };

    using stream_p = std::unique_ptr<Stream>;

    /// Factory method to return a stream implementation suitable for
    /// a given URI.  cogs provides built in support for the following
    /// file:// based URI schemes:
    ///
    /// - file://filename.json :: the file holds a JSON array of objects
    ///
    /// - file://filename.jstream :: the file holds a JSON stream
    ///   see for example https://en.wikipedia.org/wiki/JSON_streaming
    ///
    /// Support for MessagePack or Protobuf format and ZeroMQ message
    /// media may come later.
    stream_p make_stream(std::string uri);


}

#endif

