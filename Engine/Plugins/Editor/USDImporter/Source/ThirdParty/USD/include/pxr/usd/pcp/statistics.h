//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PCP_STATISTICS_H
#define PCP_STATISTICS_H

#include "pxr/pxr.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

class PcpCache;
class PcpPrimIndex;

/// Accumulate and print statistics about the contents of \p cache to
/// \p out.
void
Pcp_PrintCacheStatistics(
    const PcpCache* cache, std::ostream& out = std::cout);

/// Accumulate and print statistics about the contents of \p primIndex to
/// \p out.
void
Pcp_PrintPrimIndexStatistics(
    const PcpPrimIndex& primIndex, std::ostream& out = std::cout);

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PCP_STATISTICS_H
