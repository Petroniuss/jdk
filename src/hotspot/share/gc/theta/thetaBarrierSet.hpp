#ifndef SHARE_GC_THETA_THETABARRIERSET_HPP
#define SHARE_GC_THETA_THETABARRIERSET_HPP

#include "gc/shared/barrierSet.hpp"

class ThetaBarrierSet : public BarrierSet {
    friend class VMStructs;

public:
    ThetaBarrierSet();
    void print_on(outputStream *st)  const override { }

    template<DecoratorSet decorators, typename BarrierSetT = ThetaBarrierSet>
    class AccessBarrier: public BarrierSet::AccessBarrier<decorators, BarrierSetT> {};
};

template<>
struct BarrierSet::GetName<ThetaBarrierSet> {
    static const BarrierSet::Name value = BarrierSet::ThetaBarrierSet;
};

template<>
struct BarrierSet::GetType<BarrierSet::ThetaBarrierSet> {
    typedef ::ThetaBarrierSet type;
};

#endif
