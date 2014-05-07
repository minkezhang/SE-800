#include "client.h"

#include <iostream>

int main() {
  ClientNetUtils clientUtils;
  if (clientUtils.connect_to_server(6667, "localhost"))
    cout << "connect test Passed!" << endl;
  return 0;
}
