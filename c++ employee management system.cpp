#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <filesystem>
#include <sstream>

static void createEmployee()
{
    std::string ID;
    std::string firstName;
    std::string lastName;
    std::string DOB;
    std::string salary;
    std::string input;

    while (true)
    {
        std::cout << "--------------------------------------------------------" << std::endl << "Type \"exit\" anytime to cancel" << std::endl;
    
        std::cout << "Enter employee ID:" << std::endl;
        std::cin >> input;
        if (input == "exit")
            return;
        ID = input;

        std::cout << "Enter employee first name:" << std::endl;
        std::cin >> input;
        if (input == "exit")
            return;
        firstName = input;

        std::cout << "Enter employee last Name:" << std::endl;
        std::cin >> input;
        if (input == "exit")
            return;
        lastName = input;

        std::cout << "Enter employee date of birth (dd/mm/yyyy):" << std::endl;
        std::cin >> input;
        if (input == "exit")
            return;
        DOB = input;

        std::cout << "Enter salary:" << std::endl;
        std::cin >> input;
        if (input == "exit")
            return;
        salary = input;

        while (true)
        {
            std::cout << "Edit anything? (y/n)" << std::endl;
            std::cin >> input;
            if (input == "exit")
                return;
            else if (input == "y")
            {
                std::cout << "(type \"ID\" to edit employee ID)" << std::endl <<
                    "(type \"first name\" to edit first name)" << std::endl <<
                    "(type \"last name\" to edit last name)" << std::endl <<
                    "(type \"DOB\" to edit date of birth)" << std::endl <<
                    "(type \"salary\" to edit salary)" << std::endl <<
                    "(type \"exit\" to not edit anything anymore)" << std::endl;
                while (true)
                {
                    std::cout << "What do you want to edit?" << std::endl;
                    std::cin >> input;
                    if (input == "ID")
                    {
                        std::cout << "Enter new employee ID:" << std::endl;
                        std::cin >> input;
                        ID = input;
                        std::cout << "OK." << std::endl << std::endl;
                    }
                    if (input == "first name")
                    {
                        std::cout << "Enter new first name:" << std::endl;
                        std::cin >> input;
                        firstName = input;
                        std::cout << "OK." << std::endl << std::endl;
                    }
                    if (input == "last name")
                    {
                        std::cout << "Enter new last name:" << std::endl;
                        std::cin >> input;
                        lastName = input;
                        std::cout << "OK." << std::endl << std::endl;
                    }
                    if (input == "DOB")
                    {
                        std::cout << "Enter new date of birth:" << std::endl;
                        std::cin >> input;
                        DOB = input;
                        std::cout << "OK." << std::endl << std::endl;
                    }
                    if (input == "salary")
                    {
                        std::cout << "Enter new salary:" << std::endl;
                        std::cin >> input;
                        salary = input;
                        std::cout << "OK." << std::endl << std::endl;
                    }
                    if (input == "exit")
                        break;
                }
                std::ofstream outputFile("employees/" + firstName + "-" + lastName + "-" + ID + ".txt");


                if (!outputFile.is_open())
                {
                    std::cerr << "There was an error opening the file!" << std::endl;
                }

                outputFile << ID << '\n';
                outputFile << firstName << '\n';
                outputFile << lastName << '\n';
                outputFile << DOB << '\n';
                outputFile << salary << '\n';

                outputFile.close();
                std::cout << "File created!" << std::endl;
                break;
            }
            else if (input == "n")
            {
                std::ofstream outputFile("employees/" + firstName + "-" + lastName + "-" + ID + ".txt");


                if (!outputFile.is_open())
                {
                    std::cerr << "There was an error opening the file!" << std::endl;
                    return;
                }

                outputFile << ID << "\n";
                outputFile << firstName << '\n';
                outputFile << lastName << '\n';
                outputFile << DOB << '\n';
                outputFile << salary << '\n';

                outputFile.close();
                std::cout << "File created!" << std::endl;
                return;
            }
        }
    }
}

static bool fileExists(const std::string& filename)
{
    return std::filesystem::exists("employees/" + filename + ".txt");
}

