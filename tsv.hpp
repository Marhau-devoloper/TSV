//we use filesystem to open and read or write a file
#include "filesystem"
//for searching
#include <algorithm>
// for creating and using lists
#include <list>

using namespace std;
// function with open .tsv file
list<string> OpenTSV(string Path){
        //path to file
        list<string> TSV_LIST;
        //open file and stream it to Data verb
        ifstream Data(Path);
        string FileData;
        // writing line by line file into a list like each collum in separate list
        while (getline(Data, FileData)) {
            // push next collum to back of list
            TSV_LIST.push_back(FileData);
        }
        //return list
        return TSV_LIST;
}



// searching inside of TSV and return it as string
string SearchTSV_As_String(list<string> &Data, string Query){
    string Matches;
    for (const auto& s : Data) {
    if (s.find(Query) != string::npos) {
        Matches += s;
    }
    }
    return Matches;
}
// searching inside of TSV and return it as list
list<string> SearchTSV_As_List(list<string> &Data, string Query){
    list<string> Matches;
    for (const auto& s : Data) {
    if (s.find(Query) != string::npos) {
        Matches.push_back(s);
    }
    }
    return Matches;
}

// this function help us to speperate rows in collum
list<string> Split_Rows(string &sentence,  bool csv = false) {
  
    
    stringstream ss(sentence);
    

    string Whole_String ;
    // separator verb init
    char separator;
    list<string> Row_List;
    //if csv is True we use csv , to string else we use spaces
    if (csv == true ) {
        separator = ',';
    }else{
        separator = '\t';
    }
    // seperate a each part of string and put them in list 
    while (getline(ss, Whole_String , separator)) {
        size_t pos;
        while ((pos = Whole_String .find("\t")) != string::npos) {
            Whole_String .replace(pos, 3, "");
        }
        
        Row_List.push_back(Whole_String);
    }
    // retrun seperated rows inside of list    
    return Row_List;
}

