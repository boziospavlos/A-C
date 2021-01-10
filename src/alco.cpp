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
				adj_matrix[i * exams + j] = 0;
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

	//number of vertices

	cout << "Vertices : "<< exams << endl;

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
	cout << "Degree Max : " << max << endl;

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

	cout << "Degree Min : " << min << endl;

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
	cout << "Coefficient Variance : "<< cv << endl;

	// coloring with first fit

	int Vercolor[exams];
	int colorCount = 0;

	for (int i = 0; i < exams; i ++)
	{
		Vercolor[i] = 0;
	}

	for (int i = 0; i < exams; i ++)
	{
		int curColor = 1;

		while(Vercolor[i] == 0)
		{
			bool is_Color_Adjc = false;
			for (int j = 0; j < exams; j ++)
			{
				if (count_common_elements(exam_students[i+1], exam_students[j+1]) > 0 && i != j)
				{
					if(Vercolor[j] == curColor)
						is_Color_Adjc = true;
				}
			}
			if (is_Color_Adjc)
				curColor++;
			else
			{
				Vercolor[i] = curColor;
				if (curColor > colorCount)
					colorCount = curColor;
			}
		}
	}
	cout << "Colors Used : " << colorCount << endl;
}

int main()
{
	read_data("hec-s-92.stu", 2823, 81);
	read_data("sta-f-83.stu",611,139);
	read_data("yor-f-83.stu",941,181);
	read_data("ute-s-92.stu",2750,184);
	read_data("ear-f-83.stu",1125,190);
	read_data("tre-s-92.stu",4362,261);
	read_data("lse-f-91.stu",2726,381);
	read_data("kfu-s-93.stu",5349,461);
	read_data("ruy-s-93.stu",11483,486);
	read_data("car-f-92.stu",18419,543);
	read_data("uta-s-92.stu",21266,622);
	read_data("car-s-91.stu",16926,682);
	read_data("pur-s-93.stu",30032,2419);

	return 1;
}
