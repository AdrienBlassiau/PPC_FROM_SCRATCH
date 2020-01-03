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

/** @file duo.h
 *
 * @brief This file manages the representation of a (var,val) association.
 */

#ifndef DUO__H
#define DUO__H

#include "include.h"
#include "stack.h"


/**
 * \struct duo
 * \brief duo structure
 *
 * \a An duo structure is a representation of a (var,val) association.
 *
 */
typedef struct duo {
	int var;
	int val;
} duo, *Pduo;

typedef struct duostack
{
	Pduo duo_element;
	struct duostack *next;
}duostack, *Pduostack;


/**
 * This function creates a new duo.
 * @param  var The variable of the duo.
 * @param  val The value of the duo.
 * @return     A new duo.
 */
Pduo new_duo(int var, int val);

/**
 * This function free the allocated space in the heap for the duo.
 * @param pduo The duo we want to free.
 */
void free_duo(void *pduo);

/**
 * This function print a duo.
 * @param pduo The duo we want to print.
 */
void print_duo(void *pduo);

/**
* Retourne une Pile vide
* @return Une Pile vide
*/
Pduostack new_duostack(void);

/**
* Vide la Pile de ses éléments
* @param st La Pile à nettoyer
*/
void free_duostack(void* st);

/**
* Vérifie si une Pile est vide
* @param st La pile à tester
* @return true si la Pile est vide, faux sinon
*/
Bool is_empty_duostack(Pduostack st);

/**
* Affiche une Pile
* @param st La Pile
*/
void print_duostack(void* pst);

/**
* Empile un duo dans la Pile
* @param st La Pile
* @param duo Le duo à ajouter
* @return La nouvelle Pile
*/
Pduostack push_duostack(Pduostack st, Pduo duo);

/**
* Dépile un duo de la Pile
* @param st La Pile
* @param La pile sans le premier élément
*/
Pduostack pop_duostack(Pduostack st);

/**
* Retourne le duo au sommet de la Pile
* @param st La Pile
* @return Le duo au sommet de la Pile
*/
Pduo top_duostack(Pduostack st);

/**
* Retourne la hauteur (longueur) de la Pile
* @param st La Pile
* @return La taille de la Pile
*/
int duostack_length(Pduostack st);


#endif