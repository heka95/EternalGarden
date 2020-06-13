#if !defined(__SIZE__)
#define __SIZE__

#include <iostream>

namespace Garden
{
    struct Size
    {
        int width = 0;
        int height = 0;
    };

    inline std::ostream &operator<<(std::ostream &os, const Size &size)
    {
        os << size.width << "x" << size.height;
        return os;
    }

} // namespace Garden

#endif