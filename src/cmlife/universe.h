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

    int lastPosition() const
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
        newU.position = u.lastPosition() - 1;
    return newU;
}

template <typename T> Universe<T>
right(const Universe<T>& u)
{
    Universe<T> newU { u.field, u.position + 1 };
    if (u.position == u.lastPosition() - 1)
        newU.position = 0;
    return newU;
}

// TODO: functions tail, iterate...
template <typename T> std::vector<T>
tailOfGen(int count,
    const std::function<Universe<T>(Universe<T>)>& generator,
    Universe<T> item)
{
    std::vector<T> items;
    items.reserve(count);

    item = generator(item);
    for (int i = 0; i < count; ++i)
    {
        item = generator(item);
        items.push_back(item);
    }
    return items;
}

template <typename T> Universe<T>
makeUniverse(const std::function<Universe<T>(Universe<T>)>& leftCreator,
    const std::function<Universe<T>(Universe<T>)>& rightCreator,
    const Universe<T>& u)
{
    std::vector<T> all = std::vector<T>();

    if (u.position > 0)
        all.swap(tailOfGen(u.position, leftCreator, u));

    all.push_back(u);

    // TODO: optimize it.
    auto rights = tailOfGen(u.position, rightCreator, u);

    if (u.position < u.lastPosition() - 1)
        all.insert(all.end(), rights.begin(), rights.end());

    Universe<T> newU { all, u.position };
    return newU;
}



} // namespace cmlife


#endif // UNIVERSE_H
