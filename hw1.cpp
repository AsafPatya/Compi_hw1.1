#include <string>
#include <iostream>
#include "tokens.hpp"

#define COMMENT_LEXEME "//"

const char SKIP_CHAR = '\0';
const char MIN_CHAR_BOUND = '\x00';  // TODO- check the range
const char MAX_CHAR_BOUND = '\x7f';

bool isPrintableChar(char chr)
{
    return chr >= MIN_CHAR_BOUND && chr <= MAX_CHAR_BOUND;
}

std::string getEscapeSequence(const int escapeSequenceIndex)
{
    std::string sequence;
    const char* const firstChar = yytext + escapeSequenceIndex + 1;
    char* secondChar = yytext + escapeSequenceIndex + 2;

    if (firstChar != nullptr && *firstChar != '"') {
        sequence.push_back(*firstChar);
    } else {
        secondChar = nullptr;
    }

    if (secondChar != nullptr && *secondChar != '"') {
        sequence.push_back(*secondChar);
    }

    return sequence;
}

/// handles function - start

void handleWrongChar()
{
    const char* error_message = "ERROR";
    const char* lexeme = yytext;
    cout << error_message << " " << yytext <<  endl;
    exit(0);
}

void handleStartWithZero()
{
    const char* error_message = "ERROR";
    const char* lexeme = "0";
    cout << error_message << " " << yytext <<  endl;
    exit(0);
}

void handleUnclosedString()
{
    const char* error_message = "Error unclosed string";
    cout << error_message <<  endl;
    exit(0);
}

void handleInvalidEscapeSequenceError(const std::string& lexeme)
{
    // for handleEscapeSequence function
    const char* error_message = "Error undefined escape sequence";
    cout << error_message << " " << lexeme <<  endl;
    exit(0);
}

/// handles function - end




void printToken(const int token, const std::string& lexeme = yytext)
{
    std::cout << yylineno << " " << tokenNames[token] << " " << lexeme << std::endl;
}

char handleEscapeSequence(int& escapeSequenceIndex)
{
    escapeSequenceIndex++;
    switch (yytext[escapeSequenceIndex])
    {
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case '\\':
            return '\\';
        case '"':
            return '\"';
        case 'x':
        {
            std::string sequence = getEscapeSequence(escapeSequenceIndex);
            if (sequence.length() == 2 && isxdigit((int)yytext[escapeSequenceIndex + 1]) && isxdigit((int)yytext[escapeSequenceIndex + 2])) {  // check if the two following chars are hex
                char newChar = (char) std::stoi(sequence, nullptr, 16);
                escapeSequenceIndex += 2;

                if (isPrintableChar(newChar)) {  // check if the given sequence is printable
                    return newChar;
                }
            }
            handleInvalidEscapeSequenceError("x" + sequence);
            return SKIP_CHAR;
        }
        default:  // invalid escape sequence
            handleInvalidEscapeSequenceError(std::string(yytext + escapeSequenceIndex, 1));
            return SKIP_CHAR;
    }
}

void printStringToken()
{
    std::string stringLexeme;
    int stringIndex = 0;
    bool isNullInTheMiddle = false;

    while (yytext[stringIndex] != 0) {
        char newChar = yytext[stringIndex];

        if ((newChar == '\\' && yytext[stringIndex + 1] == '0') || (newChar == '\\' && yytext[stringIndex + 1] == 'x' && yytext[stringIndex + 2] == '0' && yytext[stringIndex + 3] == '0')) {  // https://piazza.com/class/l0tou1nunya1jn?cid=27
            isNullInTheMiddle = true;
        }

        else if (newChar == '\\') {
            newChar = handleEscapeSequence(stringIndex);

        } else if (newChar == '"') {  // this is the last char in the string
            printToken(STRING, stringLexeme);
            return;
        }

        if (!isNullInTheMiddle) {
            stringLexeme.push_back(newChar);
        }
        stringIndex++;
    }
    handleUnclosedString();

}



int main()
{
	int token;
	while ((token = yylex()))
    {
        switch (token)
        {
            case WRONG_CHAR:
                handleWrongChar(); // changed V
                break;

            case ZERO_FIRST:
                handleStartWithZero();  // changed V
                break;

            case UNCLOSED_STRING:  // changed V
                handleUnclosedString();
                break;

            case WHITESPACE:
                break;
            case STRING:
                printStringToken();
                break;
            case COMMENT:
                printToken(COMMENT, COMMENT_LEXEME);
                break;
            default:
                printToken(token);
                break;
        }
	}
	return 0;
}
