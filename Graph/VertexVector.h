#ifndef GAMEFIELDGRAPH_VERTEXVECTOR_H
#define GAMEFIELDGRAPH_VERTEXVECTOR_H

#include "Graph.h"
#include <vector>


namespace Combinatorics
{
    // Wrapper class around vector which can be used with VertexIds
    template <typename T, typename Allocator = std::allocator<T>> class VertexVector : private std::vector<T, Allocator>
    {
        using base = std::vector<T, Allocator>;

    public:
        explicit VertexVector(Graph const &g_, T const &value) : std::vector<T, Allocator>(g_.numVertices(), value)
        {
            base::shrink_to_fit();
        }

        explicit VertexVector(Graph const &g_) : VertexVector(g_, T()){};

        using base::operator=;
        using base::assign;
        using base::back;
        using base::begin;
        using base::cbegin;
        using base::cend;
        using base::crbegin;
        using base::crend;
        using base::empty;
        using base::end;
        using base::front;
        using base::get_allocator;
        using base::rbegin;
        using base::rend;
        using base::size;
        using base::operator[];

        template <VertexId index> inline T &at()
        {
            return base::at(index);
        }

        template <VertexId index> inline T const &at() const
        {
            return base::at(index);
        }

        inline T &operator[](Vertex const &v)
        {
            return this->operator[](v.getId());
        }

        inline T const &operator[](Vertex const &v) const
        {
            return this->operator[](v.getId());
        }
    };

} // namespace Combinatorics

#endif // GAMEFIELDGRAPH_VERTEXVECTOR_H
