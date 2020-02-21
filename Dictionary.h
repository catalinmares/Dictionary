/*Mares Catalin-Constantin
		Grupa: 312CD      */
#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List element for Dictionary lists.
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	char *key;
	char *value;
	int frequency;
} ListNode;

// Dictionary structure that includes the lists of elements and their number.
typedef struct Dictionary {
	ListNode **lists;		// lists of elements.
	int N;					// number of lists.
} Dictionary;

//--------------------------- GIVEN FUNCTIONS ---------------------------------

// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N);

// Adds an element to the Dictionary structure.
void addElement(Dictionary* dictionary, char* key, char* value, int frequency);

// Removes an element from the Dictionary structure.
void removeElement(Dictionary* dictionary, char* key, char* value);

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE* f, Dictionary* dictionary);

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary* dictionary, char* key);

// Prints all the elements with the specified value.
void printValue(FILE* f, Dictionary* dictionary , char* value);

// Prints all the elements with the specified frequency.
void printFrequency(FILE* f, Dictionary* dictionary , int frequency);

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary* dictionary, char* value);

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary* dictionary);

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary* dictionary);

// Prints a double-linked non-circular list.
void printList(FILE* f, ListNode* list);

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary* dictionary);

// Frees all the memory allocated for a double-linked non-circular list.
void freeList(ListNode* list);

//-----------------------------------------------------------------------------

//--------------------------- AUXILIAR FUNCTIONS ------------------------------

// Checks if a linked list is empty.
int isEmpty(ListNode* list);

// Returns the length of a double-linked circular list.
int length(ListNode* list);

// Returns the total number of elements from the dictionary.
int getNrTotalElements(Dictionary* dictionary);

// Tests 2 strings alphabetically.
int testStrings(char* str1, char* str2);

// Checks if the list contains an element with given (key, value).
ListNode* containsKeyValue(ListNode* list, char* key, char* value);

// Inserts the newElement in the list maintining the list sorted.
ListNode* insertNewElement(ListNode* list, ListNode* newElement);

// Deletes the last element from a double-linked circular list.
ListNode* deleteLastElement(ListNode* list);

// Calculates the index of the list where the new element will be inserted.
int findList(char* key, int N);

// Searches the dictionary for the given key.
int containsKey(Dictionary* dictionary, char* key);

// Extracts the elements with the given value from a list into a new list.
ListNode* insertAtEndValues(ListNode* newlist, ListNode* list, char* value);

// Extracts the elements with maximum frequency from a list into a new list.
ListNode* insertAtEndMaxFrequencies(ListNode* newlist, ListNode* list);

//-----------------------------------------------------------------------------

//--------------------------- IMPLEMENTATION ----------------------------------

int isEmpty(ListNode* list) {

	// returns 1 for empty list or 0 else.
	return list == NULL;
}

int length(ListNode* list) {

	if (isEmpty(list))
	{	
		// length is 0 for empty list.
		return 0;
	}

	ListNode* temp = list;
	// the list is circular, we start from the second node.
	temp = temp->next;

	int length = 1; // is 1 because we started from the second node.

	// we parse the list and increment the length.
	while (temp != list)
	{
		length++;
		temp = temp->next;
	}

	return length;
}

int getNrTotalElements(Dictionary* dictionary) {

	if (dictionary == NULL)
	{
		// empty dictionary -> 0 elements.
		return 0;
	}

	int i;
	int nrTotalElements = 0;
	
	// we parse the lists by calling the length function for each list
	// and adding each length to the number of total elements
	for (i = 0; i < dictionary->N; i++)
	{
		nrTotalElements += length(dictionary->lists[i]);
	}

	return nrTotalElements;
}

int testStrings(char* str1, char* str2) {

	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int minLen;

	// we find the shortest length of string for parsing them.
	if (len1 < len2)
	{
		minLen = len1;
	}

	else
	{
		minLen = len2;
	}

	int i;

	// we parse the strings until the shorter one's last character.
	for (i = 0; i < minLen; i++)
	{
		if (str1[i] == str2[i])
		{
			// if the characters are equal we continue.
			continue;
		}

		if (str1[i] < str2[i])
		{
			// if the ascii code of str1 is smaller, str1 is bigger than str2.
			return 1;
		}

		// if the ascii code of str2 is small, str2 is bigger than str1.
		return -1;
	}

	// we exit the for loop only if the verified characters are equal
	// so it's enough to compare their lengths to decide which is bigger.

	if (len1 < len2)
	{
		return 1;
	}

	if (len1 > len2)
	{
		return -1;
	}

	// we return 0 if they are identical.
	return 0;
}

