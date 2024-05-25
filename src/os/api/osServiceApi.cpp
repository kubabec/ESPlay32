#include "os/portableos.hpp"
#include "os/api/osServiceApi.hpp"

const std::function<bool(RuntimeApplication* overtakerPtr)> OS_SERVICE_API::contextOvertake =
    PortableOS::contextOvertake;


const std::function<void(void)> OS_SERVICE_API::contextRelease =
    PortableOS::contextRelease;