#include "precompiled.hpp"
#include "gc/theta/thetaHeap.hpp"

ThetaHeap::ThetaHeap() {
    // todo initialize
    _memory_manager = NULL;
}

GrowableArray<GCMemoryManager *> ThetaHeap::memory_managers() {
    GrowableArray<GCMemoryManager*> memory_managers(1);
    memory_managers.append(_memory_manager);

    return memory_managers;
}