ListNode* containsKeyValue(ListNode* list, char* key, char* value) {

	if (isEmpty(list))
	{
		// empty list -> doesn't contain (key, value).
		return NULL;
	}

	ListNode* head = list;

	// we check if the head of the list is (key, value).
	if (head->key == key && head->value == value)
	{
		return head;
	}

	// we start parsing from the second node.
	head = head->next;

	while (head != list)
	{
		if (head->key == key && head->value == value)
		{
			// we return the node with found (key, value).
			return head;
		}

		head = head->next;
	}

	// parse ended, (key, value) is not in the list.
	return NULL;
}

ListNode* insertNewElement(ListNode* list, ListNode* newElement) {

	if (isEmpty(list))
	{
		// list is empty, newElement becomes the first and only element.
		newElement->next = newElement;
		newElement->prev = newElement;
		list = newElement;

		return list;
	}

	ListNode* temp;

	// we start parsing the list to find the place for the new element.
	for (temp = list; temp->next != list; temp = temp->next)
	{
		if (temp->frequency > newElement->frequency)
		{
			// temp has higher frequency, we must insert after so we continue.
			continue;
		}
		
		if (temp->frequency < newElement->frequency)
		{
			// temp has lower frequency, we must insert before head.
			newElement->next = temp;
			newElement->prev = temp->prev;
			temp->prev->next = newElement;
			temp->prev = newElement;

			if (temp == list)
			{
				// if temp was the first element, the new element becomes the
				// head of the returned list.
				list = newElement;
			}

			return list;
		}

		// if the frequency is equal, we verify the values
		if (testStrings(temp->value, newElement->value) == 1)
		{
			// if the value of temp is bigger, we continue.
			continue;
		}

		if (testStrings(temp->value, newElement->value) == -1)
		{
			// temp has smaller value (alphabetically)
			// we insert before temp.
			newElement->next = temp;
			newElement->prev = temp->prev;
			temp->prev->next = newElement;
			temp->prev = newElement;

			if (temp == list)
			{
				list = newElement;
			}

			return list;
		}

		// if the values are equal, we verify the keys
		if (testStrings(temp->key, newElement->key) == 1)
		{
			// if the key of temp is bigger, we continue.
			continue;
		}

		// temp has smaller key (alphabetically)
		// we insert before temp.
		newElement->next = temp;
		newElement->prev = temp->prev;
		temp->prev->next = newElement;
		temp->prev = newElement;

		if (temp == list)
		{
			list = newElement;
		}

		// temp and newElement can't have the same value and key
		// since this function is called only after checking
		// if the given element is already in the list and
		// deleting it before reinserting it in the list with the
		// increased frequency.

		return list;
	}

	// when we exit the for loop, temp is on the last element of the list.
	// we must check again the same conditions for the last element.

	if (temp->frequency > newElement->frequency)
	{
		// temp is the last element, so we insert after it for lower frequency.
		newElement->next = temp->next;
		newElement->prev = temp;

		temp->next = newElement;
		list->prev = newElement;

		return list;
	}
		
	if (temp->frequency < newElement->frequency)
	{
		newElement->next = temp;
		newElement->prev = temp->prev;
		temp->prev->next = newElement;
		temp->prev = newElement;

		if (temp == list)
		{
			list = newElement;
		}

		return list;
	}
	
	if (testStrings(temp->value, newElement->value) == 1)
	{
		// temp is the last element, so we insert after it for lower value.
		newElement->next = temp->next;
		newElement->prev = temp;

		temp->next = newElement;
		list->prev = newElement;

		return list;
	}

	if (testStrings(temp->value, newElement->value) == -1)
	{
		newElement->next = temp;
		newElement->prev = temp->prev;
		temp->prev->next = newElement;
		temp->prev = newElement;

		if (temp == list)
		{
			list = newElement;
		}

		return list;
	}

	if (testStrings(temp->key, newElement->key) == 1)
	{
		// temp is the last element, so we insert after it for lower key.
		newElement->next = temp->next;
		newElement->prev = temp;

		temp->next = newElement;
		list->prev = newElement;

		return list;
	}

	newElement->next = temp;
	newElement->prev = temp->prev;
	temp->prev->next = newElement;
	temp->prev = newElement;

	if (temp == list)
	{
		list = newElement;
	}

	return list;
}

