add_library(gsm GSM610Tables.cpp GSMCCCH.cpp GSMChannelHistory.cpp GSMCommon.cpp GSMConfig.cpp GSML1FEC.cpp GSML2LAPDm.cpp GSML3CCElements.cpp GSML3CCMessages.cpp GSML3CommonElements.cpp GSML3GPRSElements.cpp GSML3Message.cpp GSML3MMElements.cpp GSML3MMMessages.cpp GSML3RRElements.cpp GSML3RRMessages.cpp GSML3SSMessages.cpp GSMLogicalChannel.cpp GSMRadioResource.cpp GSMSMSCBL3Messages.cpp GSMTAPDump.cpp GSMTDMA.cpp GSMTransfer.cpp PhysicalStatus.cpp PowerManager.cpp)

target_link_libraries(gsm control)
