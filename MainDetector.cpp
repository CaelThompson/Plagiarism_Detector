#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <fstream>

using namespace std;
//This is a plagiarism detector made in C++ using functions to generate two unique hashes for strings. The hashes will be compared to a 
//set of target strings hashes and if they are the same, then plagiarism is in effect.

//Hash structure
struct Hash{
    //Constant variables used to prevent hash collision
    const long long a0 = 31, b0 = 1e9+7;
    const long long a1 = 37, b1 = 1e9+9;
    long long hash0 = 0, hash1 = 0;
    Hash(const string& comp1){
        calcHash0(comp1);
        calcHash1(comp1);
    }
    //Hash value calculations
    //First string to hash
    void calcHash0(const string& comp1){
        long power = 1;
        for(char character:comp1){
            hash0 = (hash0+(character+1-'a')*power)%b0;
            power = (power*a0)%b0;
        }
    }
    void calcHash1(const string& comp1){
        long power = 1;
        for(char character:comp1){
            hash1 = (hash1+(character+1-'a')*power)%b1;
            power = (power*a1)%b1;
        }
    }
    //Compare two different objects using comparison overloading
    bool operator==(const Hash& diff){
        return (hash0 == diff.hash0 && hash1 == diff.hash1);
    }
}; 
struct Hash2{
    //Constant variables used to prevent hash collision
    const long long a0 = 31, b0 = 1e9+7;
    const long long a1 = 37, b1 = 1e9+9;
    long long hash2 = 0, hash3 = 0;
    Hash2(const string& comp2){
        calcHash2(comp2);
        calcHash3(comp2);
    }
    //Second string to hash
    void calcHash2(const string& comp2){
        long power = 1;
        for(char character:comp2){
            hash2 = (hash2+(character+1-'a')*power)%b0;
            power = (power*a0)%b0;
        }
    }
    void calcHash3(const string& comp2){
        long power = 1;
        for(char character:comp2){
            hash3 = (hash3+(character+1-'a')*power)%b1;
            power = (power*a1)%b1;
        }
    }
    bool operator==(Hash2& diff2){
        return (hash2 == diff2.hash2 && hash3 == diff2.hash3);
    }
};
struct targetHash{
    const long long a0 = 31, b0 = 1e9+7;
    const long long a1 = 37, b1 = 1e9+9;
    long long hash4 = 0, hash5 = 0;
    targetHash(const string& targetItem){
        calcHash4(targetItem);
        calcHash5(targetItem);
    }
    //target strings to hash
    void calcHash4(const string& targetItem){
        long power = 1;
        for(char character:targetItem){
            hash4 = (hash4+(character+1-'a')*power)%b0;
            power = (power*a0)%b0;
        }
    }
    void calcHash5(const string& targetItem){
        long power = 1;
        for(char character:targetItem){
            hash5 = (hash5+(character+1-'a')*power)%b1;
            power = (power*a1)%b1;
        }
    }
    bool operator==(targetHash& diff3){
        return (hash4 == diff3.hash4 && hash5 == diff3.hash5);
    }   
};
//The main plagiarism detector structure
template<typename T>
struct plagDetect{
    plagDetect(T hash0,T hash1,T hash2,T hash3,T hash4,T hash5){
        plagDetector(hash0,hash1,hash2,hash3,hash4,hash5);
    }
    //The plagiarism detector
    void plagDetector(T hash0,T hash1,T hash2,T hash3,T hash4,T hash5){
        if((hash0 == hash4) && (hash1 == hash5)){
            cout << "Plagiarism detected! Identical hashes! Discovered in the first file." << endl;
        }
        else if((hash2 == hash4) && (hash3 == hash5)){
            cout << "Plagiarism detected! Identical hashes! Discovered in the second file." << endl;
        }
        else{
            cout << "No Plagiarism detected!" << endl;
        }  
    }
};
int main(){
    //Opening files to read strings and print the hashes. 
    //Also sends the hashes to the plagiarsim detector function.
    ifstream compFile1;
    ifstream compFile2;
    ifstream dataFile;
    compFile1.open("comparers/comp1");
    compFile2.open("comparers/comp2");
    dataFile.open("Data/items.txt");
    if(!compFile1 && !compFile2 && !dataFile){
        cout << "cannot open file";
        exit(1);
    }
    if(compFile1.is_open() && compFile2.is_open() && dataFile.is_open()){
        string comp1, comp2, targetItem;
        while(getline(compFile1,comp1), getline(compFile2,comp2), getline(dataFile,targetItem)){
            Hash hasher(comp1);
            Hash2 hasher2(comp2);
            targetHash hasher3(targetItem);
            //cout << "file 1 open" << endl;
            cout << "The hash values of " << comp1 << " are: ";
            cout << "(" << hasher.hash0 << ", " << hasher.hash1 << ")" << endl;
            //cout << "file 2 open" << endl;
            cout << "The hash values of " << comp2 << " are: ";
            cout << "(" << hasher2.hash2 << ", " << hasher2.hash3 << ")" << endl;
            //cout << "target file open" << endl;
            cout << "The hash values of " << targetItem << " are: ";
            cout << "(" << hasher3.hash4 << ", " << hasher3.hash5 << ")" << endl;
            plagDetect<long long> plag(hasher.hash0, hasher.hash1, hasher2.hash2, hasher2.hash3, hasher3.hash4, hasher3.hash5);
        }
        compFile1.close();
        compFile2.close();
        dataFile.close();
    }      
}