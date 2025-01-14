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

#include "sparrow/utils/chrono.hpp"

#include "doctest/doctest.h"

namespace sparrow
{
    TEST_SUITE("chrono")
    {
        TEST_CASE("to_days_since_the_UNIX_epoch")
        {
            constexpr auto value = std::chrono::year_month_day{
                std::chrono::year{2025},
                std::chrono::month{1},
                std::chrono::day{14}
            };
            constexpr auto result = to_days_since_the_UNIX_epoch(value);
            CHECK_EQ(result, 20102);
        }

        TEST_CASE("from_days_since_the_UNIX_epoch")
        {
            constexpr auto value = 20102;
            constexpr auto result = from_days_since_the_UNIX_epoch(value);
            CHECK_EQ(
                result,
                std::chrono::year_month_day{std::chrono::year{2025}, std::chrono::month{1}, std::chrono::day{14}}
            );
        }

        TEST_CASE("to_milliseconds_since_the_UNIX_epoch")
        {
            constexpr auto value = std::chrono::year_month_day{
                std::chrono::year{2025},
                std::chrono::month{1},
                std::chrono::day{14}
            };
            constexpr int64_t result = to_milliseconds_since_the_UNIX_epoch(value);
            CHECK_EQ(result, 1736812800000);
        }

        TEST_CASE("from_milliseconds_since_the_UNIX_epoch")
        {
            constexpr int64_t value = 1736812800000;
            constexpr auto result = from_milliseconds_since_the_UNIX_epoch(value);
            CHECK_EQ(result.time_since_epoch().count(), value);
        }

        TEST_CASE("to_seconds_since_midnight")
        {
            constexpr std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::ratio<1, 1>>> value{
                std::chrono::hours{1} + std::chrono::minutes{2} + std::chrono::seconds{3}
            };
            constexpr int32_t result = to_seconds_since_midnight(value);
            CHECK_EQ(result, 3723);
        }

        TEST_CASE("from_seconds_since_midnight")
        {
            constexpr int32_t value = 3723;
            constexpr auto result = from_seconds_since_midnight(value);
            CHECK_EQ(result.hours().count(), 1);
            CHECK_EQ(result.minutes().count(), 2);
            CHECK_EQ(result.seconds().count(), 3);
        }

        TEST_CASE("to_milliseconds_since_midnight")
        {
            constexpr auto value = std::chrono::hh_mm_ss<std::chrono::duration<int32_t, std::milli>>{
                std::chrono::hours{1} + std::chrono::minutes{2} + std::chrono::seconds{3}
                + std::chrono::milliseconds{40}
            };
            constexpr int32_t result = to_milliseconds_since_midnight(value);
            CHECK_EQ(result, 3723040);
        }

        TEST_CASE("from_milliseconds_since_midnight")
        {
            constexpr int32_t value = 3723040;
            constexpr auto result = from_milliseconds_since_midnight(value);
            CHECK_EQ(result.hours().count(), 1);
            CHECK_EQ(result.minutes().count(), 2);
            CHECK_EQ(result.seconds().count(), 3);
            CHECK_EQ(result.subseconds().count(), 40);
        }

        TEST_CASE("from_microseconds_since_midnight")
        {
            constexpr int64_t value = 3723040000;
            constexpr auto result = from_microseconds_since_midnight(value);
            CHECK_EQ(result.hours().count(), 1);
            CHECK_EQ(result.minutes().count(), 2);
            CHECK_EQ(result.seconds().count(), 3);
            CHECK_EQ(result.subseconds().count(), 40000);
        }

        TEST_CASE("to_microseconds_since_midnight")
        {
            constexpr auto value = std::chrono::hh_mm_ss<std::chrono::microseconds>{
                std::chrono::hours{1} + std::chrono::minutes{2} + std::chrono::seconds{3}
                + std::chrono::microseconds{4000}
            };
            constexpr int64_t result = to_microseconds_since_midnight(value);
            CHECK_EQ(result, 3723004000);
        }

        TEST_CASE("from_nanoseconds_since_midnight")
        {
            constexpr int64_t value = 3723004000000;
            constexpr auto result = from_nanoseconds_since_midnight(value);
            CHECK_EQ(result.hours().count(), 1);
            CHECK_EQ(result.minutes().count(), 2);
            CHECK_EQ(result.seconds().count(), 3);
            CHECK_EQ(result.subseconds().count(), 4000000);
        }

        TEST_CASE("to_nanoseconds_since_midnight")
        {
            constexpr auto value = std::chrono::hh_mm_ss<std::chrono::nanoseconds>{
                std::chrono::hours{1} + std::chrono::minutes{2} + std::chrono::seconds{3}
                + std::chrono::nanoseconds{4000000}
            };
            constexpr int64_t result = to_nanoseconds_since_midnight(value);
            CHECK_EQ(result, 3723004000000);
        }

        TEST_CASE("to_seconds")
        {
            auto value = timestamp<std::chrono::seconds>{
                "UTC",
                std::chrono::sys_time<std::chrono::seconds>{std::chrono::seconds{3723}}
            };
            const int64_t result = to_seconds(value);
            CHECK_EQ(result, 3723);
        }

        TEST_CASE("from_seconds")
        {
            constexpr int64_t value = 3723;
            const auto result = from_seconds(value, "UTC");
            CHECK_EQ(result.get_sys_time().time_since_epoch().count(), value);
        }

        TEST_CASE("to_milliseconds")
        {
            auto value = timestamp<std::chrono::milliseconds>{
                "UTC",
                std::chrono::sys_time<std::chrono::milliseconds>{std::chrono::milliseconds{3723040}}
            };
            const int64_t result = to_milliseconds(value);
            CHECK_EQ(result, 3723040);
        }

        TEST_CASE("from_milliseconds")
        {
            constexpr int64_t value = 3723040;
            const auto result = from_milliseconds(value, "UTC");
            CHECK_EQ(result.get_sys_time().time_since_epoch().count(), value);
        }

        TEST_CASE("to_microseconds")
        {
            auto value = timestamp<std::chrono::microseconds>{
                "UTC",
                std::chrono::sys_time<std::chrono::microseconds>{std::chrono::microseconds{3723004000}}
            };
            const int64_t result = to_microseconds(value);
            CHECK_EQ(result, 3723004000);
        }

        TEST_CASE("from_microseconds")
        {
            constexpr int64_t value = 3723004000;
            const auto result = from_microseconds(value, "UTC");
            CHECK_EQ(result.get_sys_time().time_since_epoch().count(), value);
        }

        TEST_CASE("to_nanoseconds")
        {
            auto value = timestamp<std::chrono::nanoseconds>{
                "UTC",
                std::chrono::sys_time<std::chrono::nanoseconds>{std::chrono::nanoseconds{3723004000000}}
            };
            const int64_t result = to_nanoseconds(value);
            CHECK_EQ(result, 3723004000000);
        }

        TEST_CASE("from_nanoseconds")
        {
            constexpr int64_t value = 3723004000000;
            const auto result = from_nanoseconds(value, "UTC");
            CHECK_EQ(result.get_sys_time().time_since_epoch().count(), value);
        }

        TEST_CASE("from_seconds_to_duration")
        {
            constexpr int64_t value = 3723;
            const auto result = from_seconds_to_duration(value);
            CHECK_EQ(result.count(), value);
        }

        TEST_CASE("to_seconds_from_duration")
        {
            constexpr auto value = std::chrono::seconds{3723};
            const int64_t result = to_seconds_from_duration(value);
            CHECK_EQ(result, value.count());
        }

        TEST_CASE("from_milliseconds_to_duration")
        {
            constexpr int64_t value = 3723040;
            const auto result = from_milliseconds_to_duration(value);
            CHECK_EQ(result.count(), value);
        }

        TEST_CASE("to_milliseconds_from_duration")
        {
            constexpr auto value = std::chrono::milliseconds{3723040};
            const int64_t result = to_milliseconds_from_duration(value);
            CHECK_EQ(result, value.count());
        }

        TEST_CASE("from_microseconds_to_duration")
        {
            constexpr int64_t value = 3723004000;
            const auto result = from_microseconds_to_duration(value);
            CHECK_EQ(result.count(), value);
        }

        TEST_CASE("to_microseconds_from_duration")
        {
            constexpr auto value = std::chrono::microseconds{3723004000};
            const int64_t result = to_microseconds_from_duration(value);
            CHECK_EQ(result, value.count());
        }

        TEST_CASE("from_nanoseconds_to_duration")
        {
            constexpr int64_t value = 3723004000000;
            const auto result = from_nanoseconds_to_duration(value);
            CHECK_EQ(result.count(), value);
        }

        TEST_CASE("to_nanoseconds_from_duration")
        {
            constexpr auto value = std::chrono::nanoseconds{3723004000000};
            const int64_t result = to_nanoseconds_from_duration(value);
            CHECK_EQ(result, value.count());
        }

        TEST_CASE("from_months_to_duration")
        {
            constexpr int32_t value = 12;
            const auto result = from_months_to_duration(value);
            CHECK_EQ(result.count(), value);
        }

        TEST_CASE("to_months_from_duration")
        {
            constexpr auto value = std::chrono::months{12};
            const int32_t result = to_months_from_duration(value);
            CHECK_EQ(result, value.count());
        }

        TEST_CASE("from_days_milliseconds_to_duration")
        {
            constexpr int32_t days = 1;
            constexpr int32_t milliseconds = 1000;
            const auto result = from_days_milliseconds_to_duration(days, milliseconds);
            CHECK_EQ(result.days.count(), days);
            CHECK_EQ(result.milliseconds.count(), milliseconds);
        }

        TEST_CASE("to_days_milliseconds_from_duration")
        {
            constexpr auto value = day_time_interval{
                .days = std::chrono::days{1},
                .milliseconds = std::chrono::duration<int32_t, std::milli>{1000}
            };
            const auto [days, milliseconds] = to_days_milliseconds_from_duration(value);
            CHECK_EQ(days, value.days.count());
            CHECK_EQ(milliseconds, value.milliseconds.count());
        }

        TEST_CASE("from_months_days_nanoseconds_to_duration")
        {
            constexpr int32_t months = 12;
            constexpr int32_t days = 1;
            constexpr int64_t nanoseconds = 1000;
            const auto result = from_months_days_nanoseconds_to_duration(months, days, nanoseconds);
            CHECK_EQ(result.months.count(), months);
            CHECK_EQ(result.days.count(), days);
            CHECK_EQ(result.nanoseconds.count(), nanoseconds);
        }

        TEST_CASE("to_months_days_nanoseconds_from_duration")
        {
            constexpr auto value = month_day_nanoseconds_interval{
                .months = std::chrono::months{12},
                .days = std::chrono::days{1},
                .nanoseconds = std::chrono::duration<int64_t, std::nano>{1000}
            };
            const auto [months, days, nanoseconds] = to_months_days_nanoseconds_from_duration(value);
            CHECK_EQ(months, value.months.count());
            CHECK_EQ(days, value.days.count());
            CHECK_EQ(nanoseconds, value.nanoseconds.count());
        }
    }
}
