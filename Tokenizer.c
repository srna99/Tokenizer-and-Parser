/*
 * Tokenizer.c
 */

#include "Tokenizer.h"
#include <string.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	char input[MY_CHAR_MAX];

	while (fgets(input, MY_CHAR_MAX, inf) != NULL){
		char str[LEXEME_MAX];
		int strInd = 0;
		int lexInd = 0;

		for (int i = 0; i < strlen(input); i++){
			str[strInd] = input[i];
			printf("%d, %lu ", i, strlen(input));
			printf("%s", str);
			int type = checkToken(str);

			if (type == WHILE_KEYWORD || type == RETURN_KEYWORD){
				printf(" 1\n");

				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;

				aLex[lexInd] = lex;
				lexInd++;

				str[0] = NULL;
				strInd = 0;
			} else if (type == VARTYPE){
				printf(" 2\n");

				struct lexics lex;
				strcpy(lex.lexeme, str);
				lex.token = type;

				aLex[lexInd] = lex;
				lexInd++;

				str[0] = NULL;
				strInd = 0;
			} else if (str[strInd] == ' '){
				printf(" 3");
				if (strlen(str) > 1){
					str[strInd] = NULL;

					struct lexics lex;
					strcpy(lex.lexeme, str);
					printf(" %s\n", str);
					lex.token = type;

					aLex[lexInd] = lex;
					lexInd++;

					str[0] = NULL;
					strInd = 0;
				} else {
					str[0] = 0;
					strInd = 0;
				}
			} else if (str[strInd] == '(' || str[strInd] == ')' || str[strInd] == '{' || str[strInd] == '}'
						|| str[strInd] == '=' || str[strInd] == ',' || str[strInd] == ';' || str[strInd] == '+'
						|| str[strInd] == '*' || strcmp(str, "!=") == 0 || strcmp(str, "==") == 0
						|| str[strInd] == '%'){
				printf(" 5");
				if (strlen(str) == 1){
					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;

					aLex[lexInd] = lex;
					lexInd++;

					str[0] = NULL;
					strInd = 0;
				} else {
					char symbol = str[strInd];
					str[strInd] = NULL;

					struct lexics lex1;
					strcpy(lex1.lexeme, str);
					lex1.token = checkToken(str);
					printf(" %d", lex1.token);

					aLex[lexInd] = lex1;
					lexInd++;

					struct lexics lex2;
					strcpy(lex2.lexeme, &symbol);
					lex2.token = checkToken(&symbol);
					printf(" %d\n", lex2.token);

					aLex[lexInd] = lex2;
					lexInd++;

					str[0] = NULL;
					strInd = 0;
				}
			} else if (type == IDENTIFIER || type == NUMBER){
				printf(" 4\n");
				strInd++;
			}
		}
	}

	fclose(inf);

	if (TRUE){
		return TRUE;
	}

	return FALSE;
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
	} else if (strcmp(str, "=") == 0){
		return EQUAL;
	} else if (strcmp(str, ",") == 0){
		return COMMA;
	} else if (strcmp(str, ";") == 0){
		return EOL;
	} else if (strcmp(str, "int") == 0 || strcmp(str, "void") == 0){
		return VARTYPE;
	} else if (strcmp(str, "+") == 0 || strcmp(str, "*") == 0 || strcmp(str, "!=") == 0
				|| strcmp(str, "==") == 0 || strcmp(str, "%") == 0){
		return BINOP;
	} else if (validIdentifier(str)){
		return IDENTIFIER;
	}
	return NUMBER;
}











