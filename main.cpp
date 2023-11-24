#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstring>
struct wordWithTranslation
{
    char word[6];
    int translation;
};

int inline translate(char word[])
{
    /**
    * We associate every char[] with 5 elements an int,
    * for example:
    *
    * for the word "fjord", we associate a 1 to a letter if
    * it exists in the word, otherwise 0

    * zy xwvu tsrq ponm lkji hgfe dcba
    * 00 0000 0010 0100 0010 0010 1000
    *
    * thus, the translation is the number whose binary
    * representation is equal to 00 0000 0010 0100 0010 0010 1000,
    * which is 148008
    */
    return (1<<(word[0]-'a'))
           | (1<<(word[1]-'a'))
           | (1<<(word[2]-'a'))
           | (1<<(word[3]-'a'))
           | (1<<(word[4]-'a'));
}
bool inline has5bits(int number)
{
    // count the number of bits set in v
    unsigned int v = number;
    // c accumulates the total bits set in v
    unsigned int c;

    for (c = 0; v; c++)
    {
        // clear the least significant bit set
        v &= v - 1;
    }
    return c == 5;
}
bool inline hasdifferentLettersThanFjordOrVibex(int number)
{
    return !( ((number & 10486034) || (number & 148008)) );

    /**
    * translate("fjord") = 148008;
    * translate("vibex") = 10486034
    */

    /**
    * when we are doing 'and' bit operation
    * the result is not null if they share letters in common
    */

    /**
    * a key optimization here is the '||' operator if the left
    * hand of the operator is true, the second part is not computed
    * and it saves computing power. Since 'vibex' has the letters 'e'
    * and 'i' which are very common in English words, we first evaluate
    * this part.
    */
}
bool inline dontShareLetters(int first, int second)
{
    return !(first & second);
}

bool inline onlyHasA(int number)
{
    return (number & 17825793) == 1;
}
bool inline onlyHasU(int number)
{
    return (number & 17825793) == 1048576;
}
int inline vowelPlaceValue(char c[])
{
    /**
    * In the problem it is specified that every word has at least a vowel,
    * because there is no consonant-consonant-consonant value.
    *
    * Since vibex has two vowels and fjord has 1, we already used 3 of them,
    * and since all 25 letters are unique, we know that there can be only one
    * vowel per word.
    */
    if(strchr("aeiouy", c[1]))
    {
        return 20;
    }
    if(strchr("aeiouy", c[2]))
    {
        return 15;
    }
    if(strchr("aeiouy", c[3]))
    {
        return 5;
    }
}
void inline dispalyTripLength(wordWithTranslation y, wordWithTranslation u, wordWithTranslation a)
{
    std::cout<<"For the pair: fjord, vibex, "
             <<y.word <<", "
             <<u.word <<", "
             <<a.word <<'\n';

    int total = 10486034
                | 148008
                | y.translation
                | u.translation
                | a.translation;
    int c = 1;
    for (; (total & 1); c++)
    {
        total = total >> 1;
    }

    ///in total now we store the total number of hours needed
    total =
        + vowelPlaceValue(y.word)
        + vowelPlaceValue(u.word)
        + vowelPlaceValue(a.word);

    std::string dayArray[] = {"Monday", "Tuesday"
                              , "Wednesday", "Thursday"
                              , "Friday", "Saturday"
                              , "Sunday"
                             };
    std::string hourArray[] = {"12am", "1am", "2am", "3am"
                               , "4am", "5am", "6am", "7am"
                               , "8am", "9am", "10am", "11am"
                               , "12pm", "1pm", "2pm", "3pm"
                               , "4pm", "5pm", "6pm", "7pm"
                               , "8pm", "9pm", "10pm", "11pm"
                              };
    ///the start will be Monday 00
    total += 32 + c;

    int timeFromMonday = total - 6;


    std::cout<<"The trip is taking "<< total<<"hours\n";
    std::cout<<"The arrival time is "<<dayArray[(timeFromMonday/24)%7]
             <<" at "<< hourArray[timeFromMonday%24]<< "\n\n";
}
int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream fin("word_list.txt");

    wordWithTranslation a[1000];
    wordWithTranslation u[1000];
    wordWithTranslation y[1000];

    int sizeOfA = 0;
    int sizeOfU = 0;
    int sizeOfY = 0;

    char s[6];
    while(fin>>s)
    {
        int translation = translate(s);

        if(hasdifferentLettersThanFjordOrVibex(translation)
                && has5bits(translation))
        {
            //std::cout<<s<<" "<<'\n';
            /**
            * it is preferably to move char by char
            * than to use strcpy() from cstring
            * in order to improve runtime
            */
            int translationForVowelChecking = translation & 17825793;
            if(translationForVowelChecking == 16777216)
            {
                y[sizeOfY].word[0] = s[0];
                y[sizeOfY].word[1] = s[1];
                y[sizeOfY].word[2] = s[2];
                y[sizeOfY].word[3] = s[3];
                y[sizeOfY].word[4] = s[4];
                y[sizeOfY].word[5] = 0;
                y[sizeOfY].translation = translation;

                sizeOfY++;

            }
            else
            {
                if(translationForVowelChecking == 1048576)
                {
                    u[sizeOfU
                     ].word[0] = s[0];
                    u[sizeOfU].word[1] = s[1];
                    u[sizeOfU].word[2] = s[2];
                    u[sizeOfU].word[3] = s[3];
                    u[sizeOfU].word[4] = s[4];
                    u[sizeOfU].word[5] = 0;
                    u[sizeOfU].translation = translation;

                    sizeOfU++;
                }
                else
                {
                    if(translationForVowelChecking == 1)
                    {
                        a[sizeOfA].word[0] = s[0];
                        a[sizeOfA].word[1] = s[1];
                        a[sizeOfA].word[2] = s[2];
                        a[sizeOfA].word[3] = s[3];
                        a[sizeOfA].word[4] = s[4];
                        a[sizeOfA].word[5] = 0;
                        a[sizeOfA].translation = translation;

                        sizeOfA++;
                    }
                }
            }
        }
    }

    auto readingDone = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(readingDone - start);
    std::cout << "Initialize all data structures time: " << duration.count()/1000.0 << std::setprecision(6) << "miliseconds\n\n";

    for(int i = 0; i < sizeOfY; i++)
    {
        for(int j = 0; j < sizeOfU ; j++)
        {
            if(dontShareLetters(y[i].translation,u[j].translation))
            {
                for(int k = 0; k < sizeOfA; k++)
                {
                    if(dontShareLetters(y[i].translation,a[k].translation)
                            && dontShareLetters(u[j].translation,a[k].translation))
                    {
                        dispalyTripLength(y[i], u[j], a[k]);
                    }
                }
            }

        }
        //
    }
    /**
    auto doneCreatingPairs = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(doneCreatingPairs - readingDone);
    std::cout << "Search for pairs of words time: " << duration.count()/1000.0
              << std::setprecision(6) << "miliseconds\n";
    **/
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<< "Execution time: " << duration.count()/1000.0 << std::setprecision(6) << "miliseconds\n";
    return 0;

}
