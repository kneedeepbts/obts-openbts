add_library(control CBS.cpp ControlTransfer.cpp DCCHDispatch.cpp L3CallControl.cpp L3Handover.cpp L3LogicalChannel.cpp L3MMLayer.cpp L3MobilityManagement.cpp L3SMSControl.cpp L3StateMachine.cpp L3SupServ.cpp L3TermCause.cpp L3TranEntry.cpp L3Utils.cpp PagingEntry.cpp RRLPServer.cpp TMSITable.cpp)

target_link_libraries(control sqlite3)
