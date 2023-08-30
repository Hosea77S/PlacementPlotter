#ifndef COMMON__H
#define COMMON__H

#pragma once

//#include <bits/stdc++.h>
#include "myAssert.h"
#include "paramproc.h"
#include "Time.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <ctime>

//for checkFileExists
#include <sys/stat.h>

#include "constants.h"

/* #define SPL_HEIGHT 40.0
#define SPL_WIDTH 40.0
#define PAD_WIDTH   50.0 
#define PAD_HEIGHT  50.0
#define PAD_OFFSET  50.0 
#define PITCH 10.0
#define SPL_DELAY 5.5
#define JTL_DELAY 4.1

#define OUT_PIN_1 1
#define OUT_PIN_2 2

#define CELL_IN1_PIN_POS 0.0
#define CELL_IN2_PIN_POS 0.1
#define CELL_OUT_PIN_POS 0.2

#define JTL_IN_PIN_POS 0.0
#define JTL_OUT_PIN_POS 0.1

#define CLK_IN_PIN_POS 0.4
#define CLK_OUT_PIN_1_POS 0.5
#define CLK_OUT_PIN_2_POS 0.6 */



typedef std::pair <int, int> INT_PAIR;

enum Dir {_XX, _YY};

enum Child {_LEFT, _RIGHT};

enum LPType 
	{ noLP= 0, CPLEX= 1, CBC=2};

//enum TopType 
//	{ MMM= 0, LP_CPLEX= 1, LP_CBC=2};
	
enum TopType {
  MMM_GREEDY = 0,	
  PLACEMENT_AWARE = 1,
  HOLD_AWARE = 2,
  HOLD_PL_AWARE=3
};
	
	
typedef std::vector<bool> bit_vector;


bool checkFileExists (const std::string& name);
std::string getCurrentDateTime();


// C++ template to print vector container elements
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (unsigned i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", \n";
    }
    os << "]\n";
    return os;
}

// C++ template to print vector container elements
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T*>& v)
{
    os << "[";
    for (unsigned i = 0; i < v.size(); ++i) {
        os << *(v[i]);
        if (i != v.size() - 1)
            os << ", \n";
    }
    os << "]\n";
    return os;
}

// C++ template to print set container elements
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v)
{
    os << "[";
    for (auto const& it : v) {
        os << it;
        if (it != *v.rbegin())
            os << ", \n";
    }
    os << "]\n";
    return os;
}

// C++ template to print set container elements
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T*>& v)
{
    os << "[";
    for (auto const& it : v) {
        os << *(it);
        if (it != *v.rbegin())
            os << ", \n";
    }
    os << "]\n";
    return os;
}


// C++ template to print map container elements
template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T, S>& v)
{
    os << "{";
    for (auto const& it : v) 
        os << it.first << " : "
           << it.second << "\n";
    os << "}\n";
     
    return os;
}

// C++ template to print map container elements
template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T*, S*>& v)
{
    os << "{";
    for (auto const& it : v) 
        os << *(it.first) << " : "
           << *(it.second) << "\n";
    os << "}\n";
     
    return os;
}
 
// C++ template to print pair<>
// class by using template
template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& v)
{
    os << "(";
    os << v.first << ", "
       << v.second << ")";
    return os;
}


// C++ template to print pair<>
// class by using template
template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T*, S*>& v)
{
    os << "(";
    os << *(v.first) << ", "
       << *(v.second) << ")";
    return os;
}
 
#endif //__COMMON__H