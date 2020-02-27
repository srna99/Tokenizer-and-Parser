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
	header();
	body();
}

void header(){
	match(VARTYPE);
	match(IDENTIFIER);
	match(LEFT_PARENTHESIS);

	if (token == VARTYPE){
		argDecl();
	}

	match(RIGHT_PARENTHESIS);
}

void argDecl(){
	match(VARTYPE);
	match(IDENTIFIER);

	while (token == COMMA){
		match(VARTYPE);
		match(IDENTIFIER);
	}
}

void body(){
	match(LEFT_BRACKET);

	if (token != RIGHT_BRACKET){
		statementList();
	}

	match(RIGHT_BRACKET);
}

void statementList(){
	statement();

	while (token == WHILE_KEYWORD || token == RETURN_KEYWORD || token == IDENTIFIER || token == LEFT_BRACKET){
		statement();
	}
}

void statement(){
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
	match(WHILE_KEYWORD);
	match(LEFT_PARENTHESIS);
	expression();
	match(RIGHT_PARENTHESIS);
	statement();
}

void returnStmt(){
	match(RETURN_KEYWORD);
	expression();
	match(EOL);
}

void assignment(){
	match(IDENTIFIER);
	match(EQUAL);
	expression();
	match(EOL);
}

void expression(){
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
		valid = FALSE;
	}
}

//get next token
void getNextToken(){
	token = lexicsArr[ind].token;
	ind++;
}
