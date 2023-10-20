// David Hughes
// 10/15/2023
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Define the Course class with appropriate constructors and members
class Course {
public:
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;

    Course(std::string cNumber, std::string cName) : courseNumber(cNumber), courseName(cName) {}
    ~Course() {}
};

// Define a BSTNode to help with the binary search tree implementation
class BSTNode {
public:
    Course* course;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Course* c) : course(c), left(nullptr), right(nullptr) {}
    ~BSTNode() {
        delete course;
        delete left;
        delete right;
    }
};

// Define the CourseBST class to manage courses in a binary search tree format
class CourseBST {
private:
    BSTNode* root;

    void insert(BSTNode*& node, Course* course) {
        if (!node) {
            node = new BSTNode(course);
            return;
        }
        if (course->courseNumber < node->course->courseNumber) {
            insert(node->left, course);
        }
        else {
            insert(node->right, course);
        }
    }

    void printInOrder(BSTNode* node) const {
        if (!node) return;
        printInOrder(node->left);
        std::cout << node->course->courseNumber << ", " << node->course->courseName << std::endl;
        printInOrder(node->right);
    }

    BSTNode* find(BSTNode* node, const std::string& courseNumber) const {
        if (!node) return nullptr;
        if (courseNumber == node->course->courseNumber) return node;
        else if (courseNumber < node->course->courseNumber) return find(node->left, courseNumber);
        else return find(node->right, courseNumber);
    }

public:
    CourseBST() : root(nullptr) {}
    ~CourseBST() { delete root; }

    void insert(Course* course) {
        insert(root, course);
    }

    void printInOrder() const {
        printInOrder(root);
    }

    Course* find(const std::string& courseNumber) const {
        BSTNode* node = find(root, courseNumber);
        if (node) return node->course;
        return nullptr;
    }
};

int main() {
    CourseBST courses;
    std::string filename;
    while (true) {
        // Menu
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter filename: ";
            std::cin >> filename;
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open the file." << std::endl;
                break;
            }
            std::string line;
            while (getline(file, line)) {
                std::istringstream ss(line);
                std::string courseNumber, courseName, prerequisite;
                getline(ss, courseNumber, ',');
                getline(ss, courseName, ',');
                Course* course = new Course(courseNumber, courseName);
                while (getline(ss, prerequisite, ',')) {
                    course->prerequisites.push_back(prerequisite);
                }
                courses.insert(course);
            }
            std::cout << "Data loaded successfully." << std::endl;
            break;
        }
        case 2:
            courses.printInOrder();
            break;
        case 3: {
            std::cout << "Enter course number: ";
            std::string courseNum;
            std::cin >> courseNum;
            Course* course = courses.find(courseNum);
            if (course) {
                std::cout << course->courseNumber << ", " << course->courseName << std::endl;
                std::cout << "Prerequisites: ";
                for (const auto& prereq : course->prerequisites) {
                    std::cout << prereq << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "Course not found!" << std::endl;
            }
            break;
        }
        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}
