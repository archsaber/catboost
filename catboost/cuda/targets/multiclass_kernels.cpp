#include "multiclass_kernels.h"

using namespace NKernelHost;

namespace NCudaLib {
    REGISTER_KERNEL(0xA11BB00,  TMultiLogitValueAndDerKernel);
    REGISTER_KERNEL(0xA11BB01,  TMultiLogitSecondDerKernel);
}
