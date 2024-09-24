#include <iostream>
#include "dataStream.hpp"
#include "dataStreamManager.hpp"

#include <thread>
#include <chrono>

using namespace hbreukers;


int main()
{
    // TODO, statefull processing
    auto source = makeSource([]()
        {
            static int i =0;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return i++;
        });

    auto stream = source.addDataStream<int>()
        .process([](auto&& in){return in+5;});
    auto stream2 = source.addDataStream<int>()
        .process([](auto&& in){return in*3;});
    auto sink = stream.addDataSink([](auto&& in){std::cout<<in<<'\n';});
    auto sink2 = stream2.addDataSink([](auto&& in){std::cout<<in<<'\n';});


    using t1 = ctgl::Node<decltype(&source)>;
    using t2 = ctgl::Node<decltype(&stream)>;
    using t3 = ctgl::Node<decltype(&stream2)>;
    using t4 = ctgl::Node<decltype(&sink)>;
    using t5 = ctgl::Node<decltype(&sink2)>;

    using tasks = ctgl::List<t1, t2, t3, t4>;

    using routes = ctgl::List<ctgl::Edge<t1, t2, 1>,
                              ctgl::Edge<t1, t3, 1>,
                              ctgl::Edge<t2, t4, 1>,
                              ctgl::Edge<t3, t5, 1>>;
    using program = ctgl::Graph<tasks, routes>;


    // TODO BFS vs DFS (currently DFS)
    // TODO concurrent execution
    // TODO think about storing by value instead of by pointer
    // TODO add concepts / customization points
    auto manager = constructDataStreamManager(program{}, &source,&stream,&stream2,&sink,&sink2);

    manager.run();
    return 0;
}