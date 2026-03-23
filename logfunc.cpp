/**
 * @file
 * @brief This file contains the implementation of logic gate functions and related utility functions.
 */

#include "logfunc.h"

/**
 * @brief This function handles logic gate operations stored in a vector of strings.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic gate operations.
 * @param stringVec Vector of strings representing the gate operation. The first element
 *                  specifies the gate type, the next two elements specify the input pins,
 *                  and the last element specifies the output pin.
 * @param lineNum Number of the line from which the operation string was taken. Used for printing errors.
 * @param name Name of the file from which the operation string was taken. Used for printing errors.
 * 
 * @details The type of logic gate is stored in the first element of the array (counting from 0), the arguments are stored in the second and third.
 */
void gateHandling(Map &pointMap, StrVector &stringVec, const int &lineNum, const std::string &name)
{
    // CHECKING IF ARGUMENT INDEX IS INITIALIZED
    if(!isInit(pointMap, stringVec[1]) || !isInit(pointMap, stringVec[2])){
        std::string gates = "AND NAND OR NOR XOR XNOR";
        if(gates.find(stringVec[0]) != std::string::npos){
            std::cout << "Skipping operation " << stringVec[0] << " trying to use pin '" << (pointMap[stringVec[1]] == -1 ? stringVec[1] : stringVec[2]) << "' as an argument before initialising it's value. [File: " << name << "; line: " << lineNum << "]" << std::endl;
        }
    } else
    // CHECKING IF THE ARGUMENT VALUES ARE INITIALIZED
    if(pointMap[stringVec[1]] == -1 || pointMap[stringVec[2]] == -1) {
        // CHECKING IF THE OPERATION IS ONE OF THE GATES IN ORDER TO NOT CREATE FALSE POSITIVES
        std::string gates = "AND NAND OR NOR XOR XNOR";
        if(gates.find(stringVec[0]) != std::string::npos){
            std::cout << "Skipping operation " << stringVec[0] << " trying to use pin '" << (pointMap[stringVec[1]] == -1 ? stringVec[1] : stringVec[2]) << "' as an argument before initialising it's value. [File: " << name << "; line: " << lineNum << "]" << std::endl;
        }
    } else{
        // CHECKING WHICH GATE THE OPERATION WRITTEN IN THE STRING IS AND PERFORMING THE LOGIC OPERATION WITH THE PROVIDED PINS
        if (stringVec[0] == "AND") 
        {
            pointMap[stringVec[3]] = gateAnd(pointMap[stringVec[1]], pointMap[stringVec[2]]);
        }
        else if (stringVec[0] == "NAND") 
        {
            pointMap[stringVec[3]] = gateNot(gateAnd(pointMap[stringVec[1]], pointMap[stringVec[2]]));
        }
        else if (stringVec[0] == "OR")
        {
            pointMap[stringVec[3]] = gateOr(pointMap[stringVec[1]], pointMap[stringVec[2]]);
        }
        else if (stringVec[0] == "NOR") 
        {
            pointMap[stringVec[3]] = gateNot(gateOr(pointMap[stringVec[1]], pointMap[stringVec[2]]));
        }
        else if (stringVec[0] == "XOR") 
        {
            pointMap[stringVec[3]] = gateXor(pointMap[stringVec[1]], pointMap[stringVec[2]]);
        }
        else if (stringVec[0] == "XNOR") 
        {
            pointMap[stringVec[3]] = gateNot(gateXor(pointMap[stringVec[1]], pointMap[stringVec[2]]));
        }
    }
}

/**
 * @brief Implements the NOT logic gate operation.
 *
 * @param a The input integer value.
 * @return The result of the NOT logic gate operation on the input.
 */
int gateNot(int a)
{
    if (a == 0)
        return 1;
    else
        return 0;
}

/**
 * @brief Implements the AND logic gate operation.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the AND logic gate operation on the inputs.
 */
int gateAnd(int a, int b)
{
    if (a == 1 && b == 1)
        return 1;
    else
        return 0;
}

