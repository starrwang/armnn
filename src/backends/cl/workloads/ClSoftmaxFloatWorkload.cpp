//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "ClSoftmaxFloatWorkload.hpp"
#include <cl/ClTensorHandle.hpp>
#include <backendsCommon/CpuTensorHandle.hpp>

#include "ClWorkloadUtils.hpp"

namespace armnn
{

ClSoftmaxFloatWorkload::ClSoftmaxFloatWorkload(const SoftmaxQueueDescriptor& descriptor, const WorkloadInfo& info,
                                                   std::shared_ptr<arm_compute::MemoryManagerOnDemand>& memoryManager)
    : FloatWorkload<SoftmaxQueueDescriptor>(descriptor, info)
    , m_SoftmaxLayer(memoryManager)
{
    m_Data.ValidateInputsOutputs("ClSoftmaxFloatWorkload", 1, 1);

    arm_compute::ICLTensor& input  = static_cast<ClTensorHandle*>(m_Data.m_Inputs[0])->GetTensor();
    arm_compute::ICLTensor& output = static_cast<ClTensorHandle*>(m_Data.m_Outputs[0])->GetTensor();
    m_SoftmaxLayer.configure(&input, &output, m_Data.m_Parameters.m_Beta);
}

void ClSoftmaxFloatWorkload::Execute() const
{
    ARMNN_SCOPED_PROFILING_EVENT_CL("ClSoftmaxFloatWorkload_Execute");
    RunClFunction(m_SoftmaxLayer, CHECK_LOCATION());
}

} //namespace armnn
