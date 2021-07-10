#include "precompiled.hpp"
#include "thetaBarrierSet.hpp"
#include "runtime/thread.hpp"
#include "gc/shared/barrierSet.hpp"
#include "gc/shared/barrierSetAssembler.hpp"
#ifdef COMPILER1
#include "gc/shared/c1/barrierSetC1.hpp"
#endif
#ifdef COMPILER2
#include "gc/shared/c2/barrierSetC2.hpp"
#endif

ThetaBarrierSet::ThetaBarrierSet() : BarrierSet(
    make_barrier_set_assembler<BarrierSetAssembler>(),
    make_barrier_set_c1<BarrierSetC1>(),
    make_barrier_set_c2<BarrierSetC2>(),
    NULL,
    BarrierSet::FakeRtti(BarrierSet::ThetaBarrierSet)) {}