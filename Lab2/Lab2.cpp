#include "Lab2.h"
using namespace std;



int main(int argc, char *argv[]){
    char filename[] = "../arr.txt";
	string s = ReadFromFile(filename);
	cout << "Initial data: "<< endl <<s << endl;
	s = StringClean(s);
	cout << "Formated data:" << endl;
    PrettyPrint(s, 40);
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
	//calculate size of tmp
	data.seekg(0,ios_base::end ); //set cursor to end of file
	tmp_size = data.tellg(); //save number of last element in file
	data.seekg(0,ios_base::beg); //set cursor to begin of file
	//read date from file
	tmp = (char*)malloc(tmp_size * sizeof(char));
	data.read(tmp, tmp_size);
	//create string with data from tmp
	string str(tmp, tmp_size);
	free(tmp);
	data.close();
	return str;
}

string StringClean(string str){
    int pos;
    char * not_other_space_char[] = {"\a","\b","\n","\t","\v","\r","\f", "  "};
    char replace_word[] = "Vau!!!"; 

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

    return str;
}

void PrettyPrint(string str, int width){
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

        str_v.push_back(str.substr(last_pos, line_width));
        last_pos = last_pos + line_width;
        if (last_pos >= max_pos){
            break;
        }

    }
    PrintVector<string>(str_v);

}

template <typename T> void PrintVector(vector<T> v){
    unsigned int i;
    for (i = 0; i < v.size(); ++i){
       cout << v[i];
    }
	cout << endl;
}