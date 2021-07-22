#ifndef HACKATHON_SIMPLERANGE_H
#define HACKATHON_SIMPLERANGE_H

namespace Combinatorics
{
    template <typename iterator_type> class SimpleRange
    {
    public:
        SimpleRange(iterator_type begin_, iterator_type end_) : _begin(begin_), _end(end_){};
        [[nodiscard]] iterator_type begin() const
        {
            return _begin;
        }
        [[nodiscard]] iterator_type end() const
        {
            return _end;
        }

    private:
        iterator_type _begin;
        iterator_type _end;
    };
} // namespace Combinatorics

#endif // HACKATHON_SIMPLERANGE_H
