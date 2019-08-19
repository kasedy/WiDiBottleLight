#include "hardware.h"

#include <WString.h>

const char* DEVICE_SAFE_NAME = ([]() {
  String beautifullName(DEVICE_BEAUTIFUL_NAME);
  beautifullName.toLowerCase();
  
  String result;
  result.reserve(beautifullName.length());
  for (unsigned int i = 0; i < beautifullName.length(); ++i) {
    if (beautifullName[i] >= 'a' && beautifullName[i] <= 'z') {
      result += beautifullName[i];
    } else if (result.length() > 0 && result[result.length() - 1] != '_') {
      result += '_';
    }
  }

  char *name = new char[result.length() + 1];
  name[result.length() + 1] = '\0';
  memcpy(name, result.c_str(), result.length());
  return name;
})();
