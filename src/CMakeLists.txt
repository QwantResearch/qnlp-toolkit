PROJECT(qnlp-toolkit)

SET(NLP_SRCS_LIBS
    ${CMAKE_SOURCE_DIR}/src/embeddings.cc
    ${CMAKE_SOURCE_DIR}/src/tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/fr_tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/en_tokenizer.cc
    ${CMAKE_SOURCE_DIR}/src/bpe.cc
    ${CMAKE_SOURCE_DIR}/src/utils.cc
)


add_library(qnlp SHARED ${NLP_SRCS_LIBS})
ADD_LIBRARY(qnlp-static STATIC ${NLP_SRCS_LIBS})

target_link_libraries(qnlp fasttext)
target_link_libraries(qnlp-static fasttext)

SET_TARGET_PROPERTIES(qnlp-static PROPERTIES OUTPUT_NAME qnlp)

install(TARGETS qnlp qnlp-static DESTINATION lib)

install(FILES ${CMAKE_SOURCE_DIR}/include/tokenizer.h ${CMAKE_SOURCE_DIR}/include/embeddings.h ${CMAKE_SOURCE_DIR}/include/bpe.h ${CMAKE_SOURCE_DIR}/include/fr_tokenizer.h ${CMAKE_SOURCE_DIR}/include/en_tokenizer.h ${CMAKE_SOURCE_DIR}/include/utils.h ${CMAKE_SOURCE_DIR}/include/processor.h DESTINATION include/qnlp)
install(FILES ${CMAKE_SOURCE_DIR}/include/utf8/core.h ${CMAKE_SOURCE_DIR}/include/utf8/checked.h ${CMAKE_SOURCE_DIR}/include/utf8/unchecked.h ${CMAKE_SOURCE_DIR}/include/utf8/utf8.h DESTINATION include/qnlp/utf8)
