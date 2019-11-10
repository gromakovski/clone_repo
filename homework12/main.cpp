#include <iostream>
#include <thread>

#include "server.h"

int main(int, char *[]) {
  //  auto h2 = async::connect(bulk);
  //  async::receive(h, "1", 1);
  //  async::receive(h2, "1\n", 2);
  //  async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
  //  async::receive(h, "b\nc\nd\n}\n89\n", 11);
  //  async::disconnect(h);
  //  async::disconnect(h2);
  //
  server s(9000);

  return 0;
}
