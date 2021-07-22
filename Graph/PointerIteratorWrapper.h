#ifndef HACKATHON_POINTERITERATORWRAPPER_H
#define HACKATHON_POINTERITERATORWRAPPER_H

#include <cstddef>
#include <iterator>
#include <vector>

namespace Combinatorics
{
    // This class is indented to wrap am Container-Iterator consisting of
    // pointer to T (raw ptr or smart ptr). The pointer will be hidden to the user
    // wo can work directly with the reference.
    template <typename T, typename Container, bool Const = true, typename iterator_tag = std::random_access_iterator_tag>
    class PointerIteratorWrapper
    {
        using const_iterator_type = typename Container::const_iterator;
        using iterator_type = typename Container::iterator;
        using wrapped_iterator_type = std::conditional_t<Const, const_iterator_type, iterator_type>;

    public:
        // Previously provided by std::iterator (but deprecated since c++17)
        using value_type = T;
        using difference_type = typename wrapped_iterator_type::difference_type;
        using pointer = std::conditional_t<Const, T const *, T *>;
        using reference = std::conditional_t<Const, T const &, T &>;
        using iterator_category = iterator_tag;

        explicit PointerIteratorWrapper(wrapped_iterator_type wrapped_) : _wrapped(wrapped_)
        {
        }

        PointerIteratorWrapper(PointerIteratorWrapper const &) = default;

        PointerIteratorWrapper &operator=(PointerIteratorWrapper const &other)
        {
            _wrapped = other._wrapped;
            return *this;
        }

        /*
         * Define a const or a non-const operator depending on Const
         */
        template <bool _Const = Const> [[nodiscard]] std::enable_if_t<_Const, reference> operator*() const
        {
            return *(*_wrapped);
        }

        template <bool _Const = Const> [[nodiscard]] std::enable_if_t<!_Const, reference> operator*()
        {
            return *(*_wrapped);
        }

        template <bool _Const = Const> [[nodiscard]] std::enable_if_t<_Const, pointer> operator->() const
        {
            return *_wrapped;
        }

        template <bool _Const = Const> [[nodiscard]] std::enable_if_t<!_Const, pointer> operator->()
        {
            return *_wrapped;
        }

        PointerIteratorWrapper &operator++()
        {
            ++_wrapped;
            return *this;
        }

        PointerIteratorWrapper &operator--()
        {
            --_wrapped;
            return *this;
        }

        PointerIteratorWrapper operator+(difference_type const &n) const
        {
            return PointerIteratorWrapper(_wrapped + n);
        }

        PointerIteratorWrapper operator-(difference_type const &n) const
        {
            return PointerIteratorWrapper(_wrapped - n);
        }

        PointerIteratorWrapper &operator+=(const difference_type &n)
        {
            _wrapped += n;
            return *this;
        }

        PointerIteratorWrapper &operator-=(const difference_type &n)
        {
            _wrapped -= n;
            return *this;
        }

        [[nodiscard]] reference operator[](difference_type const &n)
        {
            return *(*_wrapped[n]);
        }

        [[nodiscard]] bool operator==(PointerIteratorWrapper const &other) const
        {
            return _wrapped == other._wrapped;
        }

        [[nodiscard]] bool operator!=(PointerIteratorWrapper const &other) const
        {
            return _wrapped != other._wrapped;
        }

        [[nodiscard]] bool operator<(PointerIteratorWrapper const &other) const
        {
            return _wrapped < other._wrapped;
        }

        [[nodiscard]] bool operator>(PointerIteratorWrapper const &other) const
        {
            return _wrapped > other._wrapped;
        }

        [[nodiscard]] bool operator<=(PointerIteratorWrapper const &other) const
        {
            return _wrapped <= other._wrapped;
        }

        [[nodiscard]] bool operator>=(PointerIteratorWrapper const &other) const
        {
            return _wrapped >= other._wrapped;
        }

        difference_type operator+(const PointerIteratorWrapper &other) const
        {
            return _wrapped + other._wrapped;
        }

        difference_type operator-(const PointerIteratorWrapper &other) const
        {
            return _wrapped - other._wrapped;
        }

    private:
        wrapped_iterator_type _wrapped;
    };
} // namespace Combinatorics

#endif // HACKATHON_POINTERITERATORWRAPPER_H
