# HelinDataPuzzle
The algorithm found in main.cpp is a submission to the Helin's puzzle. The main challenge is to find all pairs of 5 words with 25 unique letters from a list of words, where 2 of them are "fjord" and "vibex", as efficiently as possible.
## Decreasing the number of words considered in the pair making process

There are about 13 000 words in the list. Trying to form all possible combinations would be a waste of time, thus, we need to reduce the number of eligible elements. I have implemented the following criteria for a word to be considered in the pair making process:
1. The word does not contain the letters "fjordvibex"
2. The word has 5 unique letters
3. The word has only 1 vowel
   
Altough there are words which do not have a vowel in the list, such as the one listed below, there is no need to consider them. After we find a pair, we need to calculate a cost based on the letters in the word. This cost is not defined for words which do not have vowels.


<img width="592" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/16123bd6-4301-4e4f-9238-b2ef8ad319a8">

Since every word must have a vowel and "vibex" already has two, we know that in the final pair there must be a word which only has the vowel 'a", one which only has the vowel 'u', and one which only has the vowel 'y'. I've created 3 arrays to store all the elements by their vowel type named a, u, and y. The number of entries in these arrays are as follows:
1. There are 178 words which contain the letter 'a'
2. There are 84 words which contain the letter 'u'
3. There are 13 words which contain the letter 'y' 

Thus, we need to check only a total of $194 376$ pairs, which is still a lot, but manageable. It is definitely better than $2197 * 10^9$.

## Introducing bitwise operations

To further optimize the code, we need to implement the 3 criteria efficiently. I do this by associating a positive integer to every word in a process called translation. The $n$-th bit is $1$ if the $(n + 1)$-th letter of the alphabet is in the word, otherwise it is $0$. Below you can find the example for the word "fjord", which has the translation $148008$.


<img width="220" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/e81594c1-3b19-4e50-8532-e601faf13947">

This vertical encoding of data allows us to do bit manipulations in order to apply the criteria. If we consider two words named word1 and word2 whose translations are $trans1$ and $trans2$, we can use bit operations to perform the following task:
1. The translation of word1 can be done by OR-ing the translations of each letters.
2. word1 has 5 different letters if and only if its translation has 5 bits. To do this, we remove the least significant using [bit operations](https://stackoverflow.com/questions/47779830/what-does-bitwise-operation-nn-1-do).
3. word1 and word2 have different letters if and only if ($trans1$ AND $trans2) == 0$. This operations results in $true$ if there is no bit set to $1$ in both number, otherwise in $false$.

There are many more applications of bitwise operation in the submission algorithm, but somehow similar to the ones mentioned above. Another optimization is the order of the operands in logical expression. We prioritize conditions which are less probable to hold by placing them first in the logical expression. More information can be found on the Wikipedia page of [Lazy evaluation](https://en.wikipedia.org/wiki/Lazy_evaluation#Applications).

## Perfomance statistics

I've run the program 10 times on my machine and the results are attached below. I have used the built in high_resolution_clock to keep track of how much time I spent on each major task of the problem. On average, the algorithm spends:

0,5773ms on reading from the file and generating the arrays: a, u, and y	

0,6844ms on finding all the pairs

1,33932ms in total

<img width="608" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/32c016ed-68e6-4afc-81f6-900ff3eaf83c">

## Remarks
### Displaying time
Displaying how much time the alghorithm spends on each stage takes around 0.08ms. This calculation is derived using the following formula:
$$t_{\text{time display}} = \frac{t_{\text{total}} - t_{\text{reading}} - t_{\text{pair making}}}{\text{no of time displays}}$$
As a result, if the algorithm were to run without keeping track of the time it takes to run, we would decrease the time by 0.24ms, on average, on each run.

### File input
In the file provided by Helin (which is also the one included in this repository) on line 2314 there are two five letters words on the same line not separated by anything. However, I will assume that there is no need to check that a word has exactly 5 letters, because this event only occurs once in the file (and also because it would increase the run time). 
