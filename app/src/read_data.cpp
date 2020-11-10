// ανάγνωση δεδομένων από ένα αρχείο προβλήματος (με κατάληξη stu) που περιέχει
// πληροφορίες για τις εξετάσεις μαθημάτων στις οποίες είναι εγγεγραμμένος
// ο κάθε σπουδαστής

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int count_common_elements(set<int> s1, set<int> s2)
{
    int c = 0;
    for (int x : s1)
    {
        for (int y : s2)
        {
            if (x == y)
            {
                c++;
                break;
            }
        }
    }
    return c;
}

float read_data(string fn, int students, int exams, float a)
{
    // ανάγνωση δεδομένων
    vector<set<int>> exam_students(exams + 1);
    fstream fs(fn);
    if (!fs.is_open())
    {
        cerr << "Could not open file " << fn << std::endl;
        exit(-1);
    }
    int student_id = 0;
    string line;
    while (getline(fs, line))
    {
        if (line.empty())
            continue;
        student_id++;
        istringstream iss(line);
        int exam_id;
        while (iss >> exam_id)
        {
            exam_students[exam_id].insert(student_id);
            cout << "Student " << student_id << " is enrolled in exam " << exam_id << endl;
        }
    }
    fs.close();

    cout << "#################################" << endl;

    for (int i = 1; i <= exams; i++)
    {
        cout << "Exam " << i << " Enrolled students: ";
        for (int student_id : exam_students[i]) // range based for
        {
            cout << student_id << " ";
        }
        cout << endl;
    }

    // δημιουργία πίνακα γειτνίασης
    cout << "Adjacency Matrix" << endl;
    int *adj_matrix = new int[exams * exams];
    for (int i = 0; i < exams; i++)
    {
        for (int j = 0; j < exams; j++)
        {
            if (i == j){
                adj_matrix[i * exams + j] = 0; // adj_matrix[i][j]
                continue;
            }
            int c = count_common_elements(exam_students[i + 1], exam_students[j + 1]);
            if (c > 0)
                cout << i + 1 << " " << j + 1 << " " << c << endl;
            adj_matrix[i * exams + j] = c;
        }
    }

    // Υπολογισμός συντελεστή πυκνότητας
    int c = 0;
    for (int i = 0; i < exams; i++)
    {
        for (int j = 0; j < exams; j++)
        {
            if (adj_matrix[i * exams + j] > 0)
            {
                c++;
            }
        }
    }

    double cd = double(c) / double(exams * exams);
    cout << "Conflict Density: " << cd << endl;

    delete[] adj_matrix;
    return cd;
}

int main()
{
    //    read_data("../datasets/car-f-92.stu", 18419, 543);
    // read_data("../datasets/toy_e5_s6.stu", 6, 5);
      double TABLE[13] = {0};
    //TABLE[0]=read_data("../datasets/toy_e5_s6.stu", 6, 5,TABLE[0]);
    TABLE[0] = read_data("../datasets/car-f-92.stu", 18419, 543, TABLE[0]);
    TABLE[1] = read_data("../datasets/car-s-91.stu", 16925, 682, TABLE[1]);
    TABLE[2] = read_data("../datasets/ear-f-83.stu", 1125, 190, TABLE[2]);
    TABLE[3] = read_data("../datasets/hec-s-92.stu", 2823, 81, TABLE[3]);
    TABLE[4] = read_data("../datasets/kfu-s-93.stu", 5349, 461, TABLE[4]);
    TABLE[5] = read_data("../datasets/lse-f-91.stu", 2726, 381, TABLE[5]);
    TABLE[6] = read_data("../datasets/pur-s-93.stu", 30029, 2419, TABLE[6]);
    TABLE[7] = read_data("../datasets/rye-s-93.stu", 11483, 486, TABLE[7]);
    TABLE[8] = read_data("../datasets/sta-f-83.stu", 611, 139, TABLE[8]);
    TABLE[9] = read_data("../datasets/tre-s-92.stu", 4360, 261, TABLE[9]);
    TABLE[10] = read_data("../datasets/uta-s-92.stu", 21266, 622, TABLE[10]);
    TABLE[11] = read_data("../datasets/ute-s-92.stu", 2749, 184, TABLE[11]);
    TABLE[12] = read_data("../datasets/yor-f-83.stu", 941, 181, TABLE[12]);
    for (int i = 0; 12 >= i; i++)
    {
        cout << "Conflict Density: " << TABLE[i] << endl;
    }
}

/*
Student 1 is enrolled in exam 1
Student 1 is enrolled in exam 2
Student 2 is enrolled in exam 3
Student 2 is enrolled in exam 4
Student 2 is enrolled in exam 5
Student 3 is enrolled in exam 3
Student 3 is enrolled in exam 5
Student 4 is enrolled in exam 2
Student 5 is enrolled in exam 1
Student 5 is enrolled in exam 3
Student 6 is enrolled in exam 3
Student 6 is enrolled in exam 5
#################################
Exam 1 Enrolled students: 1 5
Exam 2 Enrolled students: 1 4
Exam 3 Enrolled students: 2 3 5 6
Exam 4 Enrolled students: 2
Exam 5 Enrolled students: 2 3 6
1 2 1
1 3 1
2 1 1
3 1 1
3 4 1
3 5 3
4 3 1
4 5 1
5 3 3
5 4 1
Conflict Density: 0.4
*/