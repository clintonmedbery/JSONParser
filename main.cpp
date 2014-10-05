//
//  main.cpp
//  JSONParser
//
//  Created by Clinton Medbery on 10/2/14.
//  Copyright (c) 2014 Clinton Medbery. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>
#include "cJSON.h"


void ParseObject(cJSON *root){
    
    cJSON* age = NULL;
    cJSON* name = NULL;
    cJSON* subitem = NULL;
    
    int i;
    
    cJSON* items = cJSON_GetObjectItem(root, "items");
    
    cJSON* item = cJSON_GetObjectItem(items,"items");
    
    for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
    {
        subitem = cJSON_GetArrayItem(item, i);
        name = cJSON_GetObjectItem(subitem, "name");
        age = cJSON_GetObjectItem(subitem, "index");
       
    }
       }

void printJSon(cJSON* node)
{
    if(node != NULL)
    {
        // Name label for this node.
        if(node->string != NULL)
            std::cout << "AttributeName[" << node->string << "]: ";
        
        // cJSON_Number
        // cJSON_String
        // cJSON_Array
        // cJSON_Object
        
        // Interrogate type of node.
        if(node->type == cJSON_Array)
        {
            std::cout << "type(array)" << std::endl;
          // Loop along linked list of nodes.
            cJSON* child = node->child;
            
          // Recursively print contents of child node.
            while(child != NULL)
            {
               printJSon(child);
               // Advance to next child in the linked list.
                child = child->next;
            }// end while loop over children in linked list.
        }// end if node is an array (or linked list).
        else if(node->type == cJSON_Object)
        {
            std::cout << "type(object)" << std::endl;
            // An object may have a child.
            // If it does recursively process child.
            if(node->child != NULL)
                printJSon(node->child);
        }
        else if(node->type == cJSON_String)
        {
            std::cout << "type(string)" << std::endl;
           if(node->valuestring != NULL)
               std::cout << node->valuestring << std::endl;
        }
        else if(node->type == cJSON_Number)
        {
            std::cout << "type(number)" << std::endl;
            // Assume all numeric attributes are double.
            std::cout << node->valuedouble << std::endl;
        }
    }// end if node is not null.
}// end function.

void printAttributeValuePairs(cJSON* root)
{
    // Assume we have a list of name: value pairs.
    // { "name": "Clinton", "age": 30 }
    
    cJSON* child = root->child;
    
    // Recursively print contents of child node.
    while(child != NULL)
    {
        // Assum each child is a cJSON_Object.
        
        // Attribute name.
        std::cout << "AttributeName[" << child->string << "]: ";
        
        // Attribute value expected as a string.
        std::cout << "AttributeValue[" << child->valuestring << "]" << std::endl;
        
        
        // Advance to next child in the linked list.
        child = child->next;
    }// end while loop over children in linked list.
}

/*
 * @param root Root of JSON document or node.
 * @param attributeName Name of attribute whose value we want to print.
 */
void printSelectedAttributeValue(cJSON* root, char* attributeName)
{
    // Find child node having the given attribute name.
    cJSON * node = cJSON_GetObjectItem(root, attributeName);
    // If such a child is found...
    if(node != NULL)
    {
        // Attribute name.
        std::cout << "AttributeName[" << node->string << "]: ";
        
        // Attribute value expected as a string.
        std::cout << "AttributeValue[" << node->valuestring << "]" << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    
    std::cout << "Parser Initiated\n";
    // std::string json = "{\n\"name\":\"Clint\",\n\"age\":99\"\n}";
    // std::string json = "{ \"name\": \"Clint\" }";
    
    char text2[]="[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
    
    std::cout << text2 << std::endl;
    
    // Get C-style string from given C++ string.
    // Get back a pointer top-level cJSON object.
    cJSON* jsonRoot = cJSON_Parse(text2);
    
    if(jsonRoot == NULL)
    {
      // If the parse fails, we can request the error messages.
      const char * errorMessgPtr = cJSON_GetErrorPtr();
      // Since errorMessgPtr is a pointer we must de-reference using the * to access
      // the actual char string data.
      std::cout << "Parse failed.  Error: " << *errorMessgPtr << std::endl;
        
      // Quit with fail code.
      exit(EXIT_FAILURE);
    }
    
/*
        
    // Pretty-print the JSON object.
    std::cout << "JSON OBJECT..." << std::endl;
    char  *prettyPrintStr = cJSON_Print(jsonObject);
    std::cout << *prettyPrintStr << std::endl;
    // cJSON style recommends deallocating pretty print string.
    delete prettyPrintStr;
    // Clear pointer to NULL.
    prettyPrintStr = NULL;
 */
    
    
    printJSon(jsonRoot);

    
    
//    std::ifstream inFile;
//    inFile.open("/test.json");
//    std::stringstream strStream;
//    strStream << inFile.rdbuf();
//    
//    std::string str = strStream.str();
//    
//    std::cout << str << std::endl;
    
}
