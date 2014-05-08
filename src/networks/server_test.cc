#include "server.h"

#include <iostream>

int main() {
  Server server;
  server.start_server(6667);
  return 0;
}
