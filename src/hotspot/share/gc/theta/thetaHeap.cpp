#include "precompiled.hpp"
#include "gc/theta/thetaHeap.hpp"
#include "gc/theta/thetaBarrierSet.hpp"

jint ThetaHeap::initialize() {

    BarrierSet::set_barrier_set(new ThetaBarrierSet());
    return JNI_OK;
}

size_t ThetaHeap::max_capacity() const {
    return 0;
}

size_t ThetaHeap::capacity() const {
    return 0;
}

size_t ThetaHeap::used() const {
    return 0;
}

bool ThetaHeap::is_in(const void *p) const {
    return false;
}

bool ThetaHeap::is_maximal_no_gc() const {
    return false;
}

size_t ThetaHeap::tlab_capacity(Thread *thr) const {
    return 0;
}

size_t ThetaHeap::tlab_used(Thread *thr) const {
    return 0;
}

void ThetaHeap::collect(GCCause::Cause cause) {

}

void ThetaHeap::do_full_collection(bool clear_all_soft_refs) {

}

SoftRefPolicy *ThetaHeap::soft_ref_policy() {
    return nullptr;
}

GrowableArray<GCMemoryManager *> ThetaHeap::memory_managers() {
    return GrowableArray<GCMemoryManager *>();
}

GrowableArray<MemoryPool *> ThetaHeap::memory_pools() {
    return GrowableArray<MemoryPool *>();
}

void ThetaHeap::object_iterate(ObjectClosure *cl) {

}


void ThetaHeap::print_on(outputStream *st) const {

}

bool ThetaHeap::print_location(outputStream *st, void *addr) const {
    return false;
}

void ThetaHeap::print_tracing_info() const {

}


HeapWord *ThetaHeap::mem_allocate(size_t size, bool *gc_overhead_limit_was_exceeded) {
    return nullptr;
}

void ThetaHeap::initialize_serviceability() {

}

size_t ThetaHeap::unsafe_max_tlab_alloc(Thread *thr) const {
    return CollectedHeap::max_tlab_size() * HeapWordSize;
}

HeapWord * ThetaHeap::allocate_new_tlab(size_t min_size, size_t requested_size, size_t *actual_size) {

}