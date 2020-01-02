/*

Copyright (c) 2019-2020, Adrien BLASSIAU and Corentin JUVIGNY

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

/** @file stack.h
 *
 * @brief This file is a stack implementation
 */


#ifndef __STACK__H__
#define __STACK__H__

/* Type booléen */
typedef enum
{
	false, //0
	true //1
}Bool;

typedef struct StackElement
{
	int value;
	struct StackElement *next;
}StackElement, *Pstack;


/**
* Retourne une Pile vide
* @return Une Pile vide
*/
Pstack new_stack(void);

/**
* Vide la Pile de ses éléments
* @param st La Pile à nettoyer
* @return Une Pile vide
*/
Pstack free_stack(Pstack st);

/**
* Vérifie si une Pile est vide
* @param st La pile à tester
* @return true si la Pile est vide, faux sinon
*/
Bool is_empty_stack(Pstack st);

/**
* Affiche une Pile
* @param st La Pile
*/
void print_stack(Pstack st);

/**
* Empile un entier dans la Pile
* @param st La Pile
* @param x L'entier à ajouter
* @return La nouvelle Pile
*/
Pstack push_stack(Pstack st, int x);

/**
* Dépile un entier de la Pile
* @param st La Pile
* @param La pile sans le premier élément
*/
Pstack pop_stack(Pstack st);

/**
* Retourne l'entier au sommet de la Pile
* @param st La Pile
* @return Le nombre entier au sommet de la Pile
*/
int top_stack(Pstack st);

/**
* Retourne la hauteur (longueur) de la Pile
* @param st La Pile
* @return La taille de la Pile
*/
int stack_length(Pstack st);

#endif