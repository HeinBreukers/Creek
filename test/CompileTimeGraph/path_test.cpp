#include <gtest/gtest.h>

#include "../../include/CompileTimeGraph/path.hpp"
#include "forge.hpp"

using namespace ctgl;
using namespace forge;

// Unit tests for the ctgl::path::length() function.
TEST(PathTest, Length) {
    // Empty
    EXPECT_EQ(path::length(Path<>{}), 0);

    // Single
    EXPECT_EQ(path::length(Path<E11>{}), 1);
    EXPECT_EQ(path::length(Path<E12>{}), 2);

    // Multiple
    EXPECT_EQ(path::length(Path<E11, E11>{}), 2);
    EXPECT_EQ(path::length(Path<E11, E12>{}), 3);
    EXPECT_EQ(path::length(Path<E12, E11>{}), 3);
    EXPECT_EQ(path::length(Path<E11, E21, E31, E41>{}), 10);
}

// Unit tests for the ctgl::path::nodes() function.
TEST(PathTest, Nodes) {
    // Empty
    EXPECT_EQ(path::nodes(Path<>{}), List<>{});

    // Single
    EXPECT_EQ(path::nodes(Path<E11>{}), List<N1>{});
    EXPECT_EQ(path::nodes(Path<E11, E11>{}), List<N1>{});

    // Multiple
    EXPECT_EQ(path::nodes(Path<E12>{}), (List<N1, N2>{}));
    EXPECT_EQ(path::nodes(Path<E21>{}), (List<N2, N1>{}));
    EXPECT_EQ(path::nodes(Path<E12, E23>{}), (List<N1, N2, N3>{}));
}

// Unit tests for the ctgl::path::dropPrefix() function.
TEST(PathTest, DropPrefix) {
    // Empty
    EXPECT_EQ(path::dropPrefix(N1{}, Path<>{}), Path<>{});

    // Single
    EXPECT_EQ(path::dropPrefix(N1{}, Path<E23>{}), Path<>{});
    EXPECT_EQ(path::dropPrefix(N2{}, Path<E23>{}), Path<E23>{});
    EXPECT_EQ(path::dropPrefix(N3{}, Path<E23>{}), Path<>{});

    // Multiple
    EXPECT_EQ(path::dropPrefix(N1{}, Path<E23, E34>{}), Path<>{});
    EXPECT_EQ(path::dropPrefix(N2{}, Path<E12, E23>{}), Path<E23>{});
    EXPECT_EQ(path::dropPrefix(N3{}, Path<E34, E41>{}), (Path<E34, E41>{}));
    EXPECT_EQ(path::dropPrefix(N4{}, Path<E34, E41, E23>{}), (Path<E41, E23>{}));
}

// Unit tests for the ctgl::path::join() function.
TEST(PathTest, Join) {
    // DNE
    EXPECT_EQ(path::join(path::DNE, path::DNE), path::DNE);
    EXPECT_EQ(path::join(Path<E11>{}, path::DNE), path::DNE);
    EXPECT_EQ(path::join(path::DNE, Path<E11>{}), path::DNE);

    // Exists
    EXPECT_EQ(path::join(Path<E12>{}, Path<E23>{}), (Path<E12, E23>{}));
    EXPECT_EQ(path::join(Path<E12>{}, Path<E12>{}), (Path<E12, E12>{}));
    EXPECT_EQ(path::join(Path<E12, E23>{}, Path<E32, E21>{}), (Path<E12, E23, E32, E21>{}));
}

// Unit tests for the ctgl::path::shortest() function.
TEST(PathTest, Shortest) {
    // DNE
    EXPECT_EQ(path::shortest(path::DNE, path::DNE), path::DNE);
    EXPECT_EQ(path::shortest(Path<E11>{}, path::DNE), Path<E11>{});
    EXPECT_EQ(path::shortest(path::DNE, Path<E11>{}), Path<E11>{});

    // Exists
    EXPECT_EQ(path::shortest(Path<E12>{}, Path<E12>{}), Path<E12>{});
    EXPECT_EQ(path::shortest(Path<E12>{}, Path<E13>{}), Path<E12>{});
    EXPECT_EQ(path::shortest(Path<E13>{}, Path<E12>{}), Path<E12>{});
    EXPECT_EQ(path::shortest(Path<E11, E11>{}, Path<E14>{}), (Path<E11, E11>{}));
    EXPECT_EQ(path::shortest(Path<E14>{}, Path<E11, E11>{}), (Path<E11, E11>{}));
}