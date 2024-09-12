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

#pragma once

#include <cstdint>

#include "sparrow/arrow_interface/arrow_array_schema_utils.hpp"
#include "sparrow/arrow_interface/arrow_schema/private_data.hpp"
#include "sparrow/arrow_interface/arrow_schema/smart_pointers.hpp"

namespace sparrow
{
    /**
     * Creates an ArrowSchema owned by a `unique_ptr` and holding the provided data.
     *
     * @tparam C Value, reference or rvalue of std::vector<arrow_schema_shared_ptr>
     * @param format A mandatory, null-terminated, UTF8-encoded string describing the data type. If the data
     *               type is nested, child types are not encoded here but in the ArrowSchema.children
     *               structures.
     * @param name An optional, null-terminated, UTF8-encoded string of the field or array name.
     *             This is mainly used to reconstruct child fields of nested types.
     * @param metadata An optional, binary string describing the type’s metadata. If the data type
     *                 is nested, the metadata for child types are not encoded here but in the
     * ArrowSchema.children structures.
     * @param flags A bitfield of flags enriching the type description. Its value is computed by OR’ing
     *              together the flag values.
     * @param children Pointers to children. Vector pointer can be null. Children pointers must not be null.
     * @param dictionary Pointer to an ArrowSchema. Must be present if the ArrowSchema represents a
     * dictionary-encoded type. Must be nullptr otherwise.
     * @return The created ArrowSchema unique pointer.
     */
    template <class F, class N, class M>
        requires std::constructible_from<arrow_schema_private_data::FormatType, F>
                 && std::constructible_from<arrow_schema_private_data::NameType, N>
                 && std::constructible_from<arrow_schema_private_data::MetadataType, M>

    [[nodiscard]] arrow_schema_unique_ptr make_arrow_schema_unique_ptr(
        F format,
        N name,
        M metadata,
        std::optional<ArrowFlag> flags,
        int64_t n_children,
        ArrowSchema** children,
        ArrowSchema* dictionary
    );

    template <class F, class N, class M>
        requires std::constructible_from<arrow_schema_private_data::FormatType, F>
                 && std::constructible_from<arrow_schema_private_data::NameType, N>
                 && std::constructible_from<arrow_schema_private_data::MetadataType, M>
    [[nodiscard]] arrow_schema_unique_ptr make_arrow_schema_unique_ptr(
        F format,
        N name,
        M metadata,
        std::optional<ArrowFlag> flags,
        int64_t n_children,
        ArrowSchema** children,
        ArrowSchema* dictionary
    );

    /**
     * Release function to use for the `ArrowSchema.release` member.
     */
    void release_arrow_schema(ArrowSchema* schema);

    /**
     * Creates a default ArrowSchema unique pointer.
     *
     * @return The created ArrowSchema unique pointer.
     */
    arrow_schema_unique_ptr default_arrow_schema_unique_ptr();

    inline void release_arrow_schema(ArrowSchema* schema)
    {
        SPARROW_ASSERT_FALSE(schema == nullptr);
        SPARROW_ASSERT_TRUE(schema->release == std::addressof(release_arrow_schema));

        if (schema->private_data != nullptr)
        {
            const auto private_data = static_cast<arrow_schema_private_data*>(schema->private_data);
            delete private_data;
        }
        release_common_arrow(schema);
        *schema = {};
    }

    /**
     * Creates a unique pointer to an ArrowSchema with default values.
     * All integers are set to 0 and pointers to nullptr.
     * The ArrowSchema is in an invalid state and should not bu used as is.
     *
     * @return The created ArrowSchema.
     */
    inline arrow_schema_unique_ptr default_arrow_schema_unique_ptr()
    {
        return arrow_schema_unique_ptr(new ArrowSchema{});
    }

    template <class F, class N, class M>
        requires std::constructible_from<arrow_schema_private_data::FormatType, F>
                 && std::constructible_from<arrow_schema_private_data::NameType, N>
                 && std::constructible_from<arrow_schema_private_data::MetadataType, M>
    [[nodiscard]] arrow_schema_unique_ptr make_arrow_schema_unique_ptr(
        F format,
        N name,
        M metadata,
        std::optional<ArrowFlag> flags,
        int64_t n_children,
        ArrowSchema** children,
        ArrowSchema* dictionary
    )
    {
        SPARROW_ASSERT_FALSE(format.empty());
        if (children)
        {
            for (int64_t i = 0; i < n_children; ++i)
            {
                SPARROW_ASSERT_FALSE(children[i] == nullptr);
            }
        }

        arrow_schema_unique_ptr schema = default_arrow_schema_unique_ptr();
        schema->flags = flags.has_value() ? static_cast<int64_t>(flags.value()) : 0;
        schema->n_children = n_children;

        schema->private_data = new arrow_schema_private_data(
            std::move(format),
            std::move(name),
            std::move(metadata)
        );

        const auto private_data = static_cast<arrow_schema_private_data*>(schema->private_data);
        schema->format = private_data->format_ptr();
        schema->name = private_data->name_ptr();
        schema->metadata = private_data->metadata_ptr();
        schema->children = children;
        schema->dictionary = dictionary;
        schema->release = release_arrow_schema;
        return schema;
    };
}
