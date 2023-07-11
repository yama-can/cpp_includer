#include <bits/stdc++.h>
using namespace std;

string getFile(ifstream &ifs)
{
	string res = "";
	while (!ifs.eof())
	{
		string line;
		getline(ifs, line);
		res += line;
	}
	return res;
}

string slove(ifstream &ifs, size_t loop = 0)
{
	if (loop > 100)
		exit(10);
	string res = "";
	while (!ifs.eof())
	{
		string line;
		getline(ifs, line);
		stringstream ss(line);
		if (!ss.eof())
		{
			string f;
			ss >> f;
			string file;
			bool isFile = false;
			if (f == "#" && !ss.eof())
			{
				string p = "";
				ss >> p;
				f += p;
				if (!ss.eof())
				{
					ss >> p;
					if (p[0] == '"')
					{
						file = p.substr(1, p.length() - 2);
						isFile = true;
					}
				}
			}
			else if (f == "#include" && !ss.eof())
			{
				string p = "";
				ss >> p;
				if (p[0] == '"')
				{
					file = p.substr(1, p.length() - 2);
					isFile = true;
				}
			}
			if (isFile)
			{
				ifstream load(file);
				res += slove(load, loop + 1);
			}
			else
			{
				res += line;
			}
			res += '\n';
		}
	}
	return res;
}

int main(int args, char **argv)
{
	if (args != 3)
	{
		cout << "ファイルを入力してください。";
		return 1;
	}
	ifstream ifs(argv[1]);
	string s = slove(ifs);
	ofstream ofs(argv[2]);
	ofs << s;
}
