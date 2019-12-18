#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;


map<string, string> encode(string s){
    map <string, string> snipet;
    string prefix;
    string body;
    for(int i = 0; i < s.size() - 50; i++) {
        if(s.substr(i, 8) == "\"prefix\"") {
            prefix = "";
            body = "";
            i += 8;
            while(s[i] != '\"') i++;
            i++;

            while(s[i] != '\"') {
                prefix += s[i];
                i++;
            }
            while(s[i] != '[') i++;
            i++;
            while(s.substr(i,13) != "\"description\"") {
                body += s[i];
                i++;
                if(i + 14 >= s.size())break;
            }
            body = body.substr(0, body.size() - 9);
            for(int j = 0; j < body.size(); j++) {
                if(body[j] == '\t'){
                    body.erase(j, 1);
                    j--;
                }
            }
            for(int j = 0; j < body.size()-4; j++) {
                if(body.substr(j, 4) == "    "){
                    body.erase(j, 4);
                    j--;
                }
            }
            for(int j = 0; j < body.size() - 1; j++) {
                if(body.substr(j, 2) == "$1" || body.substr(j, 2) == "$2") {
                    body.erase(j, 2);
                    j--;
                }
            }
            
            for(int j = 0; j < body.size(); j++) {//body整形
                
                if(body[j] == '\"') {
                    if(j == 0 || body[j - 1] != '\\') {
                        body.erase(j, 1);
                        j--;
                    }
                    if(body[j + 1] == ',') {
                        body.erase(j + 1, 1);
                        j--;
                    }
                }
                if(j < body.size() - 1 && body[j] == '\\' && body[j + 1] == 't') {
                    body[j] = ' ';
                    body[j + 1] = ' ';
                }
            }
            for(int j = 0; j < prefix.size(); j++) {
                if(prefix[j] == '_') {
                    prefix.erase(j, 1);
                }
            }
            snipet[prefix] = body;
        }
    }
    return snipet;
}
int main(void){
    char InitFile[] = "init.txt";//初期化ファイル(init file)
    char InputFile[] = "snippet.json";//スニペットが入っているファイル(snippet file)
    char OutputFile[] = "snippet.tex";//出力ファイル(output file)
    string init_str = "";
    string input_str = "";
    
    char c;

    FILE *fp;
    fp = fopen(InitFile, "r");//初期化ファイル入力
    while((c = fgetc(fp)) != EOF) {
        init_str+=c;
    }
    fclose(fp);
    fp = fopen(InputFile, "r"); //スニペット入力
    while((c = fgetc(fp)) != EOF) {
        input_str+=c;
    }
    fclose(fp);

    ofstream writing_file; //初期化ファイル出力
    writing_file.open(OutputFile, ios::out);
    writing_file << init_str<<endl<<endl;
    cout << "ファイルへの出力が完了しました" << endl;

    map<string, string> snipet;
    map<string, string>::iterator it;
    snipet = encode(input_str);
    
    for(it = snipet.begin(); it != snipet.end(); it++) {
        writing_file << "\\color{white}" << endl;
        writing_file << "\\section{" << it->first << "}" << endl;
        writing_file << "\\color{black}" << endl;
        writing_file << "\\begin{lstlisting}[caption=" << it->first << "]" << endl;
        writing_file << it->second<<endl << endl;
        writing_file << "\\end{lstlisting}" << endl << endl;
        // writing_file << "\\vspace{30pt}" << endl << endl;
    }
    writing_file << "\\end{document}" << endl;

}
