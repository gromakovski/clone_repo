#ifndef BUILDER_SELECTOR_H
#define BUILDER_SELECTOR_H

#include "async.h"

class BuilderSelector {
 public:
  BuilderSelector(async::handle_t bulkParserHandler)
      : bulkParserHandler_(bulkParserHandler) {}

  void dataReceived(const char *data_, std::size_t length);

 private:
  async::handle_t bulkParserHandler_;
  async::handle_t bulkParserDynamicHandler_;

  int startendCmdCounter = 0;
  bool dynamicBlockFlag = false;
};

#endif  // BUILDER_SELECTOR_H
