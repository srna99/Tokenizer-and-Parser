/*
 * Parser.c
 */

#include "Parser.h"

int token = 0; //current token
int valid = TRUE;
int ind = 0;
struct lexics *lexicsArr;

_Bool parser(struct lexics *someLexics, int numberOfLexics){
	lexicsArr = someLexics;
	getNextToken();
	//begin parsing using EBNF grammar provided and most of funcs are self-explanatory
	function();
	return valid;
}

void function(){
	printf("1\n");
	header();
	body();
}

void header(){
	printf("2\n");
	match(VARTYPE);
	match(IDENTIFIER);
	match(LEFT_PARENTHESIS);

	if (token == VARTYPE){
		argDecl();
	}

	match(RIGHT_PARENTHESIS);
}

void argDecl(){
	printf("3\n");
	match(VARTYPE);
	match(IDENTIFIER);

	while (token == COMMA){
		match(COMMA);
		match(VARTYPE);
		match(IDENTIFIER);
	}
}

void body(){
	printf("4\n");
	match(LEFT_BRACKET);

	if (token != RIGHT_BRACKET){
		statementList();
	}

	match(RIGHT_BRACKET);
}

void statementList(){
	printf("5\n");
	statement();

	while (token == WHILE_KEYWORD || token == RETURN_KEYWORD || token == IDENTIFIER || token == LEFT_BRACKET){
		statement();
	}
}

void statement(){
	printf("6\n");
	if (token == WHILE_KEYWORD){
		whileLoop();
	} else if (token == RETURN_KEYWORD){
		returnStmt();
	} else if (token == IDENTIFIER){
		assignment();
	} else if (token == LEFT_BRACKET){
		body();
	}
}

void whileLoop(){
	printf("7\n");
	match(WHILE_KEYWORD);
	match(LEFT_PARENTHESIS);
	expression();
	match(RIGHT_PARENTHESIS);
	statement();
}

void returnStmt(){
	printf("8\n");
	match(RETURN_KEYWORD);
	expression();
	match(EOL);
}

void assignment(){
	printf("9\n");
	match(IDENTIFIER);
	match(EQUAL);
	expression();
	match(EOL);
}

void expression(){
	printf("10\n");
	if (token != LEFT_PARENTHESIS){
		term();

		while (token == BINOP){
			match(BINOP);
			term();
		}
	} else {
		match(LEFT_PARENTHESIS);
		expression();
		match(RIGHT_PARENTHESIS);
	}
}

void term(){
	printf("11\n");
	if (token == IDENTIFIER){
		match(IDENTIFIER);
	} else {
		match(NUMBER);
	}
}

//see if current token matches the expected token
void match(int inputTok){
	//if they match, update to next token
	if (token == inputTok){
		getNextToken();
	} else {
		//if not matched, EBNF violated
		printf("%d, but expected %d for %s\n", token, inputTok, lexicsArr[ind].lexeme);
		valid = FALSE;
	}
}

//get next token
void getNextToken(){
	token = lexicsArr[ind].token;
	ind++;
}

