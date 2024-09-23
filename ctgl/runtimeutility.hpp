#pragma once
#include "list.hpp"
#include "graph.hpp"

#include <tuple>
// Types
// -----------------------------------------------------------------------------
namespace ctgl {
    namespace rtutil {
        
        template<typename... ListTypes>
        constexpr auto nodeListToList([[maybe_unused]]ctgl::List<ctgl::Node<ListTypes>...> listOfNodes)
        {
            return ctgl::list::List<ListTypes...>{};
        }

        template<typename... ListTypes, typename... L2, int... I>
        constexpr auto edgeListToTailList([[maybe_unused]]ctgl::List<ctgl::Edge<ctgl::Node<ListTypes>,ctgl::Node<L2>,I>...> listOfEdges)
        {
            return ctgl::list::List<ListTypes...>{};
        }

        template<typename TupleType, typename F, typename... ListTypes>
        constexpr auto listToSubTuple(TupleType tupleOfAllTypes, ctgl::List<F,ListTypes...> listOfDesiredTypes)
        {
            if constexpr(ctgl::list::size(listOfDesiredTypes)==1)
            {
                return std::tuple<F>(std::get<F>(tupleOfAllTypes));
            }
            else
            {
                using LT = ctgl::List<ListTypes...>;
                return std::tuple_cat(std::tuple<F>(std::get<F>(tupleOfAllTypes)), listToSubTuple(tupleOfAllTypes, LT{}));
            }
        }

     
    }
}