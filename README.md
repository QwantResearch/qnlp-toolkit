# Qnlp-ToolKit

This toolkit ais to assemble the whole tools and libraries available for NLP pre-processing at Qwant.

## Installation
Automatic installation with the script: 
> install.sh [-h] [-g] [-p PREFIX] <br>
>&nbsp;&nbsp;&nbsp;&nbsp;-h&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;help <br>
>&nbsp;&nbsp;&nbsp;&nbsp;-p PREFIX&nbsp;&nbsp;&nbsp;&nbsp;specify a prefix (default /usr/local/) <br>



# Tools available
## qtokenizer
The very first step for every NLP process is a tokenizer: a tool which segement text into tokens. These tokens  can be words or set of words. For example, "c'est-à-dire" or "aujourd'hui" are a tokens. The tokenizations rules are available for every european languages, but specific rules have been written for French and English.
## qfiltering
Enable to filter bitext* according the sentence length, the sentence length ratio and other tricks.
> *bitext: two bilingual corpora aligned sentence by sentence, the second one is the translation of the first one. They are used as training corpora for Neural Machine Translation
### TODO
To be possible to tokenize asian, indi, african and arabic languages.

### References
> [Zalmout, 2017]	Nasser Zalmout and Nizar Habash: "Optimizing Tokenization Choice for Machine Translation across Multiple Target Languages", In The Prague Bulletin of Mathematical Linguistics, Vol. 108, June 2017.
>
## qStemmer
For many users, one needs a stemmer for Information Retreival. As State-of-the-Art stemmer, we included the Snowball Stemmer, for all language available.
### References
http://snowballstem.org/

## qStopWords
In Information Retrieval, it is common to use stop-words list. This is now part of the qnlp-toolkit, for French, English, Portugese, Italian, Spanish and Dutch. The list comes from the website https://www.ranks.nl

### References
https://www.ranks.nl
### TODO
Add other european languages.

