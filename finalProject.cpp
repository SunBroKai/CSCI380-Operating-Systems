/*
* CSCI 380 programming project - Kai Jungbluth - Spring 2017
* This program demonstrates the use of the "First in, first out" and 
* "Least recently used" algorithms.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <deque>
#include <map>

using namespace std;

const int REF_LENGTH = 10;
//Length of reference string.

int GetReferenceSize();
//Gets page number range
int GetFrameNumber();
//Get number of page frames.
void Generate(const int refSize, std::vector<int> & reference);
//Generates random reference string.
void InitializeFIFO(std::deque<int> & mem, const int frameNum);
//Initializes memory pages.
void InitializeLRU(std::vector<int> & mem, int frameNum);
//
void PrintReferenceString(const std::vector<int> reference);
//
int FIFO(std::deque<int> & mem, int frameNum, std::vector<int> reference);
//First in first out algorithm.
int LRU(std::vector<int> & mem, int frameNum, std::vector<int> reference);
//Least recently used.
int FIFOInsert(std::deque<int> & mem, int page, int frameNum);
//
int LRUInsert(std::vector<int> & mem, int page, int frameNum);
//
bool FIFOSearch(std::deque<int> & mem, int page);
//
int LRUSearch(std::vector<int> & mem, int page);
//
void LRUupdate(std::vector<int> & mem, int index);
//

//********************************** Main *************************************

int main()
{
    int refSize;
    //Page number range.
    int frameNum;
    //Number of page frames in memory.    
    std::vector<int> reference;
    //Sequence of pages.
    std::deque<int> fifo_mem;
    //Page frame.
    std::vector<int> lru_mem;

    refSize = GetReferenceSize();
    frameNum =  GetFrameNumber();
    
    //Perform FIFO.
    Generate(refSize, reference);
    InitializeFIFO(fifo_mem,frameNum);

    cout << "Page fault of FIFO: " << FIFO(fifo_mem,frameNum,reference) << endl;
    cout << endl;
    
    PrintReferenceString(reference);
    
    //Perform LRU.
    InitializeLRU(lru_mem,frameNum);
    cout << "Page fault of LRU: " << LRU(lru_mem,frameNum,reference) << endl;
    cout << endl;
    
    return 0;
}

//******************************** Functions **********************************

int GetReferenceSize()
{
    int ref;
    
    cout << "Enter page number(0-9)=>";
    cin >> ref;
    
    return ref;
}

int GetFrameNumber()
{
    int frame;
    
    cout << "Enter number of page frames in memory(1-7)=>";
    cin >> frame;
    
    return frame;
}

void Generate(int refSize, std::vector<int> & reference)
{
    srand(time(0));
    cout << "Generating random reference string..." << endl;
    for(int i = 0; i < REF_LENGTH; i++)
    {
        reference.push_back(rand() % refSize);
        cout << reference[i];
        if(i == REF_LENGTH-1)
        {
            cout << "." << endl;
        }else{
            cout << ", ";
        }   
    }
    cout << endl;

    return;
}


void PrintReferenceString(const std::vector<int> reference)
{
    cout << "Printing reference string..." << endl;
    for(int i = 0; i < reference.size(); i++)
    {
        cout << reference[i];
        if(i == reference.size()-1)
        {
            cout << "." << endl;
        }else{
            cout << ", ";
        }   
    }
    cout << endl;
    
    return;
}

void InitializeFIFO(std::deque<int> & mem, int frameNum)
{
    for(int i = 0; i < frameNum; i++)
    {
        mem.push_back(-1);
    }
    
    return;
}

int FIFO(std::deque<int> & mem, int frameNum, std::vector<int> reference)
{
    cout << "Running FIFO algorithm..." << endl;
    int faultCount = 0;
    for(int i = 0; i < REF_LENGTH; i++)
    {
        faultCount += FIFOInsert(mem,reference[i],frameNum);
        cout << "Frames: "; 
        for(int j = 0; j < frameNum; j++)
        {   
            cout << mem[j];
            if(j == frameNum-1)
            {
                cout << "." << endl;
            }else{
                cout << ", ";
            }   
        }
    }
    cout << endl;
    
    return faultCount;
}

int FIFOInsert(std::deque<int> & mem, int page, int frameNum)
{
    //cout << "ENTERED INSERT" << endl;
    int pageFault = 0;
    if(FIFOSearch(mem,page) == false)
    {
        pageFault++;
        mem.pop_front();
        mem.push_back(page);
    }
    
    return pageFault;
}

bool FIFOSearch(std::deque<int> & mem, int page)
{
    //cout << "ENTERED SEARCH" << endl;
    bool found = false;
    for(int i; i < mem.size(); i++)
    {
        if(mem[i] == page)
        {
            found = true;
        }
    }

    return found;
}

void InitializeLRU(std::vector<int> & mem, int frameNum)
{
    for(int i = 0; i < frameNum; i++)
    {
        mem.push_back(-1);
    }
    
    return;
}

int LRU(std::vector<int> & mem, int frameNum, std::vector<int> reference)
{
    cout << "Running LRU algorithm..." << endl;
    int faultCount = 0;
    for(int i = 0; i < REF_LENGTH; i++)
    {
        faultCount += LRUInsert(mem,reference[i],frameNum);
        cout << "Frames: "; 
        for(int j = 0; j < frameNum; j++)
        {
            cout << mem[j];
            if(j == frameNum-1)
            {
                cout << "." << endl;
            }else{
                cout << ", ";
            }  
        }
    }
    cout << endl;

    return faultCount;
}


int LRUInsert(std::vector<int> & mem, int page, int frameNum)
{
    int pageFault = 0;
    int index = -1;
    
    index = LRUSearch(mem,page);
    if (index == -1)
    {
        mem.erase(mem.begin());
        mem.push_back(page);
        pageFault++;
    }else{
        LRUupdate(mem, index);
    }
    
    return pageFault;
}


int LRUSearch(std::vector<int> & mem, int page)
{
    //cout << "ENTERED SEARCH" << endl;
    int index = -1;
    for(int i = 0; i < mem.size(); i++)
    {
        if(mem[i] == page)
        {
            index = i;
        }
    }

    return index;
}

void LRUupdate(std::vector<int> & mem, int index)
{
    if (index == mem.size() - 1) {
            return;
    }
    int cur = mem[index]; 
    mem.erase(mem.begin()+index);
    mem.push_back(cur);
    
    return;
}
