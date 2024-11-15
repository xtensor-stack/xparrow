// Copyright 2024 Man Group Operations Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "sparrow/builder/builder.hpp"
#include "test_utils.hpp"

namespace sparrow
{

    template<class T>
    void sanity_check(T && /*t*/)
    {
    }

    // to keep everything very short for very deep nested types
    template<class T>
    using nt = nullable<T>;


    TEST_SUITE("builder")
    {
        TEST_CASE("fixed-sized-list-layout")
        {
            // fixed_sized_list<float, 3>
            {   
                std::vector<std::array<float, 3>> v{
                    {1.0f, 2.0f, 3.0f},
                    {4.0f, 5.0f, 6.0f},
                    {7.0f, 8.0f, 9.0f}
                };
                sanity_check(sparrow::build(v));
            }
            // fixed_sized_list<float, 3>  with nulls
            {   
                std::vector<nt<std::array<nt<float>, 3>>> v{
                    std::array<nt<float>, 3>{1.0f, sparrow::nullval, 3.0f},
                    sparrow::nullval,
                    std::array<nt<float>, 3>{7.0f, 8.0f, sparrow::nullval}
                };
                sanity_check(sparrow::build(v));
            }
        }
    }
}

