
#include <string>
#include <nlohmann\json.hpp>
using json=nlohmann::json;
using namespace std;
int const CONSIZE=100;

json load_json(int argc,char *argv[],string filename);

void save_json(json j,string filename);

void show_store(json j);

void SetCursorPosition(const int x, const int y);

void ClearConsole(int SIZE);

void system(json j);

