PROJECT(qnlp)

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src)
# 
# SET(CMAKE_BUILD_TYPE Debug) 
# 
SET(NLP_SRCS_LIBS
    ${CMAKE_SOURCE_DIR}/src/embeddings.cc
    ${CMAKE_SOURCE_DIR}/src/tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/fr_tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/en_tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/bpe.cc
    ${CMAKE_SOURCE_DIR}/src/utils.cc
)

SET(NLP_SRCS
    main_NLP.cc
    ${NLP_SRCS_LIBS}
)


add_executable(qnlp-x ${NLP_SRCS})

# SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
# SET(BUILD_SHARED_LIBRARIES OFF)
# SET(CMAKE_EXE_LINKER_FLAGS "-static")
target_link_libraries(qnlp-x fasttext boost_regex)
# 
# add_library(qnlp SHARED ${NLP_SRCS_LIBS})
# ADD_LIBRARY(qnlp-static STATIC ${NLP_SRCS_LIBS})
# 
# SET_TARGET_PROPERTIES(qnlp-static PROPERTIES OUTPUT_NAME qnlp)
# 
# install(TARGETS qnlp qnlp-static DESTINATION lib)
install(TARGETS qnlp-x DESTINATION bin)
# install(FILES ${CMAKE_SOURCE_DIR}/include/tokenizer.h ${CMAKE_SOURCE_DIR}/include/embeddings.h ${CMAKE_SOURCE_DIR}/include/bpe.h DESTINATION include/qnlp)
