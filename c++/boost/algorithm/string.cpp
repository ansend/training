#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace boost::algorithm; // for boost::algorithm::is_any_of();


int main (int argc, char** argv)
{
	std::string tmp1 = "hello,dongtiecheng";
	std::string tmp2 = " hello ,zhangranran  ";
        std::string tmp3 = "kuokuo ";
        std::string tmp4 = " ";

	std::vector<std::string> array;
	boost::trim(tmp4);
	if(tmp4.empty())
	{
		cout << "it's a empty string" << endl;
	}
	string str("miss,you.just.call_to,say,I~love~you");
	vector<string> strVec;
	boost::split(strVec, str, is_any_of(".,"));
    cout << strVec.size() << endl;
	vector<string>::iterator it = strVec.begin();
	for (; it!=strVec.end(); it++){
           cout << "any" << endl;
	   cout << *it << endl;
	}
	return 0;

}

