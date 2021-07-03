#ifndef SHARE_GC_THETA_THETAARGUMENTS_HPP
#define SHARE_GC_THETA_THETAARGUMENTS_HPP

#include "gc/shared/gcArguments.hpp"

class CollectedHeap;

class ThetaArguments : public GCArguments {
private:
    virtual void initialize_alignments();

    virtual void initialize();
    virtual size_t conservative_max_heap_alignment();
    virtual CollectedHeap* create_heap();
};

#endif // SHARE_GC_THETA_THETAARGUMENTS_HPP
