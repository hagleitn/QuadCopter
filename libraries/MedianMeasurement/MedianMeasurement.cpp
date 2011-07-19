#include <MedianMeasurement.h>
#include <stdlib.h>

void MedianMeasurement::init() {
    cur = 0;
    size = (size & 0x1 == 0) ? size+1 : size;

    buffer = (Buffer*) malloc(sizeof(Buffer)+size*sizeof(Entry));
    measurements = (Entry**) malloc(sizeof(Entry*)*size);

    buffer->index = 0;
    for (int i = 0; i < size; ++i) {
        buffer->values[i].time = 0;
        buffer->values[i].value = 0;
        measurements[i] = &(buffer->values[i]);
    }
}

MedianMeasurement::~MedianMeasurement() {
    if (0 != buffer) free(buffer);
    if (0 != measurements) free(measurements);
}

void MedianMeasurement::swap(Entry **m, int i, int j) {
    Entry *tmp = m[i];
    m[i] = m[j];
    m[j] = tmp;
}

int MedianMeasurement::partition(Entry **m, int left, int right, int pivot) {
    double pivotValue = m[pivot]->value;
    swap(m,pivot,right);
    int store = left;
    for (int i = left; i < right; ++i) {
        if (m[i]->value < pivotValue) {
            swap(m,store,i);
            ++store;
        }
    }
    swap(m,right,store);
    return store;
}

int MedianMeasurement::select(Entry **m, int left, int right, int k) {
    while (true) {
        int pivot = left + (right-left)/2;
        int newPivot = partition(m, left, right, pivot);
        int dist = newPivot - left + 1;
        if (dist == k) {
            return newPivot;
        } else if (k < dist) {            
            right = newPivot - 1;
        } else {
            k -= dist;
            left = newPivot + 1;
        }
    }
}

bool MedianMeasurement::getMedian(double& median, long &time) {
    if (cur == size) {
        int i = select(measurements,0,size-1,size/2+1);

        median = measurements[i]->value;
        time = measurements[i]->time;

        return true;
    }
    return false;
}

void MedianMeasurement::pushMeasurement(double value) {
    pushMeasurement(value,millis());
}

void MedianMeasurement::pushMeasurement(double value, long time) {
    buffer->values[buffer->index].value = value;
    buffer->values[buffer->index].time = time;

    buffer->index = (buffer->index+1)%size;

    if (cur < size) {
        ++cur;
    }
}
