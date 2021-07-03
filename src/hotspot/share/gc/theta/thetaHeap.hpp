#include "gc/shared/markBitMap.hpp"
#include "gc/shared/collectedHeap.hpp"
#include "gc/shared/softRefPolicy.hpp"
#include "gc/shared/space.hpp"
#include "services/memoryManager.hpp"

class ThetaHeap : public CollectedHeap {
    friend class VMStructs;

private:
    SoftRefPolicy _soft_ref_policy;

    GCMemoryManager* _memory_manager;

    MemoryPool* _eden;
    MemoryPool* _survivor;
    MemoryPool* _tenured;

    ContiguousSpace* _space;

public:
    ThetaHeap();

    virtual Name kind() const override {
        return CollectedHeap::Theta;
    }

    virtual const char* name() const {
        return "Theta";
    }

    virtual SoftRefPolicy* soft_ref_policy() {
        return &_soft_ref_policy;
    }

    virtual jint initialize();
    virtual void post_initialize();
    virtual void initialize_serviceability();

    virtual GrowableArray<GCMemoryManager*> memory_managers();
    virtual GrowableArray<MemoryPool*> memory_pools();


};
