PROJECT(qnlp)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(/usr/local/lib)
SET(NLP_SRCS
    main_NLP.cc
)

SET(FILTERING_SRCS
    main_filtering.cc
)


add_executable(qnlp-x ${NLP_SRCS})
add_executable(qnlp-filtering ${FILTERING_SRCS})

target_link_libraries(qnlp-x fasttext boost_regex snowball qnlp sentencepiece)
target_link_libraries(qnlp-filtering boost_regex qnlp)
install(TARGETS qnlp-x qnlp-filtering DESTINATION bin)
