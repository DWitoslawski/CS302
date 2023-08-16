/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 4: Use unordered_maps to store keywords and category values. Once
    the maps are created, use them in order to read through description text
    and map those words to category keywords. If description text has the right
    amount of keywords for a category, then that category is properly applicable,
    and it will be printed to the console.
 Input: Input txt file that has information about number of cases, number of
    categories per case, category names, number of keywords in that category,
    number of keywords needed to be matched for a proper categorization, keywords,
    and description text to be parsed through.
 Output: If the description text has enough keywords from a specific category,
    this program will output that category name.
 *******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

int main() {
    std::vector<std::string> listOfCategories; // Keeps categories in the order they appear in input
    std::vector<int> keyWordNums; // Matches the needed value (P) with the category at index j of listOfCategories
    std::unordered_map<std::string, std::string> keyWordMap; // Stores key-value pairs of <keyword, category>
    // accessMap keeps track of if a description word has been access in keyWordMap already (prevent duplicates)
    // categoryMap is used to match category strings with how many time a category has been matched to a description word <category, counter>
    std::unordered_map<std::string, int> accessMap, categoryMap;

    int numCases, numCategories, numWordsInCat, keyWordNum;
    std::string category, keyWord;

    std::cin >> numCases;

    /*
     * Large looping structure with 3 nested layers (one for number
     * of cases, one for number of categories, and one for number of
     * words in each category) that will populate an unordered_map
     * structure that will be populated with the keywords for that
     * case. Different categories are represented by a string that
     * maps to the keyWord. Once the maps are populated, description
     * text will be read to map each word to a category (if applicable).
     * If a category has been matched the correct number of times, that
     * category will be printed to the console.
     */

    // outermost loop to loop through the cases
    for (int i = 0; i < numCases; i++)
    {
        std::cin >> numCategories;

        // loop that loops through each category and pushes category and keyWordNum into vectors (to save them for later)
        for (int j = 0; j < numCategories; j++)
        {
            std::cin >> category >> numWordsInCat >> keyWordNum;
            listOfCategories.push_back(category);
            keyWordNums.push_back(keyWordNum);

            //loop that loops through the words in each category, then populates keyWordMap with <string keyword, string category>
            for (int k = 0; k < numWordsInCat; k++)
            {
                std::cin >> keyWord;
                keyWord[i] = tolower(keyWord[i]);
                keyWordMap[keyWord] = category;
            }
        }

        // Initialize description to not be empty so that the loop will start
        std::string description = "lol";

        // Clear input so that getline will work properly
        std::cin.ignore();

        /*
         * Loop to parse through the description lines, then search keyWordMap to see if
         * that key has a category value associated with it. If it does, then use value
         * associated with the keyword from keyWordMap (which is a category) as input into
         * categoryMap <string category, int counter>, and increment the counter.
         */
        while (!description.empty())
        {
            std::getline(std::cin, description);
            std::istringstream iss(description);
            while (std::getline(iss, keyWord, ' '))
            {
                keyWord[i] = tolower(keyWord[i]);
                //std::transform(keyWord.begin(), keyWord.end(), keyWord.begin(), ::tolower);

                if (keyWordMap[keyWord] != "" && accessMap[keyWord] == 0)
                {
                    categoryMap[keyWordMap[keyWord]] += 1;
                    accessMap[keyWord] ++;
                }
            }

        }

        bool matches = false;

        std::cout << "\nTest Case " << i + 1 << std::endl;


        /* Iterate through categories and keyWordNums vectors. if the value
         * P that corresponds to the category at index j is the same as the
         * value that is stored in categoryMap at key[category], then print
         * the category name. If no categories are printed, print SQF problem
         */
        for (int j = 0; j < numCategories; j++)
        {
            if (categoryMap[listOfCategories[j]] == keyWordNums[j])
            {
                std::cout << listOfCategories[j] << std::endl;
                matches = true;
            }
        }

        if (!matches)
            std::cout << "SQF Problem" << std::endl;

        // Iterate through vectors and depopulate them
        for (auto i : listOfCategories)
        {
            listOfCategories.pop_back();
            keyWordNums.pop_back();
        }

        // Iterate through hashmaps and set second values to default

        for (auto &j : keyWordMap)
            j.second = "";

        for (auto &j : categoryMap)
            j.second = 0;

        for (auto &j : accessMap)
            j.second = 0;
    }

    return 0;
}


/*
        std::cout << "\nHashmap of keyWordMap pairs:\n";
        for (auto i: keyWordMap)
            std::cout << i.first << ":" << i.second << std::endl;

        std::cout << "\nHashmap of accessMap pairs:\n";
        for (auto i: accessMap)
            std::cout << i.first << ":" << i.second << std::endl;

        std::cout << "\nHashmap of categoryMap pairs:\n";
        for (auto i: categoryMap)
            std::cout << i.first << ":" << i.second << std::endl;
*/