#include <bits/stdc++.h>
using namespace std;

vector<string> includePaths;

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

string slove(string currentFile, size_t loop = 0)
{
	ifstream ifs(currentFile);
	if (loop > 100)
		exit(10);
	string res = "";
	int row = 1;
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
				string load;
				if (filesystem::is_regular_file(file))
				{
					load = file;
				}
				else
				{
					bool accepted = false;
					for (string path : includePaths)
					{
						filesystem::path include(path);
						include.append(file);
						if (filesystem::is_regular_file(include))
						{
							load = include;
							accepted = true;
							break;
						}
					}
					if (!accepted)
					{
						cerr << "Error: Cannnot Find File: " << file << endl;
						cerr << "At " << currentFile << ":" << row << endl;
						exit(11);
					}
				}
				res += slove(load, loop + 1);
			}
			else
			{
				res += line;
			}
			res += '\n';
		}
		row++;
	}
	return res;
}

int main(int args, char **argv)
{
	if (args < 3)
	{
		cout << "ファイルを入力してください。";
		return 1;
	}
	if (args != 3)
	{
		for (int i = 3; i < args; i++)
		{
			includePaths.push_back(string(argv[i]));
		}
	}
	string s = slove(argv[1]);
	ofstream ofs(argv[2]);
	ofs << s;
}
