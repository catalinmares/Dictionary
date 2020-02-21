# Dictionary

The program I wrote is composed, beside the functions given in the header file,
of other auxiliar functions that I wrote to help me implement the problem given.
In the following file I will explain the implementantion of every function and
the way I thought while writing this program. I will explain the implementantion
of the functions respecting the order they are declared in the header file.

**createDictionary**

* This function allocates memory for an element of type Dictionary.
* After allocating the dictionary, I filled the camp N with the given parameter.
* Also, I allocate memory for N lists, the lists that will be used by the
   dictionary.
* The function returns the dictionary allocated.

**addElement**

* This function must insert into the dictionary an new element given a key, a
   value and a frequency.
* In my implementantion, this function makes use of other auxiliar functions
   whoose role I will further explain.
* I started the function by allocating a node for the new element and by filling
   its fields with the data given by the paramateres of the function.
* After allocation, I find the index of the list where the new element must be
   inserted by calling the function findList (explained below).
* I initialize an inserted flag which will help me skip through some conditions
   after I finish adding the new element so I can verify after the insertion if
   the number of elements into the dictionary exceeded the limit of 2N.
* I calculate the length of the list where I must insert the element by calling
   the function length (explained below).
* The next step in my implementantion is checking if the new element to insert
   already exists in the dictionary. For this I call another auxiliar function,
   containsKeyValue (explained below) wich extracts the element from the list
   with a given key and value.
* Then I check if the extracted element is not NULL (the element with key and
   value already exists in the list) and I remove it by calling the function
   removeElement (explained below), I add its frequency to the frequency of the
   new element and I insert the element with the updated frequency back into the
   dictionary by calling the function insertNewElement (explained below) which
   will also keep the lists sorted by the given criteria and I set the inserted
   flag to the value 1.
* I check if the length of the list is already N and if it is I call the
   function deleteLastElement (explained below) which deletes its last element.
   I placed this test after the case when the element already exists in the list
   since in that case the list can have N elements, because no new element will
   be added, but just updated by its frequency.
* I check if the list is empty by calling the function isEmpty (explained below)
   and if it is I make the new element the head of the list and I set the inserted
   flag to the value 1.
* I check the flag. If inserted is 0, I call the function insertNewElement which
   will insert the new element into the list.
* I calculate the total number of elements in the dictionary by calling the
   function getNrTotalElements (explained below).
* I check if the total number of elements exceeds 2N. If so, I delete the last
   element of each list by calling the function deleteLastElement in a for loop.

**removeElement**

* This function must remove the element with the given key and value from the
   dictionary.
* In my implementation, I thought that the element with the given key and value
   is situated into a list which I can easily find by parsing the key string, so
   by calling my auxiliar function findList.
* Now that I found the list where the element should be, I must check if it
   really exists in the list. I check this by calling the function
   containsKeyValue. The same as in the function addElement, if my auxiliar
   function returns NULL, it means that the element given for deletion doesn't
   exist in the dictionary so I will simply interrupt the execution of the
   function by returning. The same thing will happen in the case of an empty
   list. The list is empty so it can't contain the given element.
* If the list contains the element there are three different cases.
* *FIRST CASE* - The list contains only the element to be removed. In this case
   I will simply break the link of the dictionary with the list and free the
   single element.
* *SECOND CASE* - The list contains more elements and the first must be removed.
   In this case I must set the head of the list to the second node and then free
   the old head.
* *THIRD CASE* - The list contains more elements and the element to be deleted
   is the last or a middle one. This set of instructions works for both cases
   since I am working with a circular list. In this case I must simply
   link the previous node to the next and viceversa and then free my node.

**printDictionary**

* This functions prints the dictionary by printing the elements of all its
   lists.
* In my implementation, first I check if the dictionary is empty. In this
   case I have nothing to print and I simply return.
* If the dictionary is not empty, I start parsing its lists and printing their
   elements.
* For each list I check if it's empty by calling the function isEmpty. If it is
   I continue parsing the next list.
* If the list is not empty I print its first element and then I parse it
   starting from the second element and print the rest of the elements.
   I couldn't print all the elements in the loop since the list is circular and
   I wouldn't have a condition to stop.

**get**

* This function must return a non-circular double-linked list of all the 
   elements from the dictionary containing the given key.
* In my implementation I though that a list of a dictionary can contain more
   different keys, but the same key cannot be contained in more than one list.
   So I implemented an auxiliar function called containsKey (explained below)
   which returns the index of the list containing the given key or -1 if the 
   key doesn't exist into the dictionary.
* If my function returned -1, the key doesn't exist in the dictionary so I
   return NULL.
* After identifying the index of the list containing the given key I start
   parsing it until I find the first element with the given key.
* When I find the first element with the given key I allocate a node for the
   new list and I fill its fields with the data from the found element.
* I save the address of the new node into a variable so I can link the next
   node to it and not losing its address.
