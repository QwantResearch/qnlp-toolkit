# Qnlp-ToolKit

This toolkit ais to assemble the whole tools and libraries available for NLP rpocessing at Qwant.

# Tools available
## qtokenizer
The very first step for every NLP process is a tokenizer: a tool which segement text into tokens. These tokens  can be words or set of words. For example, "c'est-à-dire" or "aujourd'hui" are a tokens. The tokenizations rules are available for every european languages, but specific rules have been written for French and English.
### TODO
To be possible to tokenize asian, indi, african and arabic languages.
### References
> [Zalmout, 2017]	Nasser Zalmout and Nizar Habash: "Optimizing Tokenization Choice for Machine Translation across Multiple Target Languages", In The Prague Bulletin of Mathematical Linguistics, Vol. 108, June 2017.

## qfasttext wrapper
This part enable to use Facebook's fasttext toolkit to extract vector representation (embeddings) for words, queries, sentences, paragraphs and documents.
### TODO
Enhance the fasttext wrapper to add some GPU processing (which should be more faster) and add several features to enhance embeddings.
### References
> [Joulin, 2016a]	Armand Joulin, Edouard Grave, Piotr Bojanowski and Tomas Mikolov: "Enriching Word Vectors with Subword Information", arXiv preprint arXiv:1607.04606, 2016
> [Joulin, 2016b]	Armand Joulin, Edouard Grave, Piotr Bojanowski and Tomas Mikolov: "Bag of Tricks for Efficient Text Classification", arXiv preprint arXiv:1607.01759, 2016
> [Joulin, 2016c]	Armand Joulin, Edouard Grave, Piotr Bojanowski, Matthijs Douze,  Hervé Jégou and Tomas Mikolov: "FastText.zip: Compressing text classification models", arXiv preprint arXiv:1612.03651, 2016


## qBPE 
This a wrapper the the Byte Pair Encoding algorithme applied to words. The main objective of this tool is to reduce the vocabulary for Neural Machine Translation toolkits. Limiting inputs and outputs enable to train faster and more accurate models.
### TODO
To propose a BPE training step.
### References
> [Sennrich, 2016a]	Rico Sennrich, Barry Haddow and Alexandra Birch: "Neural Machine Translation of Rare Words with Subword Units" in Proceedings of the 54th Annual Meeting of the Association for Computational Linguistics (ACL 2016). Berlin, Germany, 2016. qtokenizer