ListNode* deleteLastElement(ListNode* list) {

	if (isEmpty(list))
	{
		// empty list -> nothing to delete;
		return NULL;
	}

	if (list->next == list)
	{
		// list has one element.
		free(list);
		return NULL;
	}

	// we delete the last node.
	ListNode* toDelete = list->prev;

	list->prev = toDelete->prev;
	toDelete->prev->next = list;
	
	free(toDelete);
	return list;
}

int findList(char* key, int N) {

	int s = 0;
	int i;

	// we parse the key characters and sum their ASCII codes.
	for (i = 0; i < strlen(key); i++)
	{
		s += key[i];
	}

	// we calculate the list index.
	int r = s % N;

	return r;
}

int containsKey(Dictionary* dictionary, char* key) {

	int i;

	// we parse all the lists into the dictionary.
	for (i = 0; i < dictionary->N; i++)
	{
		if (isEmpty(dictionary->lists[i]))
		{
			// empty list -> doesn't contain given key, we continue.
			continue;
		}

		ListNode* listOperated = dictionary->lists[i];

		// we parse the list and check every node's key
		// if we find the key we return the index of the list which contains it.
		while (listOperated != dictionary->lists[i]->prev)
		{
			if (listOperated->key == key)
			{
				return i;
			}

			listOperated = listOperated->next;
		}

		// we verify the last node.
		if (listOperated->key == key)
		{
			return i;
		}
	}

	// key wasn't found into the dictionary, we return error.
	return -1;
}

ListNode* insertAtEndValues(ListNode* newlist, ListNode* list, char* value) {

	ListNode *prev, *tmp2;
	ListNode* tmp = list;

	// we parse the list until we find the given value.
	while (tmp != list->prev && tmp->value != value)
	{
		tmp = tmp->next;
	}

	// we found the value
	if (tmp->value == value)
	{
		// the new list is empty, we must create the first node.
		if (isEmpty(newlist))
		{
			newlist = (ListNode*) calloc(1, sizeof(ListNode));
			newlist->key = tmp->key;
			newlist->value = tmp->value;
			newlist->frequency = tmp->frequency;

			newlist->next = NULL;
			newlist->prev = NULL;

			// prev is used for making possible the linking of the new list.
			// every time we create a new node we save it in prev
			// so when we allocate another one we have the previous address.
			prev = newlist;
		}

		// the new list has some elements.
		else
		{
			tmp2 = newlist;

			// we parse the list until we find NULL.
			while (tmp2 != NULL)
			{
				prev = tmp2; // we keep track of the previous element.
				tmp2 = tmp2->next;
			}

			// we allocate a new element and make the linking with the list.
			tmp2 = (ListNode*) calloc(1, sizeof(ListNode));
			tmp2->key = tmp->key;
			tmp2->value = tmp->value;
			tmp2->frequency = tmp->frequency;
			tmp2->prev = prev;
			tmp2->next = NULL;
			prev->next = tmp2;

			prev = tmp2; // we save the new node for mext allocations.
		}
	}

	// we didn't find the value in the list.
	else
	{
		return NULL;
	}

	tmp = tmp->next;

	// we parse the list from the next node of the one where we found value.
	while (tmp != list)
	{
		// if we found the value we allocate a new node the the new list.
		if (tmp->value == value)
		{
			tmp2 = (ListNode*) calloc(1, sizeof(ListNode));
			tmp2->key = tmp->key;
			tmp2->value = tmp->value;
			tmp2->frequency = tmp->frequency;

			tmp2->prev = prev;
			tmp2->next = NULL;
			prev->next = tmp2;

			prev = tmp2;

		}

		tmp = tmp->next;
	}

	// we return the new list.
	return newlist;
}

