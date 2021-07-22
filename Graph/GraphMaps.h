#include "Graph.h"
#include <functional>
#include <map>


#ifndef GAMEFIELDGRAPH_GRAPHMAPS_H
#define GAMEFIELDGRAPH_GRAPHMAPS_H

namespace Combinatorics
{

    template <typename ClassWithId, typename T, typename Compare = std::less<size_t>,
              typename Allocator = std::allocator<std::pair<const size_t, T>>>
    class IdMap : private std::map<size_t, T, Compare, Allocator>
    {
    public:
        using underlying_map = std::map<size_t, T, Compare, Allocator>;
        class Iterator : private underlying_map::iterator
        {
            using underlying_it = typename underlying_map::iterator;

        public:
            Iterator(IdMap &idMap_, underlying_it it) : underlying_it(it), _idMap(idMap_)
            {
            }
            using underlying_it::operator!=;
            using underlying_it::operator++;
            using underlying_it::operator--;
            using underlying_it::operator==;
            [[nodiscard]] std::pair<std::reference_wrapper<ClassWithId>, T> operator*()
            {
                auto underlying = underlying_it::operator*();
                return std::make_pair(std::ref(_idMap.getObjectFromId(underlying.first)), underlying.second);
            }
            [[nodiscard]] std::unique_ptr<std::pair<std::reference_wrapper<ClassWithId>, T>> operator->()
            {
                return std::make_unique(operator*());
            }

        private:
            IdMap &_idMap;
        };

        template <typename... MapArgs>
        IdMap(Graph &graph_, MapArgs &&...args) : underlying_map(std::forward<MapArgs>(args)...), _graph(graph_)
        {
        }

        // Make untouched map methods available
        using underlying_map::clear;
        using underlying_map::empty;
        using underlying_map::max_size;
        using underlying_map::size;

        [[nodiscard]] T &at(ClassWithId const &key_class)
        {
            return underlying_map::at(key_class.getId());
        }

        [[nodiscard]] T const &at(ClassWithId const &key_class) const
        {
            return underlying_map::at(key_class.getId());
        }

        [[nodiscard]] T &operator[](ClassWithId const &key_class)
        {
            return underlying_map::operator[](key_class.getId());
        }

        [[nodiscard]] Iterator begin()
        {
            return Iterator(underlying_map::begin());
        }

        [[nodiscard]] Iterator end()
        {
            return Iterator(underlying_map::begin());
        }

        // Must be filled by actual implementations
        virtual ClassWithId &getObjectFromId(size_t id) = 0;
        virtual ClassWithId const &getObjectFromId(size_t id) const = 0;

    protected:
        Graph &_graph;
    };

    template <typename T, typename Compare = std::less<size_t>,
              typename Allocator = std::allocator<std::pair<const size_t, T>>>
    class VertexMap : public IdMap<Vertex, T, Compare, Allocator>
    {
    public:
        using base = IdMap<Vertex, T, Compare, Allocator>;
        using base::base;
        [[nodiscard]] Vertex &getObjectFromId(size_t id)
        {
            return IdMap<Vertex, T, Compare, Allocator>::_graph.getVertex(id);
        }
        [[nodiscard]] Vertex const &getObjectFromId(size_t id) const
        {
            return IdMap<Vertex, T, Compare, Allocator>::_graph.getVertex(id);
        }
    };

    template <typename T, typename Compare = std::less<size_t>,
              typename Allocator = std::allocator<std::pair<const size_t, T>>>
    class EdgeMap : public IdMap<Vertex, T, Compare, Allocator>
    {
    public:
        using base = IdMap<Edge, T, Compare, Allocator>;
        using base::base;
        [[nodiscard]] Edge &getObjectFromId(size_t id)
        {
            return base::_graph.getVertex(id);
        }
        [[nodiscard]] Edge const &getObjectFromId(size_t id) const
        {
            return IdMap<Vertex, T, Compare, Allocator>::_graph.getVertex(id);
        }
    };

} // namespace Combinatorics

#endif // GAMEFIELDGRAPH_GRAPHMAPS_H
