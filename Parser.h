/*
 * Parser.h
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Givens.h"
#include <stdio.h>

_Bool parser(struct lexics *someLexics, int numberOfLexics);
void function();
void header();
void argDecl();
void body();
void statementList();
void statement();
void whileLoop();
void returnStmt();
void assignment();
void expression();
void term();
void match(int inputTok);
void getNextToken();

#endif /* PARSER_H_ */
