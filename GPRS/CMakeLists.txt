add_library(gprs BSSG.cpp BSSGMessages.cpp ByteVector.cpp FEC.cpp GPRSCLI.cpp MAC.cpp MsgBase.cpp MSInfo.cpp RLC.cpp RLCEngine.cpp RLCMessages.cpp TBF.cpp)

target_link_libraries(gprs sgsnggsn)
