#pragma once
#include <tuple>
#include "../CompileTimeGraph/ctgl.hpp"

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
            const auto val = front->update();

            ctgl::rtutil::transformList( 
                [&]<typename AdjacentNode>()
                {
                    processNode(ctgl::Node<AdjacentNode>{}, P{}, val);
                },
                ctgl::rtutil::nodeListToList(adjs)
            );
        }
    }

    template<typename Node, typename Graph, typename Data>
    void processNode([[maybe_unused]]Node node, [[maybe_unused]] Graph graph, Data&& input)
    {
        constexpr auto adjs = ctgl::graph::getAdjacentNodes(Graph{},Node{});
        auto stream = std::get<typename Node::underlying>(mStreamComponents);
        if constexpr(ctgl::list::size(adjs)>0)
        {
            const auto val = stream->update(std::forward<Data>(input));

            ctgl::rtutil::transformList( 
                [&]<typename AdjacentNode>()
                {
                    processNode(ctgl::Node<AdjacentNode>{}, Graph{}, val);
                },
                ctgl::rtutil::nodeListToList(adjs)
            );
        }
        else 
        {
            stream->update(std::forward<Data>(input));
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