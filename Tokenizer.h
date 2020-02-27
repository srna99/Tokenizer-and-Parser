/*
 * Tokenizer.h
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "Givens.h"
#include <stdio.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);
int checkToken(char *str);
char * reformatString(char *str);

#endif /* TOKENIZER_H_ */
