# TSV
Small C++ header with help to work with .TSV files


headder has couple functions

| Function ```OpenTSV(Path)```
Opens .tsv files and returns a list

| Function ```SearchTSV_As_String(List, Query)```
Searches for a particular part in a list and returns matches as a string

| Function ```SearchTSV_As_List(List, Query)```
Searches for a particular part in a list and returns matches as a list

| Function ```Split_Rows(string)```
Splits rows using tabs and returns a list with all rows separated

| Function ```GetRow(List, Place)```
Uses Place (an int) to return a specific item from the list as a string

| Function ```TSV_To_Json(string Path, bool save_file = false, bool csv = false)```
Converts .tsv to JSON. Has 3 arguments:

```Path``` = path to file
```save_file``` = if true, saves the JSON file
```csv``` = if true, counts commas

### file format
test.tsv
```md
Name	Status	Languages
maks	devoloper	C++
```
### Example usage


```cpp
//open file
list<string> File = OpenTSV("test.tsv");
//save file as list
list<string> out_as_list = SearchTSV_As_List(File,"maks");
//save file as string
string out_as_string = SearchTSV_As_String(File,"maks");
//get one line
cout << "One line:"<< endl;
cout << GetRow(out_as_list,0) << endl;
//get one row
cout << "One Row:"<< endl;
cout << Split_Rows(out_as_string,0).front() << endl;
//convert to json
cout << "Json:"<< endl;
string test = TSV_To_Json("test.tsv");
cout << test;
```
### Out Put
```md
One line:
maks    devoloper       C++
One Row:
maks
Json:
[
{
"Name": "maks",
"Status": "devoloper",
"Languages": "C++"
}
]

```
 

