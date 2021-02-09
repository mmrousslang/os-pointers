// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
int allNums(std::string checkString);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Sequence of user input -> store in fields of `student`
    student.f_name = new char[128];

    double temp = -1;
    while(temp == -1){
        std::string message = "Please enter the student's id number: ";
        temp = promptInt(message, 0, 999999999);
    }
    student.id = temp;
    temp = -1;

    //prompt for first and last name
    student.f_name = new char[128];
    student.l_name = new char[128];
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;

    //prompt for number of assignments
    while(temp == -1){
        std::string message = "Please enter how many assignments were graded: ";
        temp = promptInt(message, 1, 134217728);
    }
    student.n_assignments = temp;
    std::cout << "\n";

    //call promptDouble for each assignment
    for(int i = 0; i < student.n_assignments; i++){
        temp = -1;
        while(temp == -1){
            std::string message = "Please enter grade for assignment " + std::to_string(i) + ": ";
            temp = promptDouble(message, 0.0, 1000.0);
        }
        student.grades[i] = temp;
    }

    std::cout << "\nStudent: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n";

    average = student.n_assignments;
    calculateStudentAverage(student.grades, &average);
    std::cout << "  Average grade: "<< average<<"\n";

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    std::string id;
    int idNum = 0;
    std::cout << message;
    std::cin >> id;


    if(allNums(id) != 1)  { 
        std::cout << "Sorry, I cannot understand your answer\n";
        return -1;
    }else {
        idNum = std::stoi(id);
        if(idNum < min || idNum > max){
            std::cout << "Sorry, I cannot understand your answer\n";
            return -1;
        }
        return idNum;
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double (grades)
    std::string grade;
    double gradeNum = 0;
    std::cout << message;
    std::cin >> grade;

    if(allNums(grade) == -1)  { 
        std::cout << "Sorry, I cannot understand your answer\n";
        return -1;
    }else {
        gradeNum = std::stod(grade);
        if(gradeNum < min || gradeNum > max){
            std::cout << "Sorry, I cannot understand your answer\n";
            return -1;
        }
        return gradeNum;
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    double *grades = (double*)object;
    double tempAvg = 0.0;

    for(int i = 0; i < *avg; i++){
        tempAvg += grades[i];
    }
    tempAvg = (tempAvg / *avg);
    tempAvg = (int)(tempAvg * 10 + .5);
    tempAvg = (double)(tempAvg / 10);
    
    *avg = tempAvg;
}

/*
    checkString: text to check if it is all numbers
    returns 1 if checkString is an int, 2 if it is a double and -1 otherwise
*/
int allNums(std::string checkString)
{
    int containsDot = 0;
    char dot = '.';

    for(int i = 0; i < checkString.length(); i++){
        if(isdigit(checkString[i]) == false){
            if(checkString[i] == dot){
                containsDot++;
            }else {
                return -1; //string contains non int chars
            }
        }
    }

    if(containsDot == 0){ //string is an int
        return 1;
    }else if(containsDot == 1){
        return 2;
    }else {
        return -1;
    }
}