/**
 * @brief Implements the OR logic gate operation.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the OR logic gate operation on the inputs.
 */
int gateOr(int a, int b)
{
    if (a == 1 || b == 1)
        return 1;
    else
        return 0;
}

/**
 * @brief Implements the XOR logic gate operation.
 *
 * @param a The first input integer value.
 * @param b The second input integer value.
 * @return The result of the XOR logic gate operation on the inputs.
 */
int gateXor(int a, int b)
{
    if (a != b)
        return 1;
    else
        return 0;
}

/**
 * @brief Checks if the input string represents a numeric value.
 *
 * @param input The input string to be checked for numeric content.
 * @return true if the input string is non-empty and contains only numeric characters, otherwise false.
 */
bool checkString(const std::string &input)
{
    // CHECK IF THE STRING IS NOT EMPTY
    if(input.length() < 1) return false;

    // CHECKS IF THE STRING IS A NUMBER
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] < '0' || input[i] > '9')
            // IF THE STRING INCLUDES A NON NUMERIC CHARACTER - RETURN FALSE
            return false;
    }
    // IF EVERYTHING IS CORRECT RETURN TRUE
    return true;
}

/**
 * @brief Splits a string into a vector of substrings using the space (' ') character as the delimiter.
 *
 * @param inputv Reference to a vector of strings to store the resulting substrings.
 * @param input The input string to be split.
 */
void splitString(StrVector &inputv, const std::string &input)
{
    // FUNCTION FOR SPLITTING A STRING INTO A VECTOR
    int lastPos = 0;
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ')
        {
            inputv.push_back(input.substr(lastPos, i - lastPos));
            lastPos = i + 1;
        }
    }
    inputv.push_back(input.substr(lastPos, input.length() - lastPos));
}

/**
 * @brief Checks if the provided file name includes the .txt file extension.
 *
 * @param input The input string representing a file name.
 * @return The original file name.
 * 
 * @details If the extension is not found, the entire program is closed.
 */
std::string fileExtension(const std::string &input)
{
    // CFHECK IF IT INCLUDES .txt FILE EXTENSION
    size_t found = input.find(".txt");
    if (found == std::string::npos)
    {
        // IF NOT FOUND INFORM THE USER
        std::cout << "Input files must be .txt files";
        exit(1);
    }
    // IF FOUND RETURN THE NAME
    return input;
}

/**
 * @brief This function checks the amount of provided command-line arguments as well as the arguments themselves and performs the necessary operations.
 *
 * @param argnum The number of command-line arguments
 * @param name1 The input string representing an input file name.
 * @param name2 The input string representing an input file name.
 * @param name3 The input string representing an output file name.
 * @param args The array of command-line arguments.
 * 
 * @details If only one argument was used, help is printed to the console. If any different number of arguments, other than 7 was used, an error message is printed. The arguments after the flags are set as the names of input files for the program.
 */
void handleArguments(int argnum, std::string &name1, std::string &name2, std::string &name3, char **&args)
{
    if (argnum == 1)
    {
        // PRINTING HELP
        std::cout << "Calculates the output signal for the given logic diagram (represented by a list of gates with their inputs and outputs), for each combination of given inputs. \n\n Options: \n -u \t input file with circuit data \n -i \t input file with all input combinations to use \n -o \t output file \n \n Example input circuit structure: \n\n IN: 1 2 3 \n OUT: 5 \n OR: 1 2 4 \n AND: 3 4 \n\n Example structure for circuit inputs: \n\n 1:0 2:1 3:1 \n 1:0 2:0 3:0 ";
        exit(0);
    } else if (argnum != 7)
    {
        // PRINTING A WARNING WHEN THE ARGUMENT COUNT IS INCORRECT
        std::cout << "Improper argument count [Execute program without arguments to display a short guide on how to use the program.]";
        exit(1);
    }

    // CHECKING INPUTS IN ARGUMENTS
    std::string argname;
    for (int i = 1; i < argnum; i++)
    {
        argname = args[i];
        if (argname == "-u")
        {
            // Circuit
            if (i < argnum - 1)
                name1 = fileExtension(args[i + 1]);
            else
            {
                std::cout << "Improper inputs [Execute program without arguments to display a short guide on how to use the program.]";
                exit(1);
            }
        }
        else if (argname == "-i")
        {
            // Inputs
            if (i < argnum - 1)
                name2 = fileExtension(args[i + 1]);
            else
            {
                std::cout << "Improper inputs [Execute program without arguments to display a short guide on how to use the program.]";
                exit(1);
            }
        }
        else if (argname == "-o")
        {
            // Output
            if (i < argnum - 1)
                name3 = args[i+1];
            else
            {
                std::cout << "Improper inputs [Execute program without arguments to display a short guide on how to use the program.]";
                exit(1);
            }
        }
    }
}