static void replace(const std::string& filename, int lineNumber, const std::string& newText) {
    std::fstream file(filename, std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    std::string line;
    std::stringstream updatedContent;

    for (int currentLineNumber = 1; std::getline(file, line); ++currentLineNumber) {
        if (currentLineNumber == lineNumber) {
            // Replace text in the current line
            updatedContent << newText << '\n';
        } else {
            // Keep the original line
            updatedContent << line << '\n';
        }
    }

    // Clear the contents of the file
    file.close();
    std::ofstream clearFile(filename, std::ios::trunc);
    clearFile.close();

    // Write the updated content back to the file
    std::ofstream outputFile(filename, std::ios::app);
    outputFile << updatedContent.str();
}

// if dashNum is default, it will replace the first name
// if dashNum is 1, it will replace the last name
// if dashNum is 2, it will replace the ID
// if it's anything else, the function will print an error

static std::string replaceTextInFilename(std::string filename, const std::string& newText, int spaceNum = 0)
{
    size_t firstSpacePos = filename.find('-');
    if (firstSpacePos != std::string::npos) 
    {

        size_t charAfterFirstSpacePos = firstSpacePos + 1;

        size_t secondSpacePos = filename.find('-', charAfterFirstSpacePos);

        size_t charAfterSecondSpacePos = secondSpacePos + 1;

        if (spaceNum == 0)
        {
            size_t lengthToReplace = (firstSpacePos != std::string::npos) ? firstSpacePos : std::string::npos;

            filename.replace(0, lengthToReplace, newText);
        }
        else if (spaceNum == 1)
        {
            size_t lengthToReplace = (secondSpacePos != std::string::npos) ? secondSpacePos - charAfterFirstSpacePos : std::string::npos;
 
            filename.replace(charAfterFirstSpacePos, lengthToReplace, newText);
        }
        else if (spaceNum == 2)
        {
            size_t lengthToReplace = (secondSpacePos != std::string::npos) ? std::string::npos - secondSpacePos : std::string::npos;

            filename.replace(charAfterSecondSpacePos, lengthToReplace, newText);
        }
    }
    return filename + ".txt";
}

void renameFile(const std::string& oldFilename, const std::string& newFilename)
{
    int result = std::rename(oldFilename.c_str(), newFilename.c_str());
    if (result == 0)
    {
        std::cout << "File renamed successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Error renaming file.";
    }
}

static void editEmployee()
{
    std::string firstName;
    std::string lastName;
    std::string ID;
    std::string DOB;
    std::string salary;
    std::string input;
    std::string filename;

    std::string dotTxt = ".txt";

    std::cout << "--------------------------------------------------------" << std::endl << "Type file name to edit exactly in this format: Firstname-Lastname-ID (with hyphens): ";
    std::cin >> filename;

    if(!fileExists(filename))
    {
        std::cerr << "File \"" << filename << "\" does not exist!" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Found file!" << std::endl << 
        "(type \"ID\" to edit employee ID)" << std::endl <<
        "(type \"first name\" to edit first name)" << std::endl <<
        "(type \"last name\" to edit last name)" << std::endl <<
        "(type \"DOB\" to edit date of birth)" << std::endl <<
        "(type \"salary\" to edit salary)" << std::endl <<
        "(type \"exit\" to not edit anything anymore)" << std::endl <<
        "(Replacing the part(s) of the name or ID will change the file name accordingly.)" << std::endl;
    while (true)
    {
        std::cout << "--------------------------------------------------------" << std::endl << "What do you want to edit?" << std::endl;
        std::getline(std::cin, input);
        
        if (input == "ID")
        {
            std::cout << "Enter new employee ID:" << std::endl;
            std::cin >> ID;
            replace("employees/" + filename + ".txt", 1, ID);
            std::string newFilename = replaceTextInFilename("employees/" + filename + ".txt", ID, 2);
            renameFile("employees/" + filename + ".txt", newFilename);
            std::cout << "OK." << std::endl;
        }
        if (input == "first name")
        {
            std::cout << "Enter new first name:" << std::endl;
            std::cin >> firstName;
            replace("employees/" + filename + ".txt", 0, firstName);
            std::string newFilename = replaceTextInFilename("employees/" + filename + ".txt", firstName, 0);
            renameFile("employees/" + filename + ".txt", newFilename);
            std::cout << "OK." << std::endl;
        }
        if (input == "last name")
        {
            std::cout << "Enter new last name:" << std::endl;
            std::cin >> lastName;
            replace("employees/" + filename + ".txt", 1, lastName);
            std::string newFilename = replaceTextInFilename("employees/" + filename + ".txt", lastName, 1);
            renameFile("employees/" + filename + ".txt", newFilename);
            std::cout << "OK." << std::endl;
        }
        if (input == "DOB")
        {
            std::cout << "Enter new date of birth:" << std::endl;
            std::cin >> DOB;
            replace(filename + ".txt", 4, DOB);
            std::cout << "OK." << std::endl;
        }
        if (input == "salary")
        {
            std::cout << "Enter new salary:" << std::endl;
            std::cin >> salary;
            replace(filename + ".txt", 5, salary);
            std::cout << "OK." << std::endl;
        }
        if (input == "exit")
        {
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static void deleteEmployee()
{
    std::string filename;

    std::cout << std::endl << "--------------------------------------------------------" << std::endl << "Type exact file name of file to delete in this format: Firstname-Lastname-ID: " << std::endl << "or type \"exit\" to cancel." << std::endl;
    std::cin >> filename;
    //(fileExists automatically adds a .txt to filename)

    std::string fullFilename = filename + ".txt";

    if(!fileExists(filename))
    {
        std::cerr << "File: \"" << fullFilename << "\" does not exist!" << std::endl;
        return;
    }

    

    std::filesystem::remove("employees/" + fullFilename);

    if (!fileExists(filename))
    {
        std::cout << "File deleted successfully!" << std::endl << std::endl;
        return;
    }
    else
    {
        std::cout << "Error deleting file." << std::endl << std::endl;
        return;
    }
}

static void showList()
{
    std::string path = "employees";
    for (const auto& entry : std::filesystem::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}

int main()
{
    std::string input;
    while (1)
    {
        std::cout << "--------------------------------------------------------" << std::endl << "Hello! Welcome to the (company) employee management system!" << std::endl <<
            "Type 1 and press enter to create a new employee" << std::endl <<
            "Type 2 and press enter to edit a new employee" << std::endl <<
            "Type 3 and press enter to delete an existing employee" << std::endl <<
            "Type 4 ans press enter to show list of employee files" << std::endl <<
            "Type \"exit\" to exit the program." << std::endl;
    start:
        std::cin >> input;

        if (input == "1")
        {
            createEmployee();
        }
        else if (input == "2")
        {
            editEmployee();
        }
        else if (input == "3")
        {
            deleteEmployee();
        }
        else if (input == "4")
        {
            showList();
        }
        else if (input == "exit")
            break;
        else
        {
            std::cout << "I don't understand." << std::endl;
            goto start;
        }
    }
    std::cout << "Thank you for using the employee management system! Goodbye!";
    return 0;
}