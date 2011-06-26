#ifndef MEDIAN_MEASUREMENT_H
#define MEDIAN_MEASUREMENT_H

#include <WProgram.h>
#include <stdlib.h>

class MedianMeasurement {
public:
    MedianMeasurement(size_t size) : size(size), cur(0) {};
    ~MedianMeasurement();
    void init();
    bool getMedian(long &time, long& median);
    void pushMeasurement(long value);
    void pushMeasurement(long value, long time);
    
private:
    typedef struct {
        long value;
        long time;
    } Entry;
    
    typedef struct {
        int index;
        Entry values[0];
    } Buffer;
    
    int select(Entry**,int,int,int);
    int partition(Entry**,int,int,int);
    void swap(Entry**,int,int);
    
    size_t cur;
    size_t size;
    Buffer *buffer;
    Entry **measurements;
    
};

#endif