PROJECT(qnlp-toolkit)

SET(NLP_SRCS_LIBS
    ${PROJECT_SOURCE_DIR}/src/embeddings.cc
    ${PROJECT_SOURCE_DIR}/src/tokenizer.cc
    ${PROJECT_SOURCE_DIR}/src/fr_tokenizer.cc
    ${PROJECT_SOURCE_DIR}/src/en_tokenizer.cc
    ${PROJECT_SOURCE_DIR}/src/bpe.cc
    ${PROJECT_SOURCE_DIR}/src/stopwords.cc
    ${PROJECT_SOURCE_DIR}/src/utils.cc
)


add_library(qnlp SHARED ${NLP_SRCS_LIBS})
ADD_LIBRARY(qnlp-static STATIC ${NLP_SRCS_LIBS})

target_link_libraries(qnlp fasttext)
target_link_libraries(qnlp-static fasttext)

SET_TARGET_PROPERTIES(qnlp-static PROPERTIES OUTPUT_NAME qnlp)

install(TARGETS qnlp qnlp-static DESTINATION lib)

install(FILES ${PROJECT_SOURCE_DIR}/include/tokenizer.h ${PROJECT_SOURCE_DIR}/include/embeddings.h ${PROJECT_SOURCE_DIR}/include/bpe.h ${PROJECT_SOURCE_DIR}/include/fr_tokenizer.h ${PROJECT_SOURCE_DIR}/include/en_tokenizer.h ${PROJECT_SOURCE_DIR}/include/utils.h ${PROJECT_SOURCE_DIR}/include/processor.h ${PROJECT_SOURCE_DIR}/include/stopwords.h DESTINATION include/qnlp)
install(FILES ${PROJECT_SOURCE_DIR}/include/utf8/core.h ${PROJECT_SOURCE_DIR}/include/utf8/checked.h ${PROJECT_SOURCE_DIR}/include/utf8/unchecked.h ${PROJECT_SOURCE_DIR}/include/utf8/utf8.h DESTINATION include/qnlp/utf8)
