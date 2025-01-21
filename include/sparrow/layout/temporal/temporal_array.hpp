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
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or mplied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// tdD : std::chrono::year_month_day
// tdm : std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>

// tts : std::chrono::duration<int32_t, std::ratio<1, 1>>
// ttm : std::chrono::duration<int32_t, std::milli>
// ttu : std::chrono::microseconds
// ttn : std::chrono::nanoseconds

// tDs : std::chrono::seconds
// tDm : std::chrono::milliseconds
// tDu : std::chrono::microseconds
// tDn : std::chrono::nanoseconds

// tiM : std::chrono::months
// tiD : sparrow::day_time_interval
// tin : sparrow::month_day_nanoseconds_interval

namespace sparrow
{
    using temporal_types_t = mpl::typelist<
        // std::chrono::year_month_day,
        // std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>,
        // std::chrono::duration<int32_t>,
        // std::chrono::duration<int32_t, std::milli>,
        timestamp<std::chrono::seconds>,
        timestamp<std::chrono::milliseconds>,
        timestamp<std::chrono::microseconds>,
        timestamp<std::chrono::nanoseconds>
        // std::chrono::seconds,
        // std::chrono::milliseconds,
        // std::chrono::microseconds,
        // std::chrono::nanoseconds,
        // std::chrono::months
        // sparrow::day_time_interval,
        // sparrow::month_day_nanoseconds_interval
        >;

    // using date_days_array = timestamp_array<std::chrono::year_month_day>;
    // using date_milliseconds_array = timestamp_array<
    //     std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>>;
    // using time_seconds_array = timestamp_array<std::chrono::duration<int32_t>>;
    // using time_milliseconds_array = timestamp_array<std::chrono::duration<int32_t, std::milli>>;
    // using time_microseconds_array = timestamp_array<std::chrono::microseconds>;
    // using time_nanoseconds_array = timestamp_array<std::chrono::nanoseconds>;
    // using seconds_array = timestamp_array<std::chrono::seconds>;
    // using milliseconds_array = timestamp_array<std::chrono::milliseconds>;
    // using microseconds_array = timestamp_array<std::chrono::microseconds>;
    // using nanoseconds_array = timestamp_array<std::chrono::nanoseconds>;
    // using months_array = timestamp_array<std::chrono::months>;
    // using day_time_interval_array = timestamp_array<day_time_interval>;
    // using month_day_nanoseconds_interval_array = timestamp_array<month_day_nanoseconds_interval>;


    template <typename T>
    struct temporal_traits;

    template <>
    struct temporal_traits<std::chrono::year_month_day>
    {
        using rep = int32_t;
    };

    template <typename T, typename U>
    struct temporal_traits<std::chrono::time_point<T, U>>
    {
        using rep = std::chrono::time_point<T, U>::rep;
    };

    template <typename T>
    struct temporal_traits<std::chrono::hh_mm_ss<T>>
    {
        using rep = std::chrono::hh_mm_ss<T>::precision::rep;
    };

    // static temporal_traits<T>::rep get_integer(const T& value)
    //     {
    //         if constexpr (std::is_same_v<T, std::chrono::year_month_day>)
    //         {
    //             return std::chrono::duration_cast<std::chrono::days>(
    //                        std::chrono::sys_days(value).time_since_epoch()
    //             )
    //                 .count();
    //         }
    //         else if constexpr (std::is_same_v<T, std::chrono::time_point<std::chrono::system_clock,
    //         std::chrono::milliseconds>>)
    //         {
    //             return
    //             std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count();
    //         }
    //         else if constexpr (mpl::is_type_instance_of_v<T, std::chrono::hh_mm_ss>)
    //         {
    //             return static_cast<int32_t>(value.to_duration().count());
    //         }
    //         else if constexpr (mpl::is_type_instance_of_v<T, timestamp>)
    //         {
    //             return value.get_sys_time().time_since_epoch().count();
    //         }
    //         else if constexpr (mpl::is_type_instance_of_v<T, std::chrono::zoned_time>)
    //         {
    //             return value.get_sys_time().time_since_epoch().count();
    //         }
    //         else if constexpr (mpl::is_type_instance_of_v<T, std::chrono::duration>)
    //         {
    //             return value.count();
    //         }
    //         else if constexpr (std::is_same_v<T, day_time_interval>)
    //         {
    //             return {};
    //         }
    //         else if constexpr (std::is_same_v<T, month_day_nanoseconds_interval>)
    //         {
    //             return {};
    //         }
    //         else
    //         {
    //             static_assert(mpl::dependent_false<T, T>::value, "Invalid type");
    //             mpl::unreachable();
    //         }
    //     }

}
