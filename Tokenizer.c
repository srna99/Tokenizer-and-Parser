/*
 * Tokenizer.c
 */

#include "Tokenizer.h"
#include <string.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	char input[MY_CHAR_MAX];
	int count = 0; //for num of lex
	int lexInd = 0; //index for lexic array
	int success = TRUE;

	//read through input line by line
	while (fgets(input, MY_CHAR_MAX, inf) != NULL){
		char str[LEXEME_MAX]; //holder for strings
		int strInd = 0;
		int doubleSym = FALSE; //for "!=" and "=="

		//for each char in input
		for (int i = 0; i < strlen(input); i++){
			//add char to string holder
			str[strInd] = input[i];
			str[strInd+1] = '\0';

			//check to see token of string
			int type = checkToken(str);

			if (type == WHILE_KEYWORD || type == RETURN_KEYWORD){
				//make new lexic and add data
				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;

				//append to lexic array
				aLex[lexInd] = lex;
				lexInd++;
				count++;

				if (type == -1){
					success = FALSE;
				}

				//mark str so str can be reset and reset str index
				str[0] = '$';
				reformatString(str);
				strInd = 0;
			} else if (type == VARTYPE){
				//so on for the similar stuff
				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;

				aLex[lexInd] = lex;
				lexInd++;
				count++;

				if (type == -1){
					success = FALSE;
				}

				str[0] = '$';
				reformatString(str);
				strInd = 0;
			//for spaces, carriage returns, or tabs
			} else if (str[strInd] == ' ' || str[strInd] == '\r' || str[strInd] == '\t'){
				//add whatever was before the space to lexic array
				if (strlen(str) > 1){
					str[strInd] = '$';
					reformatString(str);

					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = checkToken(str);

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					if (lex.token == -1){
						success = FALSE;
					}

					str[0] = '$';
					reformatString(str);
					strInd = 0;
				// else ignore space if only thing in str
				} else {
					strInd = 0;
				}
			//single-symbol
			} else if (str[strInd] == '(' || str[strInd] == ')' || str[strInd] == '{' || str[strInd] == '}'
						|| str[strInd] == ',' || str[strInd] == ';' || str[strInd] == '+'|| str[strInd] == '*'
						|| str[strInd] == '%' || str[strInd] == '!' || str[strInd] == '='){
				//check if a "!=" or "==" is coming up and prepare for it
				if (str[strInd] == '=' || str[strInd] == '!'){
					if (input[i+1] == '=' || (str[strInd] == '!' && input[i+1] != '=')){
						doubleSym = TRUE;
						strInd++;
						str[strInd+1] = '\0';
						continue;
					}
				}

				//if str is equal to the symbols, just add them to the lexic array
				if (strlen(str) == 1 || strcmp(str, "!=") == 0 || strcmp(str, "==") == 0){
					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = checkToken(str);

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					if (lex.token == -1){
						success = FALSE;
					}

					str[0] = '$';
					reformatString(str);
					strInd = 0;

					if (doubleSym){
						doubleSym = FALSE;
					}
				//else if other char are mixed in
				} else {
					char symbol[5]; //holds symbol

					//pick out symbols whether they're double or single
					if (doubleSym){
						strcpy(symbol, str + (strInd-1));
						doubleSym = FALSE;
						str[strInd-1] = '$';
					} else {
						symbol[0] = str[strInd];
						symbol[1] = '\0';
						str[strInd] = '$';
					}

					//lexic for symbol
					struct lexics lex2;
					strcpy(lex2.lexeme, symbol);
					lex2.token = checkToken(symbol);

					reformatString(str);

					//lexic for whatever came before symbol
					struct lexics lex1;
					strcpy(lex1.lexeme, str);
					lex1.token = checkToken(str);

					//add them both to lexic array in correct order
					aLex[lexInd] = lex1;
					lexInd++;
					count++;

					aLex[lexInd] = lex2;
					lexInd++;
					count++;

					if (lex1.token == -1 || lex2.token == -1){
                                       		success = FALSE;
                              		}

					str[0] = '$';
					reformatString(str);
					strInd = 0;
				}
			} else if (type == IDENTIFIER || type == NUMBER){
				//check to make sure left over char are added to lexic array
				if (i+1 == strlen(input) && strlen(str) != 0 && count == 0 && str[strInd] != '$'){
					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					if (type == -1){
						success = FALSE;
					}

					str[0] = '$';
					reformatString(str);
					strInd = 0;
				} else {
					//keep adding next char
					strInd++;
				}
			}

			str[strInd+1] = '\0';
		}
	}

	fclose(inf);

	//update with number of lexemes
	*numLex = count;

	return success;
}

//return corresponding token for a lexeme
int checkToken(char *str){
	if (strcmp(str, "(") == 0){
		return LEFT_PARENTHESIS;
	} else if (strcmp(str, ")") == 0){
		return RIGHT_PARENTHESIS;
	} else if (strcmp(str, "{") == 0){
		return LEFT_BRACKET;
	} else if (strcmp(str, "}") == 0){
		return RIGHT_BRACKET;
	} else if (strcmp(str, "while") == 0){
		return WHILE_KEYWORD;
	} else if (strcmp(str, "return") == 0){
		return RETURN_KEYWORD;
	} else if (strcmp(str, ",") == 0){
		return COMMA;
	} else if (strcmp(str, ";") == 0){
		return EOL;
	} else if (strcmp(str, "int") == 0 || strcmp(str, "void") == 0){
		return VARTYPE;
	} else if (strcmp(str, "+") == 0 || strcmp(str, "*") == 0 || strcmp(str, "!=") == 0
				|| strcmp(str, "==") == 0 || strcmp(str, "%") == 0){
		return BINOP;
	} else if (strcmp(str, "=") == 0){
		return EQUAL;
	} else if (validIdentifier(str)){
		return IDENTIFIER;
	} else if (validNumber(str)){
		return NUMBER;
	}

	return -1;
}

//reformat placeholder str for next lexeme
void reformatString(char *str){
	char reStr[LEXEME_MAX] = "$";\

	//use '$' as temp placeholder and "clear" str
	for(int i = 0; i < strlen(str); i++) {
		if (str[i] != '$'){
			reStr[i] = str[i];
		} else {
			break;
		}
	}

	strcpy(str, reStr);
}

