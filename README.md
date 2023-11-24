# HelinDataPuzzle
The algorithm below is a submission to the Helin's puzzle. The main challenge is to find all pairs of 5 words with 25 unique letters from a list of words, where 2 of them are "fjord" and "vibex", as efficient as possbile.

There are about 13 000 words in the list. Trying to form all possible combinations would be a waste of time, thus, we need reduce the number of elligeble elements. I have implemented the following criterias for a word to be considered in the pair making process:
1. The word does not contain the letters "fjordvibex"
2. The word has 5 unique letters
3. The word has only a vowel
   
Altough there are words which do not have a vowel in the list
<img width="592" alt="image" src="https://github.com/MihaiBobeica/HelinDataPuzzle/assets/77356043/16123bd6-4301-4e4f-9238-b2ef8ad319a8">


