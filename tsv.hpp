#include "filesystem"
#include <bits/stdc++.h>
#include <algorithm>
#include <list>
using namespace std;

list<std::string> OpenTSV(string Path){
        list<std::string> TSV_LIST;
        ifstream Data(Path);
        string FileData;
        while (getline(Data, FileData)) {
            TSV_LIST.push_back(FileData);
        }
        return TSV_LIST;
}




string SearchTSV_As_String(list<string> Data, string Query){
    string Matches;
    for (const auto& s : Data) {
    if (s.find(Query) != std::string::npos) {
        Matches += s;
    }
    }
    return Matches;
}

list<string> SearchTSV_As_List(list<string> Data, string Query){
    list<string> Matches;
    for (const auto& s : Data) {
    if (s.find(Query) != std::string::npos) {
        Matches.push_back(s);
    }
    }
    return Matches;
}


list<string> Split_Rows(string sen) {
  
    
    stringstream ss(sen);
    
    
    string Whole_String ;
    
    
    list<string> Row_List;
    
    
    while (getline(ss, Whole_String , '	')) {
        size_t pos;
        while ((pos = Whole_String .find("	")) != std::string::npos) {
            Whole_String .replace(pos, 3, "");
        }
        
        Row_List.push_back(Whole_String);
    }
    
    return Row_List;
}


string GetRow(list<string> List, int place){
    if (place < 0){
        place = 0;
    }else if (place == 0)
    {
        return List.front();
    }
    
    if (place > List.size()) {
    place = List.size();
    }

    for (int i = 0; i < place; i++) {
        List.pop_front();
    }
    return List.front();
}


