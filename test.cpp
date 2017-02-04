#include"term_pkg_parser.h"
#include<iostream>
using namespace std;

int main()
{
	term_pkg_parser tpp;

	term_cmd tc;
	char buff[]="if_browser  ls    C:\\ ";

	tc=tpp.do_parse(buff);

	cout<<tc.cmd<<" "<<tc.para<<" "<<tc.args<<endl;
	return 0;
}
