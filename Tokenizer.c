/*
 * Tokenizer.c
 */

#include "Tokenizer.h"
#include <string.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	char input[MY_CHAR_MAX];
	int count = 0;
	int lexInd = 0;
	int success = FALSE;

	while (fgets(input, MY_CHAR_MAX, inf) != NULL){
		char str[LEXEME_MAX];
		int strInd = 0;
		int doubleSym = FALSE;

		for (int i = 0; i < strlen(input); i++){
			str[strInd] = input[i];
			printf("-- %s", str);
			int type = checkToken(str);

			if (type == WHILE_KEYWORD || type == RETURN_KEYWORD){
				printf(" 1");

				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;

				aLex[lexInd] = lex;
				lexInd++;
				count++;

				str[0] = '$';
				strcpy(str, reformatString(str));
				printf(" %s\n", str);
				strInd = 0;
			} else if (type == VARTYPE){
				printf(" 2");

				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;
				printf(" %d", type);

				aLex[lexInd] = lex;
				lexInd++;
				count++;

				str[0] = '$';
				strcpy(str, reformatString(str));
				printf(" %s\n", str);
				strInd = 0;
			} else if (str[strInd] == ' ' || str[strInd] == '\r' || str[strInd] == '\t'){
				printf(" 3");
				if (strlen(str) > 1){
					str[strInd] = '$';
					strcpy(str, reformatString(str));
					printf(" %s\n", str);

					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
					printf(" %s\n", str);
					strInd = 0;
				} else {
					printf("\n");
					strInd = 0;
				}
			} else if (str[strInd] == '(' || str[strInd] == ')' || str[strInd] == '{' || str[strInd] == '}'
					|| str[strInd] == ',' || str[strInd] == ';' || str[strInd] == '+'|| str[strInd] == '*'
							|| str[strInd] == '%' || str[strInd] == '!' || str[strInd] == '='){
				printf(" 5");
				if (str[strInd] == '=' || str[strInd] == '!'){
					if (input[i+1] == '=' || (str[strInd] == '!' && input[i+1] != '=')){
						printf(" @%c@\n", input[i+1]);
						doubleSym = TRUE;
						strInd++;
						str[strInd+1] = '\0';
						continue;
					}
				}

				if (strlen(str) == 1 || strcmp(str, "!=") == 0 || strcmp(str, "==") == 0){
					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;
					printf(" %d", type);

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
					printf(" %s\n", str);
					strInd = 0;

					if (doubleSym){
						doubleSym = FALSE;
					}
				} else {
					char symbol[5];

					if (doubleSym){
						strcpy(symbol, str + (strInd-1));
						printf(" *%s*", symbol);
						doubleSym = FALSE;
						str[strInd-1] = '$';
					} else {
						symbol[0] = str[strInd];
						str[strInd] = '$';
					}

					struct lexics lex2;
					strcpy(lex2.lexeme, symbol);
					lex2.token = checkToken(symbol);
					printf(" #%s# %d", symbol, lex2.token);

					strcpy(str, reformatString(str));
					printf(" %s\n", str);

					struct lexics lex1;
					strcpy(lex1.lexeme, str);
					lex1.token = checkToken(str);
					printf(" %d", lex1.token);

					aLex[lexInd] = lex1;
					lexInd++;
					count++;

					aLex[lexInd] = lex2;
					lexInd++;
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
					printf(" %s\n", str);
					strInd = 0;
				}
			} else if (type == IDENTIFIER || type == NUMBER){
				printf(" 4\n");
				if (i+1 == strlen(input) && strlen(str) != 0 && count == 0 && str[strInd] != '$'){
					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;
					printf(" %d", type);

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
					printf(" %s\n", str);
					strInd = 0;
				} else {
					strInd++;
				}
			}

			str[strInd+1] = '\0';
		}
		success = TRUE;
	}

	fclose(inf);

	*numLex = count;

	return success;
}

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
	}
	return NUMBER;
}

char * reformatString(char *str){
	char reStr[LEXEME_MAX] = "$";\

	for(int i = 0; i < strlen(str); i++) {
		if (str[i] != '$'){
			reStr[i] = str[i];
		} else {
			break;
		}
	}
	printf(" !%s!", reStr);
	return reStr;
}
