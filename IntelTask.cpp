#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

template <typename Type>

class Circle{

protected:
	string id;
	Type x, y, r;
public:
	Circle(string id = "0", Type x = 0.0, Type y = 0.0, Type r = 0.0) :
		id(id),x(x), y(y), r(r) {
	}

	Circle(const Circle& circle):
		id(circle.id),
		x(circle.x),
		y(circle.y),
		r(circle.r)
	{
	}

	~Circle() {

	}

	bool is_intersected(const Circle& circle) {
		return pow(x - circle.x, 2) + pow(y - circle.y, 2) < pow(r + circle.r, 2);
	}

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

template <typename Type>

ostream& operator<< (ostream& stream, Circle<Type> circle) {
	stream << "Circle #" <<circle.get_id()<< endl;
		stream << "Center " << circle.get_x() << ";" << circle.get_y()<<endl;
		stream << "Radius is "<<circle.get_r()<<endl;
		return stream;
	}

template <typename Type>

bool operator< (Circle<Type>& c1, Circle<Type>& c2)
	{
		return c1.get_r() < c2.get_r();
	}

template <typename Type>

int find_max(vector<Circle<Type>> v) {
	for (unsigned int i = v.size() - 1; i > 0; i--) {
		for (unsigned int j = i - 1; j >= 0; j--) {
			if (v.at(i).is_intersected(v.at(j))) 
				break;
			if (j == 0) 
				return j;;
		}
	}
	return -1;
}



int main()
{
	ifstream file;

	file.open("input.txt");
	if (file || !file.fail()) { // is file open correctly
		vector <Circle<double>> v;
		while (!file.eof()) {
			string s;
			vector <double> st;
			getline(file, s, ','); //id
			string id = s;
			getline(file, s, ',');//x
			st.push_back(atof(s.c_str()));
			getline(file, s, ',');//y
			st.push_back(atof(s.c_str()));
			getline(file, s);//r
			st.push_back(atof(s.c_str()));
			v.push_back(Circle<double>(id, st.at(0), st.at(1), st.at(2)));
		}
		sort(v.begin(), v.end());
		int number = find_max(v);
		cout << v.at(number);

	}
	if (file.is_open()) file.close();

}