/**
 * @brief This function checks if the input file has been opened correctly.
 *
 * @param file The ofstream variable for the input file.
 * @param name The name of the input file.
 * @return true if the file has been opened, otherwise false.
 */
bool checkInFile(std::ifstream &file, const std::string &name)
{
    // CHECK IF FILE HAS BEEN OPENED CORRECTLY
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << name << std::endl;
        return false;
    } else return true;
}

/**
 * @brief This function checks if the output file has been opened correctly.
 *
 * @param file The ofstream variable for the output file.
 * @param name The name of the output file.
 * @return true if the file has been opened, otherwise false.
 */
bool checkOutFile(std::ofstream &file, const std::string &name)
{
    // CHECK IF FILE HAS BEEN OPENED CORRECTLY
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << name << std::endl;
        return false;
    } else return true;
}

/**
 * @brief This function initialises the map for storing indexes of pins and their values, as well as the inputs and outputs for the circuits, using pin names from the input file.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 * @param file The name of the input file.
 * @param inVector The vector storing the indexes of input pins.
 * @param outVector The vector storing the indexes of output pins.
 */
void initMap(Map &pointMap, std::ifstream &file, StrVector &inVector, StrVector &outVector)
{
    std::string temp;
    while (file >> temp)
    {
        if (temp == "IN:")
        {
            // SPLIT THE STRING AFTER "IN:" INTO A VECTOR AND INSERT EACH NUMERIC VALUE INTO THE ARRAY
            (getline(file, temp));
            StrVector sVector;
            splitString(sVector, temp);
            for(std::string st: sVector){
                if(checkString(st)) inVector.push_back(st);
            }
        }
        else if (temp == "OUT:")
        {
            // SPLIT THE STRING AFTER "OUT:" INTO A VECTOR AND INSERT EACH NUMERIC VALUE INTO THE ARRAY
            (getline(file, temp));
            StrVector sVector;
            splitString(sVector, temp);
            for(std::string st: sVector){
                if(checkString(st)) outVector.push_back(st);
            }
        }
        if (checkString(temp))
        {
            // IF THE STRING IS A NUMBER INITIALISE ITS INDEX IN THE MAP
            pointMap[temp] = -1;
        }
    }
}

/**
 * @brief This function prints input and corresponding output values to the output file.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 * @param file An output file stream to write the input and output values.
 * @param inVector Reference to a vector of strings containing input points.
 * @param outVector Reference to a vector of strings containing output points.
 * @param name Reference to the name of the input file, from which input and output indexes were taken. Used for printing errors.
 * @return true if the input and output values are successfully printed, false otherwise.
 */
