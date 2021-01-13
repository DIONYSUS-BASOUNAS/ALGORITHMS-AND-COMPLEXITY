#include "GraphColoring.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

void selectAlgorithm(Graph* g) {
    cout << "1) First Fit" << endl;
    cout << "2) DSatur" << endl;
    cout << "3) RLF" << endl;
    cout << "4) Backtracking DSatur" << endl;
    int option;
    cin >> option;
    
    switch (option)
    {
    case 1:
        g -> greedyColoring();
        break;
    
    case 2:
        g -> DSatur();
        break;

    default:
        exit(-1);
        break;
    }

}

void readData(string fn, int exams) {
    vector<set<int>> examStudents(exams+1);
    Graph* graph = new Graph(exams,fn);
    fstream fs(fn);
    if (!fs.is_open()){
        cerr<<"could not open file:"<<fn << endl;
        exit(-1);
    }
    int studentId=0;
    string line;
    while(getline(fs,line)){
        if (line.empty())
        continue;
        studentId++;
        istringstream iss(line);
        int examId;
        while(iss>>examId){
            examStudents[examId].insert(studentId);
            cout <<"student"<<studentId<<"is enrolled is exam"<<examId<<endl;

        }
    }
    fs.close();
    cout<<"######################"<<endl;
    for (int i=1;i<=exams; i++){
cout <<"Exam"<<i<<"Enrolled students:";
for (int studentsId:examStudents[i])
cout<<studentsId<<"";
cout<< endl;
    }
    cout <<endl;
    graph ->initaiLizedAdj_Martix(examStudents);
    graph -> conflictDensity();
    graph -> stats();
    graph -> degMean();
    graph -> coefVar();
    cout <<graph->toString()<<endl;
    selectAlgorithm(graph);

    delete graph;
}
void selectFile() {
    //Problems
    string datasets[14] = {
        "../datasets/car-f-92.stu", //0
        "../datasets/car-s-91.stu", //1
        "../datasets/ear-f-83.stu", //2
        "../datasets/hec-s-92.stu", //3
        "../datasets/kfu-s-93.stu", //4
        "../datasets/lse-f-91.stu", //5
        "../datasets/pur-s-93.stu", //6
        "../datasets/rye-s-93.stu", //7
        "../datasets/sta-f-83.stu", //8
        "../datasets/tre-s-92.stu", //9
        "../datasets/uta-s-92.stu", //10
        "../datasets/ute-s-92.stu", //11
        "../datasets/yor-f-83.stu", //12
        "../datasets/toy_e5_s6.stu", //13 no toronto data, created for tests
    };
    int exams[14] = {543, 682, 190, 81, 461, 381, 2419, 486, 139, 261, 622, 184, 181, 5};
    
    int option;

    for (int i = 0; i < 14; i++) 
        cout << i + 1  << ") " << datasets[i].substr(12, 8) << endl;  

    cin >> option;
    option--;

    if (option < 0 || option > 13)
        exit(-1);
    readData(datasets[option], exams[option]);    
}

void selectMenuOption(int option) {
    
    Graph g;

    switch (option) {
    case 1:
        g.printStatisticArray();
        break;

    case 2:
        selectFile();
        break;

    default:
        exit(-1);
        break;
    }
}

void executeMenu() {
    

    int option;

    cout << "1) Print Statistics Array" << endl;
    cout << "2) Read Data from file" << endl;
    cout << "Or Press any key to exit" << endl;
    cin >> option;

    selectMenuOption(option);
}

int main() {

    executeMenu();

    return 0;
}