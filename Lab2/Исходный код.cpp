#include "Lab2.h"
using namespace std;

template <typename T> void PrintVector(vector<T> v){
    unsigned int i;
    for (i = 0; i < v.size(); ++i){
       cout << v[i] <<", ";
    }
}

int main(int argc, char *argv[])
{
    char filename[] = "../arr.txt";
    string s = read_file(filename);
	string s1 = ReadFromFile(filename);
    cout << "In fopen_s: "<< s << endl;
	cout << "In fstream: "<<s1 << endl;
    /*s = str_clean(s);
    cout << "Cleaned string:" << endl << s << endl;
    pretty_print(s, 40);*/

#ifdef _WIN32_C_LIB
    getchar();
#endif //WIN32

    return EXIT_SUCCESS;
}

string read_file(char * filename){
    FILE * f;

    char * f_buf;
    long int f_size;

	fopen_s(&f, filename, "r");
    if (f == NULL){
        cout << "fail open file "<< filename;
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    f_size = ftell(f);
    rewind(f);
    f_buf = (char *) malloc(f_size * sizeof(char));
    if (fread(f_buf, sizeof(char), f_size, f) != f_size){
        cout << "read file failure" << endl;
    }
    fclose(f);
    string content(f_buf, f_size);
    free(f_buf);
    return content;
}

string ReadFromFile(char *filename){
	ifstream data;
	data.open(filename);
	char *tmp;
	int tmp_size;

    if (data == NULL){
       cout << endl << "fail open file: " << filename << endl;
	   return NULL;
    }
    else{ 
		cout << endl << "file open succeful: " << filename << endl;
	}
	
	data.seekg(0,ios_base::end );
	tmp_size = data.tellg();
	data.seekg(0,ios_base::beg);
	cout << endl << "tmp_size = "<< tmp_size;

	tmp = (char*)malloc(tmp_size * sizeof(char));
	data.read(tmp, tmp_size);
	string str(tmp, tmp_size);
	free(tmp);
	data.close();
	return str;
}

string str_clean(string str){
    int pos;
    char * not_other_space_char[] = {"\a","\b","\n","\t","\v","\r","\f", "  "};
    char replace_word[] = "Vau!!!"; //bullshit

    for (int i=0; i < sizeof(not_other_space_char)/sizeof(not_other_space_char[0]); ++i){
        while( (pos = str.find(not_other_space_char[i])) != str.npos ){
            str.erase(pos,1);
        }
    }
    while ((pos = str.find(" ,")) != str.npos){
        str.erase(pos,1);
    }

    pos=0;
    while ((pos = str.find(",", pos+1 )) != str.npos){
        if(str.compare(pos+1, 1, " ") == 1){
            str.insert(pos+1, " ");
        }
    }

    // equal str.replace(QRegExp("[\\w]{10,}"), replace_word);
    int pre_pos = 0;
    int word_size = 0;
    int dot;
    bool _loop = true;

    while (_loop){
        pos = str.find(" ", pos+1 );
        if (pos ==  str.npos) {
            _loop = false;
            pos = str.length();
        }

        if( pos != 0){
            word_size = pos-1 - pre_pos;
            if ((str.compare(pos-1, 1, ",") == 0)||((dot=str.compare(pos-1, 1, ".")) == 0)){
                word_size--;
            }

            if (word_size > 10){
                if (dot == 0){
                    word_size++;
                }
                str.replace(pre_pos+1, word_size, replace_word);
            }

        }
        word_size = 0;
        pre_pos = pos;
    }

    //cout << str;
    return str;
}

void pretty_print(string str, int width){
    vector<string> str_v;
    unsigned int last_pos = 0;
    unsigned int max_pos = str.size();
    unsigned int end = 0;
    unsigned int offset = 0;
    unsigned int line_width;

    while (true){
        line_width = width;
        end = last_pos+line_width;

        if (!(last_pos+line_width >= max_pos)) {
            offset = str.rfind(" ", end);
            if (offset != str.npos){
                line_width = line_width - (end - offset);
            }
        }

        str_v.push_back(str.substr(last_pos + 1, line_width));
        last_pos = last_pos + line_width;
        if (last_pos >= max_pos){
            break;
        }

    }
    PrintVector<string>(str_v);

}