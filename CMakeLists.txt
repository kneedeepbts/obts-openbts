cmake_minimum_required(VERSION 3.25)
project(obts_openbts)

set(CMAKE_CXX_STANDARD 20)

include_directories(CommonLibs TRXManager GSM GPRS GSMShare SIP Control CLI Globals Peering NodeManager NodeManager/JsonBox-0.4.3/include SGSNGGSN SMS)

add_subdirectory(Control)

add_subdirectory(CLI)
add_subdirectory(CommonLibs)
add_subdirectory(Globals)
add_subdirectory(GPRS)
add_subdirectory(GSM)
add_subdirectory(GSMShare)
add_subdirectory(NodeManager)
add_subdirectory(Peering)
add_subdirectory(Scanning)
add_subdirectory(SGSNGGSN)
add_subdirectory(SIP)
add_subdirectory(SMS)
#Transceiver52M
#TransceiverRAD1
add_subdirectory(TRXManager)

add_subdirectory(apps)
add_executable(obts_openbts apps/OpenBTS.cpp apps/GetConfigurationKeys.cpp)

target_link_libraries(obts_openbts cli commonlibs control globals gprs gsm gsmshare nodemanager peering scanning sgsnggsn sip sms trxmanager)

