#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <functional>

namespace cmlife
{

template <typename T>
struct Universe
{
    std::vector<T> field;
    int position;

    int size() const
    {
        return field.size();
    }
};

struct Universe2
{
    Universe<Universe<char>> field2;
};

template <typename T> Universe<T>
left(const Universe<T>& u)
{
    Universe<T> newU { u.field, u.position - 1 };
    if (u.position == 0)
        newU.position = u.size() - 1;
    return newU;
}

template <typename T> Universe<T>
right(const Universe<T>& u)
{
    Universe<T> newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}

// TODO: functions tail, iterate...
template <typename T> std::vector<Universe<T>>
tailOfGen(int count,
    const std::function<Universe<T>(Universe<T>)>& generator,
    Universe<T> item)
{
    std::vector<Universe<T>> items;
    items.reserve(count);

    auto it = generator(item);
    for (int i = 0; i < count; ++i)
    {
        items.push_back(it);
        it = generator(it);
    }
    return items;
}

// TODO: it's functional and imperative code mix.
template <typename T> Universe<Universe<T>>
makeUniverse(const std::function<Universe<T>(Universe<T>)>& leftCreator,
    const std::function<Universe<T>(Universe<T>)>& rightCreator,
    const Universe<T>& u)
{
    std::vector<Universe<T>> all = std::vector<Universe<T>>();
    all.reserve(u.size());

    // TODO: optimize it.
    if (u.position > 0)
    {
        auto lefts = tailOfGen(u.position, leftCreator, u);
        all.insert(all.end(), lefts.begin(), lefts.end());
    }

    all.push_back(u);

    // TODO: optimize it.
    if (u.position < u.size() - 1)
    {
        auto rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);
        all.insert(all.end(), rights.begin(), rights.end());
    }

    Universe<Universe<T>> newU { all, u.position };
    return newU;
}



} // namespace cmlife


#endif // UNIVERSE_H
