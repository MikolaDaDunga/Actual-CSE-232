#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
#include<map>
#include<set>

std::set<std::string> ReplacementCensor(std::string inFileName, std::string outFileName, std::map<std::string, std::string> dataMap) {
    std::ifstream input(inFileName);
    std::ofstream output(outFileName);
    std::vector<std::string> holder;
    std::vector<std::string> outputHolder;
    std::string currentString = "";
    std::set<std::string> outSet;
    std::pair<std::set<std::string>::iterator, bool> result;
    std::set<std::string>::iterator iter;
    std::string temp = "";

    std::ostream_iterator<std::string> out(output, " ");
    std::string currentLine = "";
    
    //std::map<std::string, std::string>::iterator iter;
    while (!input.eof()){
        getline(input, currentLine);
        for (char & current : currentLine) {
            tolower(current);
        }
        for (std::map<std::string, std::string>::iterator iter = dataMap.begin(); iter != dataMap.end(); iter++) {
            auto loc = currentLine.find((*iter).first);
            if (loc != std::string::npos) {
                //currentLine.rep
                currentLine.erase(std::find(currentLine.begin(), currentLine.end(), (*iter).first), currentLine.end());
            }
        }
        output << currentLine;
        
    }
    //holder.push_back(temp);
    std::string temp2 = " ";
    for (std::string key : holder) {
        temp2 = key;
        auto location = dataMap.find(key);
        if (location == dataMap.end()) {
            output << key;
            if (key.at(key.size()-1)!='/n') {
                output << " ";
            }
        }
        else {
            outSet.insert(key);
            output << 
            dataMap.at(key);
            if (key.at(key.size()-1)!='/n') {
                output << " ";
            }
        }
    }


    auto replacer = [&outSet, dataMap](std::string key) {
        std::string temp2 = key;
        if (temp2.at(temp2.size()-1)==' ') {
            temp2.pop_back();
        }
        auto location = dataMap.find(key);
        if (location == dataMap.end()) {
            return dataMap.at(temp2);
        }
        else {
            outSet.insert(key);
            return dataMap.at(temp2);
        }
    };
    //std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(holder));
    std::transform(holder.begin(), holder.end(), out, replacer);
    return outSet;
}

int main() {
    std::map<std::string, std::string> bad_to_good = {{"wolverine", "wolverwimps"}};
    std::set<std::string> result = ReplacementCensor("input.txt", "output.txt", bad_to_good);
    return 0;
}