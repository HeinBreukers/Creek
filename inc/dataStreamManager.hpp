#pragma once
#include <tuple>
#include "../ctgl/ctgl.hpp"

template<typename P, typename... StreamTypes>
class DataStreamManager
{
public:
    DataStreamManager(const StreamTypes&... streams ):
    mStreamComponents(streams...)
    {}

    void run()
    {
        using Nodes = typename P::Nodes;
        constexpr auto frontNode = ctgl::list::front(Nodes{});
        constexpr auto adjs = ctgl::graph::getAdjacentNodes(P{},frontNode);
        auto front = std::get<typename decltype(frontNode)::underlying>(mStreamComponents);

        while(1)
        {
            auto val = front->update();

            // todo iterate over list instead of creating tup at runtime
            auto tup = ctgl::rtutil::listToSubTuple(mStreamComponents,ctgl::rtutil::nodeListToList(adjs));

            std::apply
            (
                [&](auto... adjacentNode)
                {
                    ((processNode(ctgl::Node<decltype(adjacentNode)>{}, P{}, val)),...);
                }, tup
            );
        }
    }

    template<typename Node, typename Graph, typename Data>
    void processNode([[maybe_unused]]Node node, [[maybe_unused]] Graph graph, Data input)
    {
        constexpr auto adjs = ctgl::graph::getAdjacentNodes(Graph{},Node{});
        auto n = std::get<typename Node::underlying>(mStreamComponents);
        if constexpr(ctgl::list::size(adjs)>0)
        {
            auto val = n->update(input);
            auto tup = ctgl::rtutil::listToSubTuple(mStreamComponents,ctgl::rtutil::nodeListToList(adjs));

            std::apply
            (
                [&](auto... adjacentNode)
                {
                    ((processNode(ctgl::Node<decltype(adjacentNode)>{}, Graph{}, val)),...);
                }, tup
            );
        }
        else {
            n->update(input);
        }
    }

private:
    std::tuple<StreamTypes...> mStreamComponents;

};

template<typename P, typename... Vars>
auto constructDataStreamManager([[maybe_unused]]P&& program, [[maybe_unused]]Vars&&... vars)
{
    return DataStreamManager<P, Vars...>{std::forward<Vars>(vars)...};
}