set(headers ${headers} ../src/NavRouting
)
set(currsources
  ../src/NavRouting/CMakeLists.txt
  ../src/NavRouting/NavRouting.h
  ../src/NavRouting/NavRoutingCurrentDirectionSetMessage.cpp
  ../src/NavRouting/NavRoutingCurrentDirectionSetMessage.h
  ../src/NavRouting/NavRoutingCurrentDirectionUpdatedMessage.cpp
  ../src/NavRouting/NavRoutingCurrentDirectionUpdatedMessage.h
  ../src/NavRouting/NavRoutingSelectedDirectionSetMessage.cpp
  ../src/NavRouting/NavRoutingSelectedDirectionSetMessage.h
  ../src/NavRouting/NavRoutingEndLocationClearClickedMessage.h
  ../src/NavRouting/NavRoutingEndLocationClearedMessage.h
  ../src/NavRouting/NavRoutingEndLocationSetMessage.cpp
  ../src/NavRouting/NavRoutingEndLocationSetMessage.h
  ../src/NavRouting/NavRoutingModeSetMessage.cpp
  ../src/NavRouting/NavRoutingModeSetMessage.h
  ../src/NavRouting/NavRoutingRemainingRouteDurationSetMessage.cpp
  ../src/NavRouting/NavRoutingRemainingRouteDurationSetMessage.h
  ../src/NavRouting/NavRoutingRerouteDialogClosedMessage.cpp
  ../src/NavRouting/NavRoutingRerouteDialogClosedMessage.h
  ../src/NavRouting/NavRoutingRouteClearedMessage.h
  ../src/NavRouting/NavRoutingRouteChangedMessage.cpp
  ../src/NavRouting/NavRoutingRouteChangedMessage.h
  ../src/NavRouting/NavRoutingSelectedDirectionChangedMessage.cpp
  ../src/NavRouting/NavRoutingSelectedDirectionChangedMessage.h
  ../src/NavRouting/NavRoutingSelectEndLocationClickedMessage.h
  ../src/NavRouting/NavRoutingSelectStartLocationClickedMessage.h
  ../src/NavRouting/NavRoutingShowRerouteDialogMessage.cpp
  ../src/NavRouting/NavRoutingShowRerouteDialogMessage.h
  ../src/NavRouting/NavRoutingStartEndRoutingButtonClickedMessage.h
  ../src/NavRouting/NavRoutingStartLocationClearClickedMessage.h
  ../src/NavRouting/NavRoutingStartLocationClearedMessage.h
  ../src/NavRouting/NavRoutingStartLocationSetMessage.cpp
  ../src/NavRouting/NavRoutingStartLocationSetMessage.h
  ../src/NavRouting/NavRoutingViewClosedMessage.h
  ../src/NavRouting/NavRoutingViewOpenedMessage.h
  ../src/NavRouting/NavRoutingViewOpenMessage.cpp
  ../src/NavRouting/NavRoutingViewOpenMessage.h
  ../src/NavRouting/NavRoutingViewStartEndLocationSwappedMessage.h
  ../src/NavRouting/NavigateToMessage.cpp
  ../src/NavRouting/NavigateToMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting FILES ${currsources})
include(../src/NavRouting/SdkModel/CMakeLists.txt)
include(../src/NavRouting/View/CMakeLists.txt)
