/*
 * Tokenizer.c
 */

#include "Tokenizer.h"
#include <string.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	char input[MY_CHAR_MAX];
	int count = 0;

	while (fgets(input, MY_CHAR_MAX, inf) != NULL){
		char str[LEXEME_MAX];
		int strInd = 0;
		int lexInd = 0;

		for (int i = 0; i < strlen(input); i++){
			str[strInd] = input[i];
			printf("%s", str);
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
				strInd = 0;
			} else if (str[strInd] == ' '){
				printf(" 3");
				if (strlen(str) > 1){
					str[strInd] = '$';
					strcpy(str, reformatString(str));

					struct lexics lex;
					strcpy(lex.lexeme, str);
					lex.token = type;

					aLex[lexInd] = lex;
					lexInd++;
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
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
					count++;

					str[0] = '$';
					strcpy(str, reformatString(str));
					strInd = 0;
				} else {
					struct lexics lex2;
					strcpy(lex2.lexeme, &str[strInd]);
					lex2.token = checkToken(&str[strInd]);
					printf(" #%s, %s# %d", lex2.lexeme, &str[strInd], lex2.token);

					str[strInd] = '$';
					strcpy(str, reformatString(str));

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
					strInd = 0;
				}
			} else if (type == IDENTIFIER || type == NUMBER){
				printf(" 4\n");
				strInd++;
			}
		}
	}

	fclose(inf);

	*numLex = count;

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

char * reformatString(char *str){
	char reStr[LEXEME_MAX] = "$";
//	printf(" %lu %s", strlen(str), str);
	for(int i = 0; i < strlen(str); i++) {
//		printf(" hi");
		if (str[i] != '$'){
	     	 reStr[i] = str[i];
		} else {
			break;
		}
	}
	printf(" !%s!\n", reStr);
	return reStr;
}











