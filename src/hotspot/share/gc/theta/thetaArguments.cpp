#include "precompiled.hpp"
#include "gc/theta/thetaArguments.hpp"
#include "runtime/globals.hpp"
#include "runtime/globals_extension.hpp"
#include "gc/theta/thetaHeap.hpp"

size_t ThetaArguments::conservative_max_heap_alignment() {
    return UseLargePages ? os::large_page_size() : os::vm_page_size();
}

void ThetaArguments::initialize_alignments() {
    size_t page_size = UseLargePages ? os::large_page_size() : os::vm_page_size();
    size_t align = MAX2((size_t)os::vm_allocation_granularity(), page_size);
    SpaceAlignment = align;
    HeapAlignment  = align;
}

void ThetaArguments::initialize() {
    GCArguments::initialize();

    assert(UseThetaGC, "Sanity");
}



CollectedHeap* ThetaArguments::create_heap() {
    return new ThetaHeap();
}