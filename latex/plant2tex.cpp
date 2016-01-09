#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <regex>
#include <bits/stl_list.h>

using namespace std;


struct method {
    bool isStatic;
    string visibility = "";
    string name;
    string args;
    string returns;
    bool isAbstract;
};

struct klass {
    vector<method> methods;
    string name;
    bool isAbstract;
};


void processcontent(queue<string> &);

void processclass(queue<string> &);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << argc << endl;
        return 1;
    }
    queue<string> lines;
    ifstream umlfile;
    umlfile.open(argv[1]);
    string tmp;
    while (umlfile) {
        getline(umlfile, tmp);
        lines.push(tmp);
    }
    umlfile.close();
    processcontent(lines);

    return 0;
}

void processcontent(queue<string> &q) {

    {
        string cur;
        while (!(q.empty())) {
            cur = (q.front());

            if (regex_match(cur.c_str(), regex("(abstract\\s+)?class(.)*\\{"))) {
                processclass(q);
                //      auto input = regex_replace(cur,regex("class|\\{"),"");

                //     cout << input;
            }
            q.pop();

        }
        return;
    }
}


void processclass(queue<string> &q) {

    klass newklass;
    string cur = q.front();
    newklass.name = regex_replace(cur, regex("class|\\{|abstract|(<<(.*)>>)"), "");
    newklass.name.erase(std::remove(newklass.name.begin(), newklass.name.end(), ' '), newklass.name.end());
    q.pop();
    cur = q.front();

    while (cur.compare("}")) {
        cur = q.front();
        cur = regex_replace(cur, regex("_"),"\\textunderscore");
        cur = regex_replace(cur, regex("&"),"\\&");
        
        if (regex_match(cur.c_str(), regex("\\s*(\\{(static|abstract)\\})?\\s*((\\+|\\#))(.*)\\((.*)\\)(.*)"))) {
            method newmeth;

            newmeth.isStatic = regex_match(cur.c_str(), regex("\\{static\\}"));
            newmeth.isAbstract = regex_match(cur.c_str(), regex("\\{abstract\\}"));

            string argbuff = regex_replace(cur.c_str(), regex("(.*\\()|(\\).*)"), "");

            newmeth.args = argbuff;
            newmeth.returns = regex_replace(cur.c_str(), regex(".*\\)"), "");
            newmeth.returns.erase(std::remove(newmeth.returns.begin(), newmeth.returns.end(), ':'),
                                  newmeth.returns.end());

            string nambuff = regex_replace(cur.c_str(), regex("\\s*\\s*(\\+)?(\\#)?"), "");
            nambuff = regex_replace(nambuff, regex("\\s*\\{abstract\\}\\s*|\\s*\\{static\\}"), "");
            newmeth.name = regex_replace(nambuff, regex("\\(.*"), "");
            newmeth.name.erase(std::remove(newmeth.name.begin(), newmeth.name.end(), ' '), newmeth.name.end());

            if (regex_search(cur.c_str(), regex("\\+"))) {
                newmeth.visibility.append("public");
            }

            if (regex_search(cur.c_str(), regex("\\#"))) {
                newmeth.visibility.append("protected");
            }
            newklass.methods.push_back(newmeth);
        }
        q.pop();
    }

    ofstream outfile;
    string filename = newklass.name; 
    filename.append(".tex");
    outfile.open(filename);
    cout << "\\input{./latex/"<<filename << "}"<< endl;
    outfile << "\\chapter{" << newklass.name << "}\n";
    outfile << "describe class " << newklass.name << " here\n";
    for (auto &m : newklass.methods) {
        outfile << "\\section{" << m.name << "}\n";
        outfile << "\\begin{longtable}{p{3cm} @{\\hskip 1cm} p{12cm}}\n \\hline\n";
        outfile << "\\textit{Name} & \\texttt{" << newklass.name << "::" << m.name << "(" << m.args << ")}\\\\\n";
        outfile << "\\hline\n " << "\\textit{Visibility} & " << m.visibility;
        if (m.isAbstract) { outfile << " abstract"; }
        if (m.isStatic) { outfile << " static"; }
        outfile << "\\\\" << endl << "\\hline\n\\textit{Parameters} & \\textit{" << m.args;
        if (m.args.length() == 0) { outfile << "none"; }
        outfile << "}\\\\" << endl << "\\hline\n\\textit{Return value} & \\textbf{" << m.returns;
        if (m.returns.length() == 0) { outfile << "none}\\\\\n"; } else {
            outfile << "} describe return value\\\\\n";}
            outfile << "  \\hline\n \\textit{behavior} & describe beahviour \\\\\n\\hline\n\\end{longtable} \\pagebreak\n ";
        }
    outfile.close();

    }