bool printToOutput(Map &pointMap, std::ofstream &file, StrVector &inVector, StrVector &outVector, std::string &name)
{
    // IF EITHER VECTOR IS EMPTY THEN ONE OF THE INPUT FILES WAS INCORRECT
    if(inVector.empty() || outVector.empty()){
        std::cerr << "Improper format in file: '" << name << "' [Execute program without arguments to display a short guide on how to use the program.]";
        return false;
    }

    // PRINTING TO OUTPUT
    file << "IN: ";
    // PRINTING INPUTS
    for (int i = 0; i < inVector.size(); i++)
    {
        file << inVector[i] << ":" << pointMap[inVector[i]] << " ";
    }
    // PRINTING OUTPUTS
    file << "OUT: ";
    for (int i = 0; i < outVector.size(); i++)
    {
        // IF OUTPUT VALUE IS -1 THEN THE ORDER OF GATES WAS INCORRECT
        if(pointMap[outVector[i]] == -1){
            std::cerr << "Operation unsuccessful: incorrect input data [Execute program without arguments to display a short guide on how to use the program.]";
            return false;
        } else file << outVector[i] << ":" << pointMap[outVector[i]] << " ";

    }
    file << std::endl;
    // IF PRINTING WAS SUCCESSFUL THEN RETURN TRUE
    return true;
}

/**
 * @brief This function updates input values in the map of pins based on the provided text line.
 *
 * @param textLine The text line containing input values in the format "index:value index:value ...".
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated with new input values.
 * @param lineNum Number of the line from the file, which was used as the argument. Used for printing errors.
 * @param name Reference to a file name, from which the new values were taken. Used for printing errors.
 * @return true if the input values are successfully updated, false otherwise.
 */
bool updateInputValues(const std::string &textLine, Map &pointMap, const int &lineNum, const std::string &name)
{
    // UPDATING INPUTS WITH THE NEW VALUES
    StrVector sVector;
    splitString(sVector, textLine);
    for(std::string st: sVector){
        // FINDING THE : symbol IN THE STRING
        size_t pos = st.find(":");
        // IF NOT FOUND RETURN FALSE
        if(pos == std::string::npos){
            std::cerr << "Improper format in file: '" << name << "' on line: " << lineNum << " [Execute program without arguments to display a short guide on how to use the program.]";
            return false;
        }
        // CHECKING IF BOTH THE INDEX AND ITS VALUE ARE NUMBERS
        if(checkString(st.substr(0, pos)) && (st.substr(pos+1, st.length()-1) == "0" || st.substr(pos+1, st.length()-1) == "1")) {
            pointMap[st.substr(0, pos)] = stoi(st.substr(pos+1, st.length()-1));
        } else {
            std::cerr << "Improper values of inputs. Inputs must be equal either '0' or '1'. [File: " << name << "; line: " << lineNum << "]";
            return false;
        }
    }
    // IF PROCESS WAS SUCCESSFUL THEN RETURN TRUE
    return true;
}

/**
 * @brief This function reads the data from the input file and uses it to execute the logic operations, updating the map of pins.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic operations from the input file.
 * @param file An input file stream containing logic operations to be applied.
 * @param name The name of the input file with circuit data.
 */
void fileToLogic(Map &pointMap, std::ifstream &file, const std::string &name)
{
    file.open(name);
    std::string temp;
    StrVector sVector;
    int line = 1;
    // LOOP FOR READING ALL LINES FROM THE CIRCUIT INPUT AND EXECUTING THE LOGIC OPERATIONS
    while (std::getline(file, temp))
    {
        // SPLITTING THE INPUT INTO SEPARATE STRING AND PUTTING THEM INTO THE VECTOR
        splitString(sVector, temp);
        // HANDLING LOGIC GATES
        gateHandling(pointMap, sVector, line, name);
        // CLEARING THE VECTOR
        sVector.clear();

        // INCREMENT LINE COUNTER
        line++;
    }
    file.close();
}

/**
 * @brief Checks if the given index has been initialised in the provided map.
 *
 * @param pointMap Reference to a map with string keys representing pin indexes and their integer values.
 *                 This map is updated based on the logic operations from the input file.
 * @param pin Index of the pin to find.
 * @return true if index was found in the map, otherwise false.
 */
bool isInit(Map &pointMap, const std::string &pin){
    for(auto p: pointMap){
        if(pin == p.first) return true;
    }
    return false;
}