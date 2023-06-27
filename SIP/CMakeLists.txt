add_library(sip SIP2Interface.cpp SIPBase.cpp SIPDialog.cpp SIPMessage.cpp SIPParse.cpp SIPRtp.cpp SIPTransaction.cpp SIPUtility.cpp)

target_link_libraries(sip ortp)
