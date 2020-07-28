PROJECT(qnlp)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(/usr/local/lib)
SET(NLP_SRCS
    main_NLP.cpp
)

SET(FILTERING_SRCS
    main_filtering.cpp
)


add_executable(qtokenizer ${NLP_SRCS})
add_executable(qfiltering ${FILTERING_SRCS})

target_link_libraries(qtokenizer boost_regex snowball qnlp)
target_link_libraries(qfiltering boost_regex qnlp)
install(TARGETS qtokenizer qfiltering DESTINATION bin)
