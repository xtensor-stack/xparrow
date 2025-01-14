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

#include <chrono>
#include <cstdint>
#include <ratio>

#include "sparrow/types/data_type.hpp"

namespace sparrow
{

    constexpr int32_t to_days_since_the_UNIX_epoch(const auto& value)
    {
        const auto duration = std::chrono::sys_days(value).time_since_epoch();
        return std::chrono::duration_cast<std::chrono::days>(duration).count();
    }

    constexpr std::chrono::year_month_day from_days_since_the_UNIX_epoch(const int32_t days)
    {
        return std::chrono::year_month_day{std::chrono::sys_days{std::chrono::days{days}}};
    }

    constexpr int64_t to_milliseconds_since_the_UNIX_epoch(const auto& value)
    {
        const auto duration = std::chrono::sys_days(value).time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    constexpr std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>
    from_milliseconds_since_the_UNIX_epoch(const int64_t milliseconds)
    {
        return std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>{
            std::chrono::milliseconds{milliseconds}
        };
    }

    constexpr int32_t
    to_seconds_since_midnight(const std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::ratio<1, 1>>>& value)
    {
        return static_cast<int32_t>(value.to_duration().count());
    }

    constexpr std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::ratio<1, 1>>>
    from_seconds_since_midnight(const int32_t seconds)
    {
        return std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::ratio<1, 1>>>{
            std::chrono::seconds{seconds}
        };
    }

    constexpr int32_t
    to_milliseconds_since_midnight(const std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::milli>>& value)
    {
        return static_cast<int32_t>(value.to_duration().count());
    }

    constexpr std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::milli>>
    from_milliseconds_since_midnight(const int32_t milliseconds)
    {
        return std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::milli>>{
            std::chrono::milliseconds{milliseconds}
        };
    }

    constexpr std::chrono::hh_mm_ss<std::chrono::microseconds>
    from_microseconds_since_midnight(const int64_t microseconds)
    {
        return std::chrono::hh_mm_ss<std::chrono::microseconds>{std::chrono::microseconds{microseconds}};
    }

    constexpr int64_t
    to_microseconds_since_midnight(const std::chrono::hh_mm_ss<std::chrono::microseconds>& value)
    {
        return value.to_duration().count();
    }

    constexpr std::chrono::hh_mm_ss<std::chrono::nanoseconds>
    from_nanoseconds_since_midnight(const int64_t nanoseconds)
    {
        return std::chrono::hh_mm_ss<std::chrono::nanoseconds>{std::chrono::nanoseconds{nanoseconds}};
    }

    constexpr int64_t
    to_nanoseconds_since_midnight(const std::chrono::hh_mm_ss<std::chrono::nanoseconds>& value)
    {
        return value.to_duration().count();
    }

    int64_t to_seconds(timestamp<std::chrono::seconds> value)
    {
        return value.get_sys_time().time_since_epoch().count();
    }

    timestamp<std::chrono::seconds> from_seconds(int64_t seconds, std::string_view timezone)
    {
        const auto sys_time = std::chrono::sys_time<std::chrono::seconds>{std::chrono::seconds{seconds}};
        return timestamp<std::chrono::seconds>{timezone, sys_time};
    }

    int64_t to_milliseconds(timestamp<std::chrono::milliseconds> value)
    {
        return value.get_sys_time().time_since_epoch().count();
    }

    timestamp<std::chrono::milliseconds> from_milliseconds(int64_t milliseconds, std::string_view timezone)
    {
        const auto sys_time = std::chrono::sys_time<std::chrono::milliseconds>{
            std::chrono::milliseconds{milliseconds}
        };
        return timestamp<std::chrono::milliseconds>{timezone, sys_time};
    }

    int64_t to_microseconds(timestamp<std::chrono::microseconds> value)
    {
        return value.get_sys_time().time_since_epoch().count();
    }

    timestamp<std::chrono::microseconds> from_microseconds(int64_t microseconds, std::string_view timezone)
    {
        const auto sys_time = std::chrono::sys_time<std::chrono::microseconds>{
            std::chrono::microseconds{microseconds}
        };
        return timestamp<std::chrono::microseconds>{timezone, sys_time};
    }

    int64_t to_nanoseconds(timestamp<std::chrono::nanoseconds> value)
    {
        return value.get_sys_time().time_since_epoch().count();
    }

    timestamp<std::chrono::nanoseconds> from_nanoseconds(int64_t nanoseconds, std::string_view timezone)
    {
        const auto sys_time = std::chrono::sys_time<std::chrono::nanoseconds>{
            std::chrono::nanoseconds{nanoseconds}
        };
        return timestamp<std::chrono::nanoseconds>{timezone, sys_time};
    }

    constexpr std::chrono::seconds from_seconds_to_duration(int64_t value)
    {
        return std::chrono::seconds{value};
    }

    constexpr int64_t to_seconds_from_duration(std::chrono::seconds value)
    {
        return value.count();
    }

    constexpr std::chrono::milliseconds from_milliseconds_to_duration(int64_t value)
    {
        return std::chrono::milliseconds{value};
    }

    constexpr int64_t to_milliseconds_from_duration(std::chrono::milliseconds value)
    {
        return value.count();
    }

    constexpr std::chrono::microseconds from_microseconds_to_duration(int64_t value)
    {
        return std::chrono::microseconds{value};
    }

    constexpr int64_t to_microseconds_from_duration(std::chrono::microseconds value)
    {
        return value.count();
    }

    constexpr std::chrono::nanoseconds from_nanoseconds_to_duration(int64_t value)
    {
        return std::chrono::nanoseconds{value};
    }

    constexpr int64_t to_nanoseconds_from_duration(std::chrono::nanoseconds value)
    {
        return value.count();
    }

    constexpr std::chrono::months from_months_to_duration(int32_t value)
    {
        return std::chrono::months{value};
    }

    constexpr int32_t to_months_from_duration(std::chrono::months value)
    {
        return value.count();
    }

    struct day_time_interval
    {
        std::chrono::days days;
        std::chrono::duration<int32_t, std::milli> milliseconds;
    };

    constexpr day_time_interval from_days_milliseconds_to_duration(int32_t days, int32_t milliseconds)
    {
        return day_time_interval{
            .days = std::chrono::days{days},
            .milliseconds = std::chrono::duration<int32_t, std::milli>{milliseconds}
        };
    }

    constexpr std::pair<int32_t, int32_t> to_days_milliseconds_from_duration(const day_time_interval& value)
    {
        return {value.days.count(), value.milliseconds.count()};
    }

    struct month_day_nanoseconds_interval
    {
        std::chrono::months months;
        std::chrono::days days;
        std::chrono::duration<int64_t, std::nano> nanoseconds;
    };

    constexpr month_day_nanoseconds_interval
    from_months_days_nanoseconds_to_duration(int32_t months, int32_t days, int64_t nanoseconds)
    {
        return month_day_nanoseconds_interval{
            .months = std::chrono::months{months},
            .days = std::chrono::days{days},
            .nanoseconds = std::chrono::duration<int64_t, std::nano>{nanoseconds}
        };
    }

    constexpr std::tuple<int32_t, int32_t, int64_t>
    to_months_days_nanoseconds_from_duration(const month_day_nanoseconds_interval& value)
    {
        return {value.months.count(), value.days.count(), value.nanoseconds.count()};
    }
}  // namespace sparrow
