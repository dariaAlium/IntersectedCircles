#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

//class that describes an abstract data type : a circle

template <typename Type>

class Circle{

protected:
	string id; //the number of every circle in the output file
	Type x, y, r; // (x,y) and radius
public:
	//defult constructor
	Circle(string id = "0", Type x = 0.0, Type y = 0.0, Type r = 0.0) :
		id(id),x(x), y(y), r(r) {
	}
	
	//copy constructor
	Circle(const Circle& circle):
		id(circle.id),
		x(circle.x),
		y(circle.y),
		r(circle.r)
	{
	}

	//destructor
	
	~Circle() {

	}

	//intersected cheсk 

	bool is_intersected(const Circle& circle) {
		return pow(x - circle.x, 2) + pow(y - circle.y, 2) < pow(r + circle.r, 2);
	}

	//getters

	Type get_r() {
		return r;
	}

	Type get_x() {
		return x;
	}
	
	Type get_y() {
		return y;
	}

	string get_id() {
		return id;
	}
	

};

//visualization

template <typename Type>

ostream& operator<< (ostream& stream, Circle<Type> circle) {
	stream << "Circle #" <<circle.get_id()<< endl;
		stream << "Center " << circle.get_x() << " ; " << circle.get_y()<<endl;
		stream << "Radius is "<<circle.get_r()<<endl;
		return stream;
	}

//for sort function (sorting by radius)

template <typename Type>

bool operator< (Circle<Type>& c1, Circle<Type>& c2)
	{
		return c1.get_r() < c2.get_r();
	}

// searching the biggest circle

template <typename Type>

int find_max(vector<Circle<Type>> v) {
	
	set<int> s; //the set of index of intersected circles
	s.insert(-1); // not empty set
	
	for (unsigned int i = 0; i < v.size(); i++) {
		
		if(s.find(i) != s.end()) continue; // if i circle is already intersected
		
		for (unsigned int j = 1; j < v.size(); j++) { // we do not begin with j = i + 1 as there are many events, when it is wrong 
			
			if (s.find(j) != s.end() || i == j) continue; // if j circle is already intersected or i = j
			
			if (v.at(i).is_intersected(v.at(j))) { // if i and j circles intersect
				
				s.insert(i); // add index to set
				s.insert(j);
				
				break; //close inner cycle
			}

			if (j == v.size() - 1) //if we check all circles
				return i;
		}
	}
	return -1; //if all circles are intersected
}

//read file and full the vector

template <typename Type>

vector <Circle<Type>> full_the_vector(vector <Circle<Type>> v) {
	
	ifstream file;
	file.open("input.txt");
	
	if (file || !file.fail()) { // is file open correctly
		
		while (!file.eof()) {
			string id;
			getline(file, id, ','); //id
			
			string s;
			vector <Type> st;
			
			getline(file, s, ',');//x
			st.push_back(atof(s.c_str()));
			
			getline(file, s, ',');//y
			st.push_back(atof(s.c_str()));
			
			getline(file, s);//r
			st.push_back(atof(s.c_str()));
			
			v.push_back(Circle<Type>(id, st.at(0), st.at(1), st.at(2)));
		}

		sort(v.begin(), v.end()); //sort by radius
		
		reverse(v.begin(), v.end()); //ascending
		
	}
	if (file.is_open()) file.close();
	
	return v;
}

int main()
{
	vector <Circle<double>> v = full_the_vector(v);
	
	try {
		int number = find_max(v); //find the biggest
		cout << v.at(number);
	}
	catch (out_of_range&) {
		cout << "There are no such circle";
	}
		return 0;
}
