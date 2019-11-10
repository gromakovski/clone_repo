#include "builder_selector.h"

void BuilderSelector::dataReceived(const char *data_, std::size_t length) {
  if (data_[0] == '{') {
    if (!dynamicBlockFlag) bulkParserDynamicHandler_ = async::connect(3);
    startendCmdCounter++;
    dynamicBlockFlag = true;
  }

  if (data_[0] == '}') {
    startendCmdCounter--;
  }

  if (!dynamicBlockFlag) {
    async::receive(bulkParserHandler_, data_, length);
  }

  if (dynamicBlockFlag) {
    async::receive(bulkParserDynamicHandler_, data_, length);
  }

  if (startendCmdCounter == 0 && dynamicBlockFlag) {
    dynamicBlockFlag = false;
    async::disconnect(bulkParserDynamicHandler_);
  }
}