* I skip to the next element of the list and I start parsing it until its end.
* Every time I found a new element with the given key, I allocate a new node
   for the new list and I fill its fields with the data of the found element.
* After extracting all the elements with the given key from the dictionary, 
   we must increment all those elements' frequency with the value 1.
* In my implementation, I started parsing the new list and calling for each
   element the function addElement with the frequency 1. The function will
   adopt the case when the element already exists into the dictionary and
   simply updating its frequency by deleting it from the list and reinserting
   it at the correct position, keeping the list sorted.
* The function returns the list containing all the elements with the given key.

**printValue**

* This functions prints all the elements from the dictionary with the given
   value.
* In my implementation, I check if the dictionary is empty. If it is, I have
   no elements to print and I simply return.
* If the dictionary contains some elements, I start parsing it and checking
   every list's elements for the given value.
* If the list is empty, I have no elements to print and I continue with the
   next list.
* If the list is not empty, I parse the list by checking for the given value
   and printing the elements that contain that value.

**printFrequency**

* This functions prints all the elements from the dictionary with the given
   frequency.
* In my implementation, I check if the dictionary is empty. If it is, I have
   no elements to print and I simply return.
* If the dictionary contains some elements, I start parsing it and checking
   every list's elements for the given frequency.
* If the list is empty, I have no elements to print and I continue with the
   next list.
* If the list is not empty, I parse the list by checking for the given
   frequency and printing the elements that contain that frequency.

**unionValues**

* This function creates a non-circular double-linked list containing all the
   elements from the dictionary with the given value.
* In my implementation, I initialize the new list to NULL and I parse the
   dictionary for the given value.
* If the list is empty, I have no elements to extract, so I continue with the
   next list.
* I update for each iteration the new list by calling the function 
   insertAtEndValues (explained below) which parses the list from the
   dictionary and inserts in the new list all the elements with the given value.
* The function returns a list of all the elements from the dictionary with the
   given value.

**unionMaxFrequencies**

* This function creates a non-circular double-linked list containing all the
   elements from the dictionary with the maximum frequency of each list.
* In my implementation, I initialize the new list to NULL and I parse the
   dictionary for the maximum frequencies.
* If the list is empty, I have no elements to extract, so I continue with the
   next list.
* I update for each iteration the new list by calling the function 
   insertAtEndMaxFrequencies (explained below) which parses the list from the
   dictionary and inserts in the new list all the elements with the maximum
   frequency for each list of the dictionary.
* The function returns a list of all the elements from the dictionary with the
   maximum frequencies.

**reverseLists**

* This functions creates a new dictionary which contains the same elements
   from the given dictionary, but with the elements of the lists in reversed
   order.
* In my implementation, first I create a new dictionary by calling the function
   createDictionary and then I start parsing the old dictionary list by list to
   reverse their elements into the lists of the new dictionary.
* If the list is empty, I have no elements to reverse, so I continue with the
   next list.
* If the list is not empty, I start from the last element and I allocate the
   first element of the same list of the new dictionary. I fill its fields
   with the data of the last element of the old list. I save the address of the
   node as it will be the first, but also the previous for the next element
   which will be inserted.
* I start parsing the old list from tail to head and for each element I
   allocate memory for a new node for the new list and I fill its fields with
   the data of the element of the old list.
* Then for each list, I link the new dictionary with the head of the new lists.
* The function returns a new dictionary with the elements of its lists reversed.

**printList**

* This function prints the elements of non-circular double-linked list.
* In my implementantion, first of all I check if the list is empty, in which
   case I return because I have no elements to print.
* If the list has some elements, I parse it until its end while printing each
   element.

**freeDictionary**

* This function frees the dictionary by deallocating all the memory it used.
* First of all, if the dictionary is empty, I have no memory to free and I
   simply return.
* If the dictionary has some elements, I start parsing it list by list, freeing
   the lists one by one.
* If one list is empty, I have no memory to free for it, so I will continue
   with the next list.
* For each list, I will break the links between the first and the last element,
   transforming it into a non-circular list which I will free using the function
   freeList (explained below).
* After freeing all the elements from all the lists I will finally free the
   lists and the dictionary itself.

**freeList**

* This function frees a non-circular double-linked list by deallocating all
   the memory it used.
* First of all, if the list is empty, I have no memory to free and I simply
   return.
* If the list has at least one element, we parse it and we free it node by
   node.

**isEmpty**

* This function checks if a list is empty.
* The function returns 1 if the list is empty and 0 if it isn't.

**length**

* This function calculates the length of a circular list.
* If the list is empty, the function will return 0.
* I start parsing the list from the second node and counting the nodes of the
   list by parsing it.
* The function returns the length of the list.

**getNrTotalElements**

* This function calculates the total number of elements from the dictionary.
* If the dictionary is empty, the function will return 0.
* If the dictionary is not empty, we add to the total number of elements the
   length of each list by calling the function length in a for loop for each
   list from the dictionary.