ListNode* insertAtEndMaxFrequencies(ListNode* newlist, ListNode* list) {

	ListNode *prev, *tmp2;

	// we save the maximum frequency to a separate variable.
	int maxFrequency = list->frequency;

	ListNode* tmp = list;

	// we parse the list while the frequency is maximum.
	while (tmp != list->prev && tmp->frequency == maxFrequency)
	{
		// here we have the same cases as in the previous functions.
		if (isEmpty(newlist))
		{
			newlist = (ListNode*) calloc(1, sizeof(ListNode));
			newlist->key = tmp->key;
			newlist->value = tmp->value;
			newlist->frequency = tmp->frequency;

			newlist->next = NULL;
			newlist->prev = NULL;

			prev = newlist;
		}

		else
		{
			tmp2 = newlist;

			while (tmp2 != NULL)
			{
				prev = tmp2;
				tmp2 = tmp2->next;
			}

			tmp2 = (ListNode*) calloc(1, sizeof(ListNode));
			tmp2->key = tmp->key;
			tmp2->value = tmp->value;
			tmp2->frequency = tmp->frequency;
			tmp2->prev = prev;
			tmp2->next = NULL;
			prev->next = tmp2;

			prev = tmp2;
		}

		tmp = tmp->next;
	}

	// we check if the last node has maximum frequency.
	if (tmp->frequency == maxFrequency)
	{
		tmp2 = (ListNode*) calloc(1, sizeof(ListNode));
		tmp2->key = tmp->key;
		tmp2->value = tmp->value;
		tmp2->frequency = tmp->frequency;
		tmp2->prev = prev;
		tmp2->next = NULL;
		prev->next = tmp2;

		prev = tmp2;	
	}

	// we return the new list.
	return newlist;
}

//-----------------------------------------------------------------------------

Dictionary* createDictionary(int N) {

	// we allocate memory for the dictionary.
	Dictionary* dictionary = (Dictionary*) calloc(1, sizeof(Dictionary));
	dictionary->N = N;

	// we allocate memory for N lists.
	dictionary->lists = (ListNode**) calloc(N, sizeof(ListNode*));

	return dictionary;
}

void addElement(Dictionary *dictionary, char *key, char *value, int frequency) {

	// we allocate memory for a new element.
	ListNode* newElement = (ListNode*) calloc(1, sizeof(ListNode));
	newElement->key = key;
	newElement->value = value;
	newElement->frequency = frequency;

	// we find the index of the list to insert into by calling findList.
	int r = findList(key, dictionary->N);

	int inserted = 0; // inserted flag

	ListNode* listOperated = dictionary->lists[r];

	int len = length(listOperated); // we calculate the length of the list.

	// we extract from the list the element with (key, value) to insert.
	ListNode* extracted = containsKeyValue(listOperated, key, value);

	// if we found one we remove it from the list and add it back
	// with the new summed frequency maintaining the list sorted.
	if (extracted != NULL)
	{
		removeElement(dictionary, key, value);
		listOperated = dictionary->lists[r];

		newElement->frequency += extracted->frequency;

		listOperated = insertNewElement(listOperated, newElement);

		inserted = 1; // set flag to 1.
	}

	// we test if the list already has N elements.
	if (len == dictionary->N && !inserted)
	{
		// we delete the last element from the list.
		listOperated = deleteLastElement(listOperated);
	}

	// separated case for empty list.
	if (isEmpty(listOperated))
	{
		newElement->prev = newElement;
		newElement->next = newElement;

		listOperated = newElement;

		inserted = 1; // set flag to 1.
	}

	// we test if the element wasn't inserted in previous cases.
	// if not, the element is new and the list is not empty.
	if (!inserted)
	{
		listOperated = insertNewElement(listOperated, newElement);
		inserted = 1; // set flag to 1.
	}

	dictionary->lists[r] = listOperated; // we link the list to the dictionary.

	// after insertion we calculate the total number of elements.
	int nrTotalElements = getNrTotalElements(dictionary);

	// if there are more than 2N elements in the dictionary
	// we delete every list's last element.
	if (nrTotalElements > 2 * dictionary->N)
	{
		int i;

		// we parse the lists and delete for each one its last element.
		for (i = 0; i < dictionary->N; i++)
		{
			dictionary->lists[i] = deleteLastElement(dictionary->lists[i]);
		}
	}
}

void removeElement(Dictionary *dictionary, char *key, char *value) {
	
	// we locate in which list is the element situated.
	int r = findList(key, dictionary->N);

	ListNode* listOperated = dictionary->lists[r];

	// we extract the element from the list.
	ListNode* extracted = containsKeyValue(listOperated, key, value);
	
	// if the list is empty or the given element isn't in the list we return.
	if (isEmpty(listOperated) || extracted == NULL)
	{
		return;
	}

	// case for a list with only one element which must be removed.
	if (extracted->next == extracted)
	{
		dictionary->lists[r] = NULL;
		free(extracted);
		extracted = NULL;

		return;
	}

	// case for a list with more elements with the first to be removed.
	if (extracted == listOperated)
	{
		extracted->next->prev = extracted->prev;
		extracted->prev->next = extracted->next;

		// we change the head of the list.
		dictionary->lists[r] = extracted->next;
		free(extracted);

		return;

	}

	// case when we delete from the middle or at the last.
	extracted->prev->next = extracted->next;
	extracted->next->prev = extracted->prev;
	free(extracted);
}

void printDictionary(FILE *f, Dictionary *dictionary) {

	// case for empty dictionary -> nothing to print
	if (dictionary == NULL)
	{
		fprintf(f, "\n");

		return;
	}

	int i;

	// we parse the dictionary and print every list.
	for (i = 0; i < dictionary->N; i++)
	{
		if (i != 0)
		{
			fprintf(f, "\n");
		}
		fprintf(f, "List %d: ", i);

		// if the list is empty we continue with the next list.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}

		ListNode* listOperated = dictionary->lists[i];

		// we print the first element.
		fprintf(f, "(%s, %s, %d) ", listOperated->key, listOperated->value,
		listOperated->frequency);

		listOperated = listOperated->next;

		// we start parsing from the second element and we print all the list.
		while (listOperated != dictionary->lists[i])
		{
			fprintf(f, "(%s, %s, %d) ", listOperated->key, listOperated->value,
			listOperated->frequency);

			listOperated = listOperated->next;
		}
	}

	fprintf(f, "\n");
}

ListNode* get(Dictionary *dictionary, char *key) {

	// we check if the key is in the dictionary
	int listNr = containsKey(dictionary, key);

	if (listNr == -1)
	{
		// function containsKey returned -1 -> the key isn't in the dictionary.
		return NULL;
	}

	ListNode* listOperated = dictionary->lists[listNr];
	ListNode *list, *prev, *temp;

	// we parse the list until we find the first element with the key searched.
	while (listOperated->key != key)
	{
		listOperated = listOperated->next;
	}

	// we allocate the first element of the new list.
	list = (ListNode*) calloc(1, sizeof(ListNode));
	list->key = listOperated->key;
	list->value = listOperated->value;
	list->frequency = listOperated->frequency;
	list->prev = NULL;
	list->next = NULL;

	// we go to the next element in the old list.
	listOperated = listOperated->next;
	// we save the address of the new node for further linking.
	prev = list;

	// we parse the old list to find all the elements with given key.
	while (listOperated != dictionary->lists[listNr])
	{
		// every time we find an element with the given key
		// we insert it in the new list.
		if (listOperated->key == key)
		{
			temp = (ListNode*) calloc(1, sizeof(ListNode));
			temp->key = listOperated->key;
			temp->value = listOperated->value;
			temp->frequency = listOperated->frequency;

			// we link the new node to the previous one in the list.
			temp->next = NULL;
			temp->prev = prev;
			prev->next = temp;

			prev = prev->next; // prev becomes the new node.
		}

		listOperated = listOperated->next;
	}

	ListNode* tmp = list;

	// now we must increment the frequency for each element extracted.
	// we parse the new list and we call the addElement function which
	// will operate on the case for elements that are already in the list.
	while (tmp != NULL)
	{
		addElement(dictionary, tmp->key, tmp->value, 1);
		tmp = tmp->next;
	}

	return list;
}

void printValue(FILE *f, Dictionary *dictionary , char *value) {

	// empty dictionary -> nothing to print.
	if (dictionary == NULL)
	{
		fprintf(f, "\n");
		return;
	}

	int i;

	// we start parsing all the lists searching for the given value.
	for (i = 0; i < dictionary->N; i++)
	{
		// empty list -> nothing to print -> we continue with the next list.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}

		ListNode* listOperated = dictionary->lists[i];

		// we check the first element for the given value.
		if (listOperated->value == value)
		{
			fprintf(f, "(%s, %s, %d) ", listOperated->key, listOperated->value,
			listOperated->frequency);
		}

		listOperated = listOperated->next;
		// we parse the list starting from the second node and we print all
		// the elements with the given value.
		while (listOperated != dictionary->lists[i])
		{
			if (listOperated->value == value)
			{
				fprintf(f, "(%s, %s, %d) ", listOperated->key, 
				listOperated->value,listOperated->frequency);
			}

			listOperated = listOperated->next;
		}
	}

	fprintf(f, "\n");
}

void printFrequency(FILE *f, Dictionary *dictionary , int frequency) {

	// empty dictionary -> nothing to print.
	if (dictionary == NULL)
	{
		fprintf(f, "\n");
		return;
	}

	int i;

	// we start parsing all the lists searching for the given frequency.
	for (i = 0; i < dictionary->N; i++)
	{
		// empty list -> nothing to print -> we continue with the next list.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}

		ListNode* listOperated = dictionary->lists[i];

		// we check the first element for the given frequency.
		if (listOperated->frequency == frequency)
		{
			fprintf(f, "(%s, %s, %d) ", listOperated->key, listOperated->value,
			listOperated->frequency);
		}

		listOperated = listOperated->next;

		// we parse the list starting from the second node and we print all
		// the elements with the given frequency. 
		while (listOperated != dictionary->lists[i])
		{
			if (listOperated->frequency == frequency)
			{
				fprintf(f, "(%s, %s, %d) ", listOperated->key,
				listOperated->value,listOperated->frequency);
			}

			listOperated = listOperated->next;
		}
	}

	fprintf(f, "\n");
}

ListNode* unionValues(Dictionary *dictionary, char *value) {

	int i;

	// we initialize the new list to NULL.
	ListNode* newlist = NULL;
	
	// we start parsing the dictionary to find all elements with given value.
	for (i = 0; i < dictionary->N; i++)
	{
		// empty list -> nothing to extract -> we continue with the next list.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}

		// we parse the list and insert into the new list the elements
		// with given value that we find in each list.
		newlist = insertAtEndValues(newlist, dictionary->lists[i], value);
	}

	return newlist;
}

ListNode* unionMaxFrequencies(Dictionary *dictionary) {

	int i;

	// same algorithm as the previous function.
	ListNode* newlist = NULL;
	
	for (i = 0; i < dictionary->N; i++)
	{
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}

		newlist = insertAtEndMaxFrequencies(newlist, dictionary->lists[i]);
	}

	return newlist;
}

Dictionary* reverseLists(Dictionary *dictionary) {

	// we create the new dictionary.
	Dictionary* reversedDictionary = createDictionary(dictionary->N);

	int i;

	// we parse the old dictionary and reverse the lists.
	for (i = 0; i < dictionary->N; i++)
	{
		// empty list -> nothing to insert into the new dictionary -> continue.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}
		
		// we insert the last element of the old list on the first
		// position of the new list.
		ListNode* listTail = dictionary->lists[i]->prev;

		ListNode *listRev, *prev, *temp, *first;

		listRev = (ListNode*) calloc(1, sizeof(ListNode));

		listRev->key = listTail->key;
		listRev->value = listTail->value;
		listRev->frequency = listTail->frequency;
		listRev->next = listRev->prev = listRev;

		// we save the address of the previous node and of the first.
		prev = listRev;
		first = listRev;

		listTail = listTail->prev;

		// we parse the old in reverse while inserting its elements
		// into the new list.
		while (listTail != dictionary->lists[i]->prev)
		{
			temp = (ListNode*) calloc(1, sizeof(ListNode));
			temp->key = listTail->key;
			temp->value = listTail->value;
			temp->frequency = listTail->frequency;

			temp->prev = prev;
			temp->next = first;

			// we link the first node to the new last.
			first->prev = temp;
			// we link the previous node to the new node.
			prev->next = temp;
			prev = prev->next;

			listTail = listTail->prev;
		}

		reversedDictionary->lists[i] = first;
	}

	return reversedDictionary;
}

void printList(FILE* f, ListNode *list) {

	// empty list -> nothing to print.
	if (isEmpty(list))
	{
		fprintf(f, "\n");
		return;
	}

	// we parse the list and we print its elements.
	while (list != NULL)
	{
		fprintf(f, "(%s, %s, %d) ", list->key, list->value, list->frequency);
		list = list->next;
	}

	fprintf(f, "\n");
}

void freeDictionary(Dictionary *dictionary) {

	// empty dictionary -> nothing to free.
	if (dictionary == NULL)
	{
		return;
	}

	int i;

	// we parse the dictionary and we free all its lists.
	for (i = 0; i < dictionary->N; i++)
	{
		// empty list -> nothing to free -> we continue with the next list.
		if (isEmpty(dictionary->lists[i]))
		{
			continue;
		}
		// we break the links between the first and the last element of the list
		// and we call the function freeList which frees a non-circular list.
		ListNode* listOperated = dictionary->lists[i];
		listOperated->prev->next = NULL;
		listOperated->prev = NULL;
		freeList(listOperated);
	}

	// we free the lists and the dictionary.
	free(dictionary->lists);
	free(dictionary);
}

void freeList(ListNode *list) {
	
	// empty list -> nothing to free.
	if (isEmpty(list))
	{
		return;
	}

	// we parse the list and we free each element.
	while (list != NULL)
	{
		ListNode* toFree = list;
		list = list->next;
		free(toFree);
	}

	list = NULL;
}

#endif
