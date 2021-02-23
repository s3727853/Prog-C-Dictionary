Changes to code:

word_list.c

Changing the return type of load_dictionary. This function returned a BOOLEAN 
initialy, however I have changed it so that it returns a populated word list, 
providing the words file passed in was correct. This change allows for greater 
flexibility for the calling method as it can easily validate that the return is
not NULL and it has access to the word_list structure that has been created and
populated. !!!!!!!CHECK THIS WAS IN SOURCE CODE A BOOLEAN RETURN!!!!!!!! 