* The function returns the total number of elements of a dictionary.

**testStrings**

* This function determines which one of the two given strings is bigger
   alphabetically.
* First, I save the lengths of the two strings using the function strlen.
* Then I determine the minimum length and I parse the two strings until the
   end of the shortest one by comparing them character by character.
* If the two characters are equal, I continue with the next character of the
   strings.
* If the ASCII code of the letter of the first string is smaller than the
   ASCII code of the letter of the second string it means that the first string
   is bigger alphabetically than the second and viceversa.
* If the for loop is exited it means that all the compared characters were
   equal, so it's enough to compare the strings' lengths. This means that the
   shorter string is also the bigger one alphabetically.
* The function will be used in the function insertNewElement to compare the
   values and the keys for keeping the list sorted by the given criteria at
   each insertion.
* The function returns 1 if the first string is bigger alphabetically, -1 for
   the second string and 0 if the strings are equal.

**containsKeyValue**

* This function checks if a list contains an element with the given key and
   value.
* If the list is empty, it cannot contain the searched element, so it returns
   NULL.
* I parse the list and check each element for the given key and value.
* If I found the element, I return it, else I return NULL.
* The function will be used in addElement to verify if the element to be added
   already exists in the list.
* The function returns the element from the list with given key and value or
   NULL if there is no such element in the list.

**insertNewElement**

* This function inserts a new element in a list by keeping it sorted by the
   three criteria given.
* If the list is empty the new element becomes the head and only element of
   the list.
* If the list has at least one element, we parse it by verifying the three
   criteria.
* If temp has a higher frequency than the element to be inserted, we must
   insert the element at its right so temp becomes the next element of the list.
* If temp has a lower frequency than the element to be inserted, we insert the
   new element at its left. If temp was the head of the list, the new element
   becomes the head of the list.
* If temp has the same frequency as the new element, we must verify the values.
* If temp has a bigger value, then we must insert the new element at its right
   so temp becomes the next element of the list.
* If temp has a smaller value, then we insert the new element at its left. If
   temp was the head of the list, the new element becomes the head of the list.
* If temp has the same value as the new element, we must verify the keys.
* If temp has a bigger key, then we must insert the new element at its right
   so temp becomes the next element of the list.
* If temp has a smaller key, then we insert the new element at its left. If
   temp was the head of the list, the new element becomes the head of the list.
* Temp and the new element cannot have all three elements equal, because this
   function is called for that case only after deleting the element for which
   all conditions are apllied.
* When the program exits the for loop, temp is on the last element of the list
   for which we must verify the same conditions declared above.
* The function returns the list after the insertion.

**deleteLastElement**

* This function deletes the last of a list.
* If the list is empty, I have no element to delete, so I simply return NULL.
* If the list has one element, I free the element and I return NULL.
* If the list has more than one element, I link the first element of the list
   to the previous element of the one to be deleted and then I delete it.
* The function returns the list without the last element.

**findList**

* This function calculates the index of the list for a given key.
* I parse the string of the key and I sum the ASCII codes. The list index will
   be the sum % N.
* The function returns the index of the list where the given key must be
   situated.

**containsKey**

* This function checks if a dictionary contains the given key.
* I parse the dictionary and I check every list's elements for the given key.
* If an element with the given key is found, the function returns the index of
   the list which contains the given key.
* If no such element is found, the function returns -1.

**insertAtEndValues**

* This function inserts the elements with a given value from a list into a new
   list.
* I parse the list until I found the given value.
* If I found the value in the list, I check if the new list is empty.
* If the list is empty, I allocate the first element of the list and I fill
   its fields with the data from the found element from the old list, then I 
   save its address for further insertions.
* If the list is not empty, I parse the list until its end and I allocate a
   new node and I fill its fields with the data from the found element 
   from the old list, then I save its address for further insertions.
* If the value wasn't found in the list, the function returns NULL.
* I continue parsing the list until I find all the elements with the given
   value and for each one I allocate a new node for the new list and I
   insert it into the list, keeping the links with the previous elements.
* The function returns the new list updated with all the elements from the
   old list having the given value.

**insertAtEndMaxFrequencies**

* This function inserts the elements with the maximum frequency from a list
   into a new list.
* I save the maximum frequency to a separated variable.
* I parse the list while I found the maximum frequency.
* For each element found, I check if the new list is empty.
* If the list is empty, I allocate the first element of the list and I fill
   its fields with the data from the found element from the old list, then I 
   save its address for further insertions.
* If the list is not empty, I parse the list until its end and I allocate a
   new node and I fill its fields with the data from the found element 
   from the old list, then I save its address for further insertions.
* I check last element's frequency if is maximum and if it is I allocate a new
   node and I fill its fields with the data from the last element from the old
   list.
* The function returns the new list updated with all the elements from the
   old list having the maximum frequency.
