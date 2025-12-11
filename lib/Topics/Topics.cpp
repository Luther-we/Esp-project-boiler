#include "Topics.h"
#include "ProjectConfig.h"

namespace Topics {
  const String& base() {
    static String t = ProjectConfig::baseTopic(); // ex "desk3/"
    return t;
  }
  
  // SHT31 topics
  const String& availability() {
    static String t = base() + "status";
    return t;
  }

  const String& tempState() {
    static String t = base() + "sensor/sht31_temperature";
    return t;
  }

  const String& tempDiscovery() {
    static String t =
      "homeassistant/sensor/" + String(ProjectConfig::deviceName()) +
      "_sht31_temperature/config";
    return t;
  }

}