#add_subdirectory(poll)
#add_subdirectory(service)

aux_source_directory(. HYPER_NET_SOURCE)
aux_source_directory(./poll HYPER_NET_POLL_SOURCE)
aux_source_directory(./service HYPER_NET_SERVICE_SOURCE)
aux_source_directory(./protocols HYPER_NET_PROTOCOLS_SOURCE)
aux_source_directory(./common HYPER_NET_COMMON_SOURCE)
#link_directories(net ${HYPER_NET_SOURCE})

add_library(net ${HYPER_NET_SOURCE} ${HYPER_NET_POLL_SOURCE}
        ${HYPER_NET_PROTOCOLS_SOURCE} ${HYPER_NET_SERVICE_SOURCE} ${HYPER_NET_COMMON_SOURCE})

#target_link_libraries(net hypernetpoll hypernetservice)