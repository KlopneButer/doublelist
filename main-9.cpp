#include "mylist.h"

int main() {
  List<std::string> test;
  test.list_import("test_import.txt");
  test.sort();
  test.print_from_head();
  test.list_export("test_export.txt");
  return 0;
}
