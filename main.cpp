#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<limits>

// Class to represent a Student
class Student {
private:
    int id;
    std::string name;
    std::string course;

public:
    // Constructor
    Student(int i, std::string n, std::string c) : id(i), name(n), course(c) {}

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCourse() const { return course; }

    // Setters
    void setName(const std::string& n) { name = n; }
    void setCourse(const std::string& c) { course = c; }
};

// Class to manage the SMS
class StudentManagementSystem {
private:
    std::vector<Student> students;
    const std::string filename = "students.txt";

    // Save student data to a file
    void saveToFile() {
        std::ofstream file(filename);
        for (const auto& student : students) {
            file << student.getId() << "," << student.getName() << "," << student.getCourse() << "\n";
        }
        file.close();
    }

    // Load student data from a file
    void loadFromFile() {
        students.clear();
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            int id;
            std::string name, course;
            size_t pos;
            int i = 0;

            while ((pos = line.find(",")) != std::string::npos) {
                if (i == 0) id = std::stoi(line.substr(0, pos));
                else if (i == 1) name = line.substr(0, pos);
                line.erase(0, pos + 1);
                i++;
            }// https://github.com/3BThakuri/SMS
            course = line;
            students.emplace_back(id, name, course);
        }
        file.close();
    }

    // Check if a student with a given ID exists
    bool studentExists(int id) const {
        for (const auto& student : students) {
            if (student.getId() == id) {
                return true;
            }
        }
        return false;
    }

public:
    // Constructor to initialize and load data
    StudentManagementSystem() {
        loadFromFile();
    }

    // Add a new student
    void addStudent() {
        int id;
        std::string name, course;

        std::cout << "Enter student ID: ";
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (studentExists(id)) {
            std::cout << "\n That a student with the same ID is already in the system. (You can't add a new student with the same ID)\n";
            return;
        }

        std::cout << "Enter student name: ";
        std::getline(std::cin, name);
        std::cout << "Enter student course: ";
        std::getline(std::cin, course);

        students.emplace_back(id, name, course);
        saveToFile();
        std::cout << "\nGreat! The student has been added.\n";
    }

    // Display all students
    void viewStudents() const {
        if (students.empty()) {
            std::cout << "\nThere are no students in the system yet.\n";
            return;
        }
        std::cout << "\nHere are all the students:\n";
        for (const auto& student : students) {
            std::cout << "ID: " << student.getId()
                      << ", Name: " << student.getName()
                      << ", Course: " << student.getCourse() << "\n";
        }
    }

    // Search for a student by ID
    Student* searchStudentById(int id) {
        for (auto& student : students) {
            if (student.getId() == id) {
                return &student;
            }
        }
        return nullptr;
    }

    // Update student details
    void updateStudent() {
        int id;
        std::cout << "\nEnter the ID of the student you want to update: ";
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Student* student = searchStudentById(id);
        if (!student) {
            std::cout << "\nSorry, no student found with that ID.\n";
            return;
        }

        std::string name, course;
        std::cout << "\nDo you want to change the name? Enter a new Name or press Enter to skip: ";
        std::getline(std::cin, name);
        if (!name.empty()) student->setName(name);

        std::cout << "\nDo you want to change the course? Enter a new Course or press Enter to skip: ";
        std::getline(std::cin, course);
        if (!course.empty()) student->setCourse(course);

        saveToFile();
        std::cout << "\nThe student has been updated!\n";
    }

    // Delete a student
    void deleteStudent() {
        int id;
        std::cout << "\nEnter the ID of the student you want to delete: ";
        std::cin >> id;
            // https://github.com/3BThakuri/SMS
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getId() == id) {
                students.erase(it);
                saveToFile();
                std::cout << "\nThe student has been deleted.\n";
                return;
            }
        }
        std::cout << "\nSorry, no student found with that ID.\n";
    }
};

// Main function
int main() {
    StudentManagementSystem sms;
    int choice;

    do {
        std::cout << "\nStudent Management System\n";
        std::cout << "1. Add a New Student\n";
        std::cout << "2. View All Students\n";
        std::cout << "3. Update a Student\n";
        std::cout << "4. Delete a Student\n";
        std::cout << "5. Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.viewStudents();
                break;
            case 3:
                sms.updateStudent();
                break;
            case 4:
                sms.deleteStudent();
                break;
            case 5:
                std::cout << "\nGoodbye! See you next time.\n";
                break;
            default:
                std::cout << "\nThat is not a valid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}











// https://github.com/3BThakuri/SMS
