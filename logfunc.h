#pragma once

/**
 * @file
 * @brief This file contains the headers of logic gate functions and related utility functions.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <string>

using Map = std::map<std::string, int>;
using StrVector = std::vector<std::string>;

/**
 * @brief This function handles logic gate operations stored in a vector of strings.
 *
 * The function checks if the pins used as arguments in the logic operations have initialized values.
 * If the values of pins have been initialized, the function performs logic gate operations 
 * specified in the first element of the provided vector of strings and updates the corresponding element in the provided
 * map.
 * Otherwise, if any of the pins has not been initialiszed, the function prints an error message.
 *
 * Supported gate types include:
 * - AND
 * - NAND
 * - OR
 * - NOR
 * - XOR
 * - XNOR
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic gate operations.
 * @param stringVec Vector of strings representing the gate operation. The first element
 *                  specifies the gate type, the next two elements specify the input pins,
 *                  and the last element specifies the output pin.
 * @param lineNum Number of the line from which the operation string was taken. Used for printing errors.
 * @param name Name of the file from which the operation string was taken. Used for printing errors.
 * 
 * @note The type of gate is stored in the first element of the array (counting from 0), the arguments are stored in the second and third.
 */
void gateHandling(Map &pointMap, StrVector &stringVec, const int &lineNum, const std::string &name);

/**
 * @brief Implements the NOT logic gate operation.
 *
 * The function takes an integer input and performs the NOT logic gate operation.
 * If the input is 0, the function returns 1; otherwise, it returns 0.
 *
 * @param a The input integer value.
 * @return The result of the NOT logic gate operation on the input.
 */
int gateNot(int a);

/**
 * @brief Implements the AND logic gate operation.
 *
 * The function takes two integer inputs and performs the AND logic gate operation.
 * If both inputs are 1, the function returns 1; otherwise, it returns 0.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the AND logic gate operation on the inputs.
 */
int gateAnd(int a, int b);

/**
 * @brief Implements the OR logic gate operation.
 *
 * The function takes two integer inputs and performs the OR logic gate operation.
 * If at least one input is 1, the function returns 1; otherwise, it returns 0.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the OR logic gate operation on the inputs.
 */
int gateOr(int a, int b);

/**
 * @brief Implements the XOR logic gate operation.
 *
 * The function takes two integer inputs and performs the XOR logic gate operation.
 * If the inputs are different, the function returns 1; otherwise, it returns 0.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the XOR logic gate operation on the inputs.
 */
int gateXor(int a, int b);

/**
 * @brief Checks if the input string represents a numeric value.
 *
 * The function checks whether the provided string is empty or not.
 * If the string is empty the function returns false.
 * If the string is not empty, the function iterates through each character of the input string and verifies
 * whether all characters are numeric (0-9). 
 * If the string contains any non-numeric characters, the function returns false.
 * If the function successfully iterates through the whole string without returning false, it returns true.
 *
 * @param input The input string to be checked for numeric content.
 * @return true if the input string is non-empty and contains only numeric characters, otherwise false.
 *
 * @note Leading or trailing spaces are not accepted and will cause the function to return false.
 */
bool checkString(const std::string &input);

/**
 * @brief Splits a string into a vector of substrings using the space (' ') character as the delimiter.
 *
 * This function takes a string and splits it into individual substrings using space (' ')
 * as the delimiter. The resulting substrings are stored in a provided vector of strings.
 *
 * @param inputv Reference to a vector of strings to store the resulting substrings.
 * @param input The input string to be split.
 */
void splitString(StrVector &inputv, const std::string &input);

/**
 * @brief Checks if the provided file name includes the .txt file extension.
 *
 * This function takes a string representing a file name and checks if it
 * includes the .txt file extension. If the .txt extension is found it returns the name.
 * If the extension is not found, the user is informed that such file type is required and the program is ended.
 *
 * @param input The input string representing a file name.
 * @return The original file name.
 *
 * @note The function checks for the presence of the .txt file extension in a case-sensitive manner.
 * @note If the .txt extension is found, the name of the file is returned.
 * @note If the .txt extension is not found, a message is printed to the console output and the program is ended.
 * @note This function is called before creating any file stream variables to avoid the program from closing improperly.
 */
std::string fileExtension(const std::string &input);

/**
 * @brief This function checks the amount of provided command-line arguments as well as the arguments themselves and performs the necessary operations.
 *
 * The function takes the number of arguments, the three string variables for storing the input file names, and the argument array.
 * If only one argument has been used, the function prints a short guide on how to use the program.
 * In the case of any other number of arguments not equal 7, the function prints an error message and exits the program.
 * The function checks if the appropiate flags have been used as the arguments and uses the arguments after them as the input and output file names.
 *
 * @param argnum The number of command-line arguments
 * @param name1 The input string representing an input file name.
 * @param name2 The input string representing an input file name.
 * @param name3 The input string representing an output file name.
 * @param args The array of command-line arguments.
 *
 * @note If only one argument was used, a help message is printed to the console output.
 * @note If any number of arguments different than 1 or 7 was used, an error message is printed to the console output.
 * @note The arguments are assigned as the names of the input files for the program.
 * @note Input files are validated using the fileExtension function, but the output file is not.
 */
void handleArguments(int argnum, std::string &name1, std::string &name2, std::string &name3, char **&args);

/**
 * @brief This function checks if the input file has been opened correctly.
 *
 * The function takes the ifstream variable for the input file, as well as its name stored in a string.
 * If the file hasn't been opened correctly, the function prints an error message and returns false.
 * If the file has been opened correctly, the function returns true.
 *
 * @param file The ifstream variable for the input file.
 * @param name The name of the input file.
 * @return true if the file has been opened, otherwise false.
 */
bool checkInFile(std::ifstream &file, const std::string &name);

/**
 * @brief This function checks if the output file has been opened correctly.
 *
 * The function takes the ofstream variable for the output file, as well as its name stored in a string.
 * If the file hasn't been opened correctly, the function prints an error message and returns false.
 * If the file has been opened correctly, the function returns true.
 *
 * @param file The ofstream variable for the output file.
 * @param name The name of the output file.
 * @return true if the file has been opened, otherwise false.
 */
bool checkOutFile(std::ofstream &file, const std::string &name);

/**
 * @brief This function initialises the map for storing indexes of pins and their values, as well as the inputs and outputs for the circuits, using pin names from the input file.
 *
 *  Initialises the map for storing names of pins and their values, as well as the inputs and outputs for the circuits, using pin indexes from the input file.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 * @param file The name of the input file.
 * @param inVector The vector storing the indexes of input pins.
 * @param outVector The vector storing the indexes of output pins.
 *
 * @note The function assumes a specific file format with "IN:" and "OUT:" sections and individual numeric values.
 */
void initMap(Map &pointMap, std::ifstream &file, StrVector &inVector, StrVector &outVector);

/**
 * @brief This function prints input and corresponding output values to the output file.
 *
 * This function prints the input and output values of the given logic circuit, stored in the map, to the output file. 
 * The function checks if the vectors storing indexes of input and output pins are not empty and if the values of these pins are initialized.
 * If the values were not initialized, it means the input file must have had an incorrect order of logic operations.
 * If an issue is detected, it prints an error message to the standard error stream and returns false. 
 * Otherwise, it returns true.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 * @param file An output file stream to write the input and output values.
 * @param inVector Reference to a vector of strings containing input points.
 * @param outVector Reference to a vector of strings containing output points.
 * @param name Reference to the name of the input file, from which input and output indexes were taken. Used for printing errors.
 * @return true if the input and output values are successfully printed, false otherwise.
 *
 * @note If either input or output vectors are empty, it prints an error message and returns false.
 * @note If an output value in the point map is -1, it indicates an incorrect order of gates, and the function returns false.
 */
bool printToOutput(Map &pointMap, std::ofstream &file, StrVector &inVector, StrVector &outVector, std::string &name);

/**
 * @brief This function updates input values in the map of pins based on the provided text line.
 *
 * This function takes a text line, which includes indexes of pins and their values, and updates the corresponding pins
 * in the map. 
 * It checks for correctness in the input values, ensuring that both the index and its value are numeric.
 * The function also checks if the line includes the ':' symbol. 
 * If an issue is detected, it prints an error
 * message to the standard output stream and returns false. 
 * Otherwise, it returns true.
 *
 * @param textLine The text line containing input values in the format "index:value index:value ...".
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated with new input values.
 * @param lineNum Number of the line from the file, which was used as the argument. Used for printing errors.
 * @param name Reference to a file name, from which the new values were taken. Used for printing errors.
 * @return true if the input values are successfully updated, false otherwise.
 *
 * @note The function expects input values in the format "index:value" separated by spaces.
 * @note It checks that both the index and its value are numeric, and the value is either '0' or '1'.
 * @note If an issue is detected, it prints an error message and returns false.
 */
bool updateInputValues(const std::string &textLine, Map &pointMap, const int &lineNum, const std::string &name);

/**
 * @brief This function reads the data from the input file and uses it to execute the logic operations, updating the map of pins.
 *
 * This function reads the contents of the input file line by line, splitting each line into a vector of strings
 * and then passing that vector to the gate interpreting function.
 * The function also keeps track of the number of the current line in the file.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic operations from the input file.
 * @param file An input file stream containing logic operations to be applied.
 * @param name The name of the input file with circuit data.
 *
 * @note The function assumes that the input file contains logic operations, one per line.
 * @note It uses the gateHandling function to process and update the point map based on the logic operations.
 */
void fileToLogic(Map &pointMap, std::ifstream &file, const std::string &name);

/**
 * @brief Checks if the given index has been initialised in the provided map.
 *
 * This function iterates through the map and checks if the index provided in the pin variable matches any of the elements from the map.
 * If a match is found, the function returns true.
 * If the function finishes iterating without returning true, it returns false.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic operations from the input file.
 * @param pin Index of the pin to find.
 * @return true if index was found in the map, otherwise false.
 */
bool isInit(Map &pointMap, const std::string &pin);
