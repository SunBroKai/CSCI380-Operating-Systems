/*
* CSCI 380 programming project - Kai Jungbluth - Spring 2017
* This program demonstrates the use of the "First in, first out",
* "Least recently used", and optimal algorithms.
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
//Initializes memory pages for FIFO.

void InitializeLRU(std::vector<int> & mem, int frameNum);
//Initializes memory pages for LRU.

void InitializeOptimal(std::vector<int> & mem, int frameNum);
//Initializes memory pages for optimal page algorithm.

void PrintReferenceString(const std::vector<int> reference);
//Prints Reference string.

int FIFO(std::deque<int> & mem, int frameNum, std::vector<int> reference);
//Applies First in first out algorithm and returns number of page faults.

int LRU(std::vector<int> & mem, int frameNum, std::vector<int> reference);
//Applies least recently used algorithm and returns number of page faults.

int Optimal(std::vector<int> & mem, int frameNum, std::vector<int> reference);
//Applies the optimal page algorithm and returns number of page faults.

int FIFOInsert(std::deque<int> & mem, int page, int frameNum);
//Inserts page into page frame using FIFO.

int LRUInsert(std::vector<int> & mem, int page, int frameNum);
//Inserts page into page frame using LRU.

int OptimalInsert(std::vector<int> & mem, int page, int it, int frameNum, std::vector<int> reference);
//Inserts page into page frame using the optimal page algorithm.

bool FIFOSearch(std::deque<int> & mem, int page);
//Returns whether or not page is currently in the FIFO page frame.

int LRUSearch(std::vector<int> & mem, int page);
//Returns index of page from LRU page frame if present, -1 otherwise.

bool OptimalSearch(std::vector<int> & mem, int page);
//Returns whether or not page is currently in the optimal page frame.

void LRUupdate(std::vector<int> & mem, int index);
//Moves most recently used page to the end of the page frame,

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
    //Page frame for FIFO.
    std::vector<int> lru_mem;
    //Page frame for LRU.
    std::vector<int> opt_mem;
    //Page frame for optimal.
    
    refSize = GetReferenceSize();
    frameNum =  GetFrameNumber();
    
    //Perform FIFO.
    Generate(refSize, reference);
    InitializeFIFO(fifo_mem,frameNum);
    cout << "Page fault of FIFO: " << FIFO(fifo_mem,frameNum,reference) << endl;
    cout << endl;
    
    //Print reference string.
    PrintReferenceString(reference);
    
    //Perform LRU.
    InitializeLRU(lru_mem,frameNum);
    cout << "Page fault of LRU: " << LRU(lru_mem,frameNum,reference) << endl;
    cout << endl;
    
    //Print reference string one more time.
    PrintReferenceString(reference);
    
    //Perform optimal algorithm.
    InitializeOptimal(opt_mem,frameNum);
    cout << "Page fault of optimal: " << Optimal(opt_mem,frameNum,reference) << endl;
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
    if (index == mem.size() - 1) 
    {
            return;
    }
    int cur = mem[index]; 
    mem.erase(mem.begin()+index);
    mem.push_back(cur);
    
    return;
}

void InitializeOptimal(std::vector<int> & mem, int frameNum)
{
    for(int i = 0; i < frameNum; i++)
    {
        mem.push_back(-1);
    }
    
    return;
}

int Optimal(std::vector<int> & mem, int frameNum, std::vector<int> reference)
{
    int flag,
        faultCount = 0;
        
    cout << "Running optimal algorithm..." << endl;
    for(int i = 0; i < REF_LENGTH; i++)
    {
        flag = 0;
        faultCount += OptimalInsert(mem,reference[i],i,frameNum,reference);
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

int OptimalInsert(std::vector<int> & mem, int page, int it, int frameNum, std::vector<int> reference)
{
    //About 90% of the time spent on this program was spent on this function...
    int pageFault = 0,
        index = 0,
        highestDistance = 0;
    bool found = false,
         frameAcquired = false;
    int * distance = new int[frameNum];
    
    for(int k = 0; k < frameNum; k++)
    {
        distance[k] = -1;
    }
    found = OptimalSearch(mem,page);
    if (found == false)
    {
        for(int i = 0; i < frameNum; i++)
        {
            for(int j = it+1; j < REF_LENGTH; j++)
            {
                if(mem[i] == reference[j] and distance[i] == -1)
                {
                    distance[i] = j-it;
                }
            }
        }
        
        for(int l = 0; l < frameNum; l++)
        {
            if(distance[l] == -1 and not frameAcquired)
            {
                index = l;
                frameAcquired = true;
            }
            else if(distance[l] != -1 and distance[l] > highestDistance and not frameAcquired)
            {
                highestDistance = distance[l];
                index = l;
            }
        }
        mem.erase(mem.begin()+index);
        mem.push_back(page);
        pageFault++;
    }
    delete[] distance;
    distance = NULL;
    
    return pageFault;
}

bool OptimalSearch(std::vector<int> & mem, int page)
{
    bool found = false;
    
    for(int i = 0; i < mem.size(); i++)
    {
        if(mem[i] == page)
        {
            found = true;
        }
    }

    return found;
}
