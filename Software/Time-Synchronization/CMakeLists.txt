cmake_minimum_required(VERSION 3.0.0)
project(caas_tsn VERSION 0.1.0)

# SET(CMAKE_BUILD_TYPE Debug)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})


set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O0 -Wall -lpthread -lm  -march=native -DLOG_USE_COLOR")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O0 -Wall -lpthread -lm  -march=native -DLOG_USE_COLOR")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g3 -Wall -lpthread -lm -march=native -DLOG_USE_COLOR")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g3 -Wall -lpthread -lm  -march=native -DLOG_USE_COLOR")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/dma_proxy" 
"${PROJECT_SOURCE_DIR}/time_sync"
"${PROJECT_SOURCE_DIR}/log"
"${PROJECT_SOURCE_DIR}/tsn_drivers"
)

link_directories("${PROJECT_SOURCE_DIR}/lib")

add_library(${PROJECT_NAME} SHARED
dma_proxy/buffer_queue.c
dma_proxy/dma-proxy.c
tsn_drivers/gpio_reset.c
tsn_drivers/ptp_types.c
tsn_drivers/tagger.c
tsn_drivers/gcl.c
tsn_drivers/switch_rules.c
tsn_drivers/tsu.c
tsn_drivers/rtc.c
tsn_drivers/uio.c
log/log.c
config.c
topo.cpp
)


add_executable(time_sync_app time_sync_main_loop.c)
target_link_libraries(time_sync_app ${PROJECT_NAME} time_sync)

add_executable(switch_config switch_config_main.c)
target_link_libraries(switch_config ${PROJECT_NAME} time_sync)