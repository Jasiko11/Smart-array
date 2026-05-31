
#include <gtest/gtest.h>

#include "../include/SmartArray/SmartArray.h"

#include <array>


// ------------------ Initialize ---------------------------------

TEST(InitializeVector, initializeWithConstructor_empty)
{
    SmartArray<int> v;
    ASSERT_EQ(v.size(), 0);
    ASSERT_GE(v.capacity(), 0);
    int test = 5;
}

TEST(InitializeVector, initializeWithConstructor_p100)
{
    SmartArray<int> v(100);
    ASSERT_GE(v.capacity(), 100);
    ASSERT_EQ(v.size(), 0);
}

// ------------------ Push back and access ---------------------------------

TEST(AddElementsAndAccess, addElementsAndAccess_operator)
{
    SmartArray<int> v;
    v.pushBack(88);
    ASSERT_EQ(v[0], 88);
    ASSERT_EQ(v.size(), 1);
}

TEST(AddElementsAndAccess, addElementsAndAccess_at)
{
    SmartArray<int> v;
    v.pushBack(88);
    ASSERT_EQ(v.at(0), 88);
    ASSERT_EQ(v.size(), 1);
}

// ---------------- Clear -----------------

TEST(Clear, empty)
{
    SmartArray<int> v;
    v.clear();
    ASSERT_EQ(v.size(), 0);
}