#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <math.h>

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

void read_data(string fn, int students, int exams)
{
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
        for (int student_id : exam_students[i])
        {
             cout << student_id << " ";
        }
         cout << endl;
    }

    // adjacency matrix
    cout << "Adjacency Matrix" << endl;
    int *adj_matrix = new int[exams * exams];
    for (int i = 0; i < exams; i++)
    {
        for (int j = 0; j < exams; j++)
        {
            if (i == j)
            {
                adj_matrix[i * exams + j] = 0; // adj_matrix[i][j]
                continue;
            }
            int c = count_common_elements(exam_students[i + 1], exam_students[j + 1]);
            if (c > 0)
            {
                cout << i + 1 << " " << j + 1 << " " << c << endl;
            }
            adj_matrix[i * exams + j] = c;
        }
    }

    // density
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
    cout << "Vertices : "<< exams << endl;

    double cd = double(c) / double(exams * exams);
    cout << "Conflict Density: " << cd << endl;

    //max
    int max = 0;
    for (int i = 0; i < exams; i++)
    {
        int d = 0;
        for (int j = 0; j < exams; j++)
        {
            if (adj_matrix[i * exams + j] > 0)
            {
                d++;
            }
        }
        if (d > max)
        {
            max = d;
        }
    }
    cout << "Degree Max: " << max << endl;

    //min
    int min = max;
    for (int i = 0; i < exams; i++)
    {
        int m = 0;
        for (int j = 0; j < exams; j++)
        {
            if (adj_matrix[i * exams + j] > 0)
            {
                m++;
            }
        }
        if (m < min)
        {
            min = m;
        }
    }

    cout << "Degree Min: " << min << endl;


   //median
    	int med=0;
    	int sorted[exams];
    	int conflictSum = 0;
    	for (int i = 0; i < exams; i++)
    	 {
    	  int c=0;
    	  for (int j = 0; j < exams; j++)
    	  {
    	   if (adj_matrix[i * exams + j] > 0)
    	   {
    	    c++;
    	    conflictSum++;
    	   }
    	  }
    	   sorted[i] = c;
    	 }

    	int nsize = sizeof(sorted) / sizeof(sorted[0]);
    	sort(sorted, sorted+nsize);
    	med = sorted[exams/2 + (exams % 2 == 0 ? 0 : 1)];

    	cout << "Median : "<< med << endl;


    //mean

    	   double mean= double (conflictSum) / double (exams);

    	   cout << "Mean : "<< mean << endl;

    //coefficient variance

    	    double calc = 0.0;
    	    for (int i = 0; i < exams; i++)
            {
    	     int c =0;
             for (int j = 0; j < exams; j++)
    	     {
				  if (adj_matrix[i * exams + j] > 0)
				  {
				   c++;
				  }
    	     }
             calc += pow((c - mean),2);
    	    }
    	    calc = calc / double(exams);
    	    double cv = (sqrt(calc) / mean)* 100;
    	    cout << "cv : "<< cv << endl;
}

int main()
{
    //read_data("car-f-92.stu", 18419, 543);
    read_data("hec-s-92.stu", 2823, 81);
    return 1;
}
