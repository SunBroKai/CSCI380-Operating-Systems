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

using namespace std;

const int REF_LENGTH = 10;
//Length of reference string.

int GetReferenceSize();
//Gets page number range
int GetFrameNumber();
//Get number of page frames.
void Generate(const int refSize, std::vector<int> & reference);
//Generates random reference string.
void Initialize(std::deque<int> & mem, const int frameNum);
//Initializes memory pages.
void PrintReferenceString(const std::vector<int> reference);
//
int FIFO(std::deque<int> & mem, int frameNum, std::vector<int> reference);
//First in first out algorithm.
//int LRU(PageFrame mem, int frameNum, std::vector<int> reference);
//Least recently used.
int FIFOInsert(std::deque<int> & mem, int page, int frameNum);
//
//int LRUInsert(int Page);
//
bool FIFOSearch(std::deque<int> & mem, int page, int frameNum);
//
//bool LRUSearch(int page);
//
//void LRUupdate(int index);
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

    refSize = GetReferenceSize();
    frameNum =  GetFrameNumber();
    
    //FIFO.
    Generate(refSize, reference);
    Initialize(fifo_mem, frameNum);

    cout << "Page fault of FIFO: " << FIFO(fifo_mem,frameNum,reference) << endl;
    cout << endl;
    
    PrintReferenceString(reference);
    
    //LRU.
    //Initialize(mem, frameNum);
    
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

void Initialize(std::deque<int> & mem, int frameNum)
{
    for(int i = 0; i < frameNum; i++)
    {
        mem.push_back(-1);
    }
    
    return;
}

void PrintReferenceString(const std::vector<int> reference)
{

    //cout << "Printing reference string..." << endl;
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
    if(FIFOSearch(mem,page,frameNum) == 0)
    {
        pageFault++;
        mem.pop_front();
        mem.push_back(page);
    }
    
    return pageFault;
}

bool FIFOSearch(std::deque<int> & mem, int page, int frameNum)
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
/*
int LRU(PageFrame mem, int frameNum, std::vector<int> reference)
{
    int faultCount = 0;
    for(int i = 0; i < REF_LENGTH; i++)
    {
        faultCount += LRUInsert(reference[i]);
        for(int j = 0; j < frameNum; j++)
        {
            cout << mem[j] << endl;
        }
    }
    
    return faultCount;
}

int LRUInsert(int page)
{
    int fault = 0;
    int index = -1;
    
    index = LRUSearch(page);
    if (index = -1)
    {
        
    }else{
        LRUupdate(index);
    }
    
    return fault;
}

int LRUSearch(int page)
{
    return 0;
}

void LRUupdate(int index)
{
    return;
}
*/