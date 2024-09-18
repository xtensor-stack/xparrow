#include <memory>
#include "sparrow_v01/layout/array_base.hpp"
#include "sparrow/arrow_array_schema_proxy.hpp"


#include "sparrow_v01/layout/primitive_array.hpp"
#include "sparrow_v01/layout/list_array.hpp"
#include "sparrow_v01/layout/null_array.hpp"

namespace sparrow
{
    std::unique_ptr<array_base> array_factory(arrow_proxy proxy)
    {
        if(proxy.format().size() == 1)
        {
            switch(proxy.format()[0])
            {
                case 'n':
                    return std::make_unique<null_array>(std::move(proxy));
                case 'b':
                    return std::make_unique<primitive_array<bool>>(std::move(proxy));
                case 'c':
                    return std::make_unique<primitive_array<std::int8_t>>(std::move(proxy));
                case 'C':
                    return std::make_unique<primitive_array<std::uint8_t>>(std::move(proxy));
                case 's':
                    return std::make_unique<primitive_array<std::int16_t>>(std::move(proxy));
                case 'S':
                    return std::make_unique<primitive_array<std::uint16_t>>(std::move(proxy));
                case 'i':
                    return std::make_unique<primitive_array<std::int32_t>>(std::move(proxy));
                case 'I':
                    return std::make_unique<primitive_array<std::uint32_t>>(std::move(proxy));
                case 'l':
                    return std::make_unique<primitive_array<std::int64_t>>(std::move(proxy));
                case 'L':
                    return std::make_unique<primitive_array<std::uint64_t>>(std::move(proxy));
                case 'f':
                    return std::make_unique<primitive_array<float>>(std::move(proxy));
                case 'd':
                    return std::make_unique<primitive_array<double>>(std::move(proxy));
                default:
                    throw std::runtime_error("Unsupported format"); // todo use appropriate exception
                
            }
        }
        else{
            if(proxy.format() == "+l")
            {
                return std::make_unique<list_array>(std::move(proxy));
            }
            else if(proxy.format() == "+L")
            {   
                return std::make_unique<big_list_array>(std::move(proxy));
            }
            else
            {
                throw std::runtime_error("Unsupported format"); // todo use appropriate exception
            } 
        }
    }
    
}