// function to get specific row from list like 0 
string GetRow(list<string>& List, size_t place){
    if (place >= List.size()) {
    place = List.size() - 1;
    }

    auto it = List.begin();
    advance(it, place);
    return *it;
}
// function with convers tsv or csv to json has 3 arguments, Path, Save_file = if true saves json file, csv = if true counts commas
string TSV_To_Json(string Path,bool save_file = false, bool csv = false ){
    //open TSV file as list
    list<string> lists = OpenTSV(Path);
    // save size of list
    int list_size= lists.size();
    // takes hedder with is firs collum
    string Headder = lists.front();
    //verbs is splited row of headder with will using as veriables in json 
    list<string>  verbs = Split_Rows(Headder,csv);
    // check how many verbs
    const short int number_of_verbs = verbs.size();
    
    //if Save_file == true we save result in file
    if (save_file == true){
    //open TSV.json for writing
    ofstream MyFile("TSV.json");
    // addin [ at start of json
    MyFile << "[" << endl;
    
    // count  main loop
    int counts;
    
    for (const auto& _ : lists){
        
        
        //starting first element in json with {
        MyFile << "{" << endl;
        //we get a line
        string TSV_Data = GetRow(lists,counts);
        // we split line into smaller pices
        list<string> Value = Split_Rows(TSV_Data,csv);
        //loop with write a json structure like "verb": value
        for (int i = 1; i < number_of_verbs; i++)
        {
            //we get a line   
            string key = GetRow(verbs, i);
            // we split line into smaller pices
            string value = GetRow(Value, i);

            // clean key
            key.erase(remove(key.begin(), key.end(), '\n'), key.end());
            key.erase(remove(key.begin(), key.end(), '\r'), key.end());
            key.erase(remove(key.begin(), key.end(), '"'), key.end());
            // clean value
            value.erase(remove(value.begin(), value.end(), '\n'), value.end());
            value.erase(remove(value.begin(), value.end(), '\r'), value.end());
            value.erase(remove(value.begin(), value.end(), '"'), value.end());


            MyFile << "\"" << key << "\": \"" << value << "\"";
            
            //here we check if this element is last one if it last one we not adding , at end
            if (i != number_of_verbs - 1)
            //adding , at end
                MyFile << ",";
            //make indent   
            MyFile << endl;
        
        }
        //here we check if this element is last one if it last one we not adding }, at end
        if (counts != list_size - 1){
            //adding }, at end
            MyFile << "}," << endl;
        }else{
            //adding regular }
            MyFile << "}" << endl;
        }
        //make indent
        MyFile << endl;
        //move to next part
        counts =+1;
        }
        
        //finish a json with ]
        MyFile << "]" << endl;
    
        //save file
        MyFile.close(); 
    }else{
    //if Save_file is false we just return json
    string json;
    //main loop
    json += "[\n" ;
    int counts = 1;
    for (const auto& _ : lists){

    //we use /n to make new line and [ { to start a json
    
    json += "{\n" ;
    //we getting a string line
    string TSV_Data = GetRow(lists,counts);
    //we dividing line into pieces
    list<string> Value = Split_Rows(TSV_Data,csv);
    //loop with write a json structure like "verb": value
    int ijson;
    for (const auto& _ : verbs)
    {
        
    //we get a line   
    string key = GetRow(verbs, ijson);
    // we split line into smaller pices
    string value = GetRow(Value, ijson);

    // clean key
    key.erase(remove(key.begin(), key.end(), '\n'), key.end());
    key.erase(remove(key.begin(), key.end(), '\r'), key.end());
    key.erase(remove(key.begin(), key.end(), '"'), key.end());
    // clean value
    value.erase(remove(value.begin(), value.end(), '\n'), value.end());
    value.erase(remove(value.begin(), value.end(), '\r'), value.end());
    value.erase(remove(value.begin(), value.end(), '"'), value.end());


    json += "\"" + key + "\": \"" + value + "\"";
    
    //here we check if this element is last one if it last one we not adding , at end  
    if (ijson != number_of_verbs - 1)
    json += ",";
    //making new line
    json += "\n";
    ijson ++;
    }
    //here we check if this element is last one if it last one we not adding }, at end
    if (counts != list_size - 1){
        //adding },/n
        json += "},\n";
    }else{
        //adding }/n
        json += "}\n" ;
        //finishing json with ]
        json += "]\n";
    }
    counts =+1;
    }
    
    
    
    //return json
    return json;
    }
    return "Done";
}


//function with converts TSV to CSV, arguments, Path with is path to file in string, Save file is bool if set to true save CSV as file and final 3rd argument is FileName with file expension on default set to Myfile.csv
string TSV_To_CSV(string path,bool Save_File = false, string Name = "Myfile.csv") {
    list<string> File = OpenTSV(path);
    
    if (Save_File == true){
        ofstream file(Name);
        for (const string &line : File) {
        string fixed = line;

        // replace tabs with commas
        replace(fixed.begin(), fixed.end(), '\t', ',');
        
        file << fixed << endl;
    
    }
    
    file.close();
    return Name + " File Saved";
    }else{
        string result;
        for (const string &line : File) {
        string fixed = line;

        // replace tabs with commas
        replace(fixed.begin(), fixed.end(), '\t', ',');
        
        result += fixed + "\n";
        
    }
    return result;
    }
    

    
}


//function with converts CSV to TSV, arguments, Path with is path to file in string, Save file is bool if set to true save CSV as file and final 3rd argument is FileName with file expension on default set to Myfile.tsv
string CSV_To_TSV(string path,bool Save_File = false, string Name = "Myfile.tsv") {
    list<string> File = OpenTSV(path);
    
    if (Save_File == true){
        ofstream file(Name);
        for (const string &line : File) {
        string fixed = line;

        // replace tabs with commas
        replace(fixed.begin(), fixed.end(), ',', '\t');
        
        file << fixed << endl;
    
    }
    
    file.close();
    return Name + " File Saved";
    }else{
        string result;
        for (const string &line : File) {
        string fixed = line;

        // replace tabs with commas
        replace(fixed.begin(), fixed.end(), '\t', ',');
        
        result += fixed + "\n";
        
    }
    return result;
    }
    

    
}
