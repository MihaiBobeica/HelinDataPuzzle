# HelinDataPuzzle
The algorithm below is a submission to the Helin's puzzle. The main challenge is to find all pairs of 5 words with 25 unique letters from a list of words, where 2 of them are "fjord" and "vibex", as efficient as possbile.

There are about 13 000 words in the list. Trying to form all possible combinations would be a waste of time, thus, we need reduce the number of elligeble elements. I have implemented the following criteria for a word to be considered in the pair making process:
1. The word does not contain the letters "fjordvibex"
2. The word has 5 unique letters
3. The word has only a vowel
   
Altough there are words which do not have a vowel in the list, such as the one listed below, there is no need to consider them. After we find a pair, we need to calculate a cost based on the letters in the word. This cost is not defined for words which do not have vowels.


<img width="592" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/16123bd6-4301-4e4f-9238-b2ef8ad319a8">

Since every word must have a vowel and "vibex" already used two, we know that in the final pair there must be a word which only has the vowel 'a", one which only has the vowel 'u', and one which only has the vowel 'y'. I've created 3 arrays to store all the elements by their vowel type name a, u, and y. The number of entries in these arrays are as follows:
1. There are 178 words with contains the letter 'a'
2. There are 84 words with contains the letter 'u'
3. There are 13 words with contains the letter 'y' 

Thus, we need to check only a total of 194 376, which is still a lot, but manageable. It is definetly better than $2197 * 10^9$.

To further optimize the code, we need to implement the 3 criteria efficiently. I do this by associating every word a positive integer in a process called translation. The $n$-th bit is $1$ if the $(n + 1)$-th letter of the alphabet is in the word, otherwise it is $0$. Below you can find the example for the word "fjord", which has the translation $148008$.


<img width="220" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/e81594c1-3b19-4e50-8532-e601faf13947">

This vertical encoding of data allows us to do bit manipulations in order to apply the criteria. If we consider two words named word1 and word2 whose translations are $trans1$ and $trans2$, then we can use bit operations to perform the following task:
1. The translation of word1 can be done by OR-ing the translations of each letters.
2. word1 has 5 different letters if and only if its translation has 5 bits. To do this, we remove the least significant using [bit operations](https://stackoverflow.com/questions/47779830/what-does-bitwise-operation-nn-1-do).
3. Checking for two word to have different letters can be done using NOT ($trans1$ AND $trans2) == 0$. This operations results in $true$ if there is no bit set to $1$ in both number, otherwise in $false$.
4. Checking for the presence of only a vowel can be done by 
