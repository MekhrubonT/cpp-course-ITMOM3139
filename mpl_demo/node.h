#pragma once

struct nil
{};

template <int Data, typename Next>
struct node
{
    static int const data = Data;
    typedef Next next;
};
