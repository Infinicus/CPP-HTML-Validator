//HTML Validator. Prints valid and not valid.
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#define ARR_SIZE 100

using namespace std;

bool isNotSingleKeyword(string tags)                                                //Function to check if tag is not single keyword
{
    int keyword_count = 13;
    string single_keyword[keyword_count] = {"area", "base", "br", "col", "hr", "img", "input", "link", "meta", "param", "command", "keygen", "source"};  //HTML5 single keywords
    for(int i = 0; i < keyword_count; i++)
    {
        if(tags != single_keyword[i]) {}                                            //Loops through keywords. If tags is the same
        else                                                                        //as one of the keywords, return false.
            return false;

        if(i == keyword_count)                                                      //If looped through all keywords, then TRUE
            return true;
    }
}

void printHTML(char line)                                                           //Function to print the HTML as it is
{
    if(line == '>')
        cout << line << endl;
    else
        cout << line;
}

void printStack(stack<string> string_stack)                                         //Function to print stack
{
    cout << "\nPrint Stack:" << endl;
    do
    {
        if(string_stack.empty())
        {
            cout << "Stack Empty!" << endl;
            break;
        }
        cout << string_stack.top() << endl;
        string_stack.pop();
    }while(!string_stack.empty());
}

int main()
{
    ifstream htmlfile("index.html");                                                //input
    stack<string> tags_stack;
    string tags, line;
    char char_tags[ARR_SIZE];

    if(htmlfile.is_open())                                                          //Checks if file exists
    {
        while(getline(htmlfile, line))                                              //Loops through the file
        {
            size_t pos_open = line.find('<');                                       //position of the tags

            for(int tags_counter = 0; tags_counter < ARR_SIZE; tags_counter++)      //Loops through a line to check if there are multiple tags in one
            {                                                                       //line. (Max 100 tags)
                int n = 0;
                pos_open = line.find('<', pos_open + tags_counter);                 //Position of the tags with + counter where + 1 is the next pos

                if(pos_open != string::npos)                                        //check for open tag (<), if tag is found, execute.
                {
                    for(int i = pos_open; line[i-1] != '>'; i++)                    //Ignores the indentations and reads until '>'
                    {
                        //Function to print HTML as it is (for checking)
                        //printHTML(line[i]);

                        if(line[i] != '<' && line[i] != '>' && line[i] != '/')      //ignore these symbols
                        {
                            char_tags[n] = line[i];                                 //Assign char_tags as the same value as the HTML tags
                            n++;
                        }
                    }
                    tags = char_tags;                                               //Copy the char_tags array to string since the stack is <string> type

                    //Condition when stack is empty or top stack is not a closing tag and tag is not a single keyword.
                    if((tags_stack.empty() || tags_stack.top() != tags) && isNotSingleKeyword(tags))
                        tags_stack.push(tags);                                      //Push tags to the stack as a string.
                    else if(tags_stack.top() == tags)                               //If the top stack is the same as tags, then
                        tags_stack.pop();                                           //pops the top stack, "marking" it closed.

                    printStack(tags_stack);                                         //Prints stack to know the current condition of stack.

                    for(int i = 0; i < ARR_SIZE; i++)                               //Resets the char_tags members.
                        char_tags[i] = NULL;
                }
                else
                    break;                                                          //Breaks if no further tags are found in that line
            }
        }

        if(tags_stack.empty()) cout << "\nDocument is valid!" << endl;              //Validation
                    else cout << "\nDocument is not valid!" << endl;

    }
    else
        cout << "File not found!" << endl;                                          //ptinrs file not found

    return 0;
}

//Giga Hidjrika Aura Adkhy
//16/03/2022
