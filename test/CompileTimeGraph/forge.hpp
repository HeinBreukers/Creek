#pragma once

#include "../../include/CompileTimeGraph/graph.hpp"

using namespace ctgl;

template <int ID>
class Id
{
    static constexpr int id = ID;
};




namespace forge {
    // Nodes
    // -------------------------------------------------------------------------
    using N1 = Node<Id<1>>;
    using N2 = Node<Id<2>>;
    using N3 = Node<Id<3>>;
    using N4 = Node<Id<4>>;
    using N5 = Node<Id<5>>;
    using N6 = Node<Id<6>>;
    using N7 = Node<Id<7>>;

    // Edges
    // -------------------------------------------------------------------------
    using E11 = Edge<N1, N1, 1>;
    using E12 = Edge<N1, N2, 2>;
    using E13 = Edge<N1, N3, 3>;
    using E14 = Edge<N1, N4, 4>;

    using E21 = Edge<N2, N1, 4>;
    using E22 = Edge<N2, N2, 1>;
    using E23 = Edge<N2, N3, 2>;
    using E24 = Edge<N2, N4, 3>;

    using E31 = Edge<N3, N1, 3>;
    using E32 = Edge<N3, N2, 4>;
    using E33 = Edge<N3, N3, 1>;
    using E34 = Edge<N3, N4, 2>;

    using E41 = Edge<N4, N1, 2>;
    using E42 = Edge<N4, N2, 3>;
    using E43 = Edge<N4, N3, 4>;
    using E44 = Edge<N4, N4, 1>;

    using E56 = Edge<N5, N6, 3>;
    using E57 = Edge<N5, N7, 1>;
    using E65 = Edge<N6, N5, 3>;
    using E76 = Edge<N7, N6, 1>;

    using NE11 = Edge<N1, N1, -1>;
    using NE12 = Edge<N1, N2, -2>;
    using NE13 = Edge<N1, N3, -3>;
    using NE14 = Edge<N1, N4, -4>;

    using NE21 = Edge<N2, N1, -4>;
    using NE22 = Edge<N2, N2, -1>;
    using NE23 = Edge<N2, N3, -2>;
    using NE24 = Edge<N2, N4, -3>;

    using NE31 = Edge<N3, N1, -3>;
    using NE32 = Edge<N3, N2, -4>;
    using NE33 = Edge<N3, N3, -1>;
    using NE34 = Edge<N3, N4, -2>;

    using NE41 = Edge<N4, N1, -2>;
    using NE42 = Edge<N4, N2, -3>;
    using NE43 = Edge<N4, N3, -4>;
    using NE44 = Edge<N4, N4, -1>;

    using NE56 = Edge<N5, N6, -2>;
    using NE65 = Edge<N6, N5, -2>;

    // Graphs
    // -------------------------------------------------------------------------
    using Empty = Graph<List<>, List<>>;

    // (N1)
    using Island = Graph<List<N1>, List<>>;

    //  v----.
    // (N1) -'
    using Loopback = Graph<List<N1>, List<E11>>;

    // (N1) --> (N2)
    using Arrow = Graph<List<N1, N2>, List<E12>>;

    // (N1) --v
    //  ^--- (N2)
    using Bridge = Graph<List<N1, N2>, List<E12, E21>>;

    // (N1) --> (N2) --> (N3)
    //  '-----------------^
    using Leap = Graph<List<N1, N2, N3>, List<E12, E23, E13>>;

    // (N1) -----> (N2)
    //  ^-- (N3) <--'
    using Triangle = Graph<List<N1, N2, N3>, List<E12, E23, E31>>;

    // (N1) ------> (N2) --> (N3)
    //  '--> (N4) ---^
    using Pan = Graph<List<N1, N2, N3, N4>, List<E12, E23, E14, E42>>;

    // (N5) ------> (N6)
    //  '--> (N7) ---^
    using Bow = Graph<List<N5, N6, N7>, List<E56, E57, E76>>;

    // (N1) --> (N2) --> (N3) <-- (N4)
    //  ^-----------------'
    using Dipper = Graph<List<N1, N2, N3, N4>, List<E12, E23, E31, E43>>;

    // Graphs with Negative Cycles
    // -------------------------------------------------------------------------

    //  v----.
    // (N1) -'
    using Alone = Graph<List<N1>, List<NE11>>;

    // (N1) --v
    //  ^--- (N2)
    using Debate = Graph<List<N1, N2>, List<NE12, NE21>>;

    // (N1) -----> (N2)
    //  ^-- (N3) <--'
    using Spiral = Graph<List<N1, N2, N3>, List<NE12, NE23, NE31>>;

    // (N1) --> (N2) -----> (N3)
    //           ^-- (N4) <--'
    using Hole = Graph<List<N1, N2, N3, N4>, List<E12, E23, NE34, NE42>>;

    //  v========,
    // (N5)     (N6)
    //  ^========'
    using Magnet = Graph<List<N5, N6>, List<E56, E65, NE56, NE65>>;
}