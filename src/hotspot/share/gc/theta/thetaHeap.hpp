#include "gc/shared/markBitMap.hpp"
#include "gc/shared/collectedHeap.hpp"
#include "gc/shared/softRefPolicy.hpp"
#include "gc/shared/space.hpp"
#include "services/memoryManager.hpp"

class ThetaHeap : public CollectedHeap {
    friend class VMStructs;

public:
    Name kind() const override { return Theta; }
    const char *name() const override { return "Theta"; }

    jint initialize() override;

    size_t used() const override;
    size_t capacity() const override;
    size_t max_capacity() const override;
    bool is_maximal_no_gc() const override;

    bool is_in(const void *p) const override;

    HeapWord* allocate_new_tlab(size_t min_size, size_t requested_size, size_t* actual_size) override;

    size_t tlab_capacity(Thread *thr) const override;
    size_t tlab_used(Thread *thr) const override;
    size_t unsafe_max_tlab_alloc(Thread* thr) const override;

    void collect(GCCause::Cause cause) override;
    void do_full_collection(bool clear_all_soft_refs) override;

    SoftRefPolicy *soft_ref_policy() override;

    GrowableArray<GCMemoryManager *> memory_managers() override;
    GrowableArray<MemoryPool *> memory_pools() override;

    void object_iterate(ObjectClosure *cl) override;


    void print_on(outputStream *st) const override;
    bool print_location(outputStream *st, void *addr) const override;
    void print_tracing_info() const override;

    void gc_threads_do(ThreadClosure *tc) const override { };
    void register_nmethod(nmethod *nm) override { };
    void unregister_nmethod(nmethod *nm) override { };
    void flush_nmethod(nmethod *nm) override { };
    void verify_nmethod(nmethod *nm) override { };
    void prepare_for_verify() override { };
    void verify(VerifyOption option) override { };

protected:
    HeapWord *mem_allocate(size_t size, bool *gc_overhead_limit_was_exceeded) override;

private:
    void initialize_serviceability() override;
};
