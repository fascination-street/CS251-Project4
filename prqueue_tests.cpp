#include "prqueue.h"

#include "gtest/gtest.h"

using namespace std;

TEST(DefaultConstructor, Test) {
    prqueue<int> pq;

    EXPECT_EQ(nullptr, pq.getRoot()) << "Default constructor did not set root to nullptr\n";
    EXPECT_EQ(0, pq.size()) << "Size was not set to 0\n";
}

//
// enqueue tests
//

TEST(Enqueue, EmptyTree) {
    prqueue<string> test;

    test.enqueue("First", 1);

    EXPECT_NE(nullptr, test.getRoot()) << "root is null\n";
}

TEST(Enqueue, NormalEnqueue) {
    prqueue<int> test;

    test.enqueue(12, 4);
    test.enqueue(13, 2);
    test.enqueue(14, 5);
    test.enqueue(15, 1);

    EXPECT_EQ(4, test.size()) << "size of test is not 4\n";
    EXPECT_EQ(15, test.dequeue()) << "highest priority is not 15\n";
    EXPECT_EQ(13, test.dequeue()) << "next highest priority is not 13\n";
    EXPECT_EQ(12, test.dequeue()) << "next highest priority is not 12\n";
    EXPECT_EQ(14, test.dequeue()) << "lowest priority is not 14\n";
    
}

TEST(Enqueue, DupeRoot) {
    prqueue<string> test;

    test.enqueue("kyle", 3);
    test.enqueue("tyler", 3);
    test.enqueue("jason", 4);

    EXPECT_EQ(3, test.size()) << "size is not correct\n";
    EXPECT_EQ("kyle", test.dequeue()) << "kyle was not the first dequeue\n";
    EXPECT_EQ("tyler", test.dequeue()) << "tyler was not the second dequeue\n";
}

TEST(Enqueue, ManyDupes) {
    prqueue<string> test;

    test.enqueue("win", 3);
    test.enqueue("frank", 2);
    test.enqueue("carl", 4);
    test.enqueue("chris", 2);
    test.enqueue("harold", 1);
    test.enqueue("gary", 4);
    test.enqueue("kerry", 2);

    EXPECT_EQ(7, test.size()) << "size is not correct\n";
    EXPECT_EQ("harold", test.dequeue()) << "harold was not dequeued first\n";
    EXPECT_EQ("frank", test.dequeue()) << "frank was not dequeued second\n";
    EXPECT_EQ("chris", test.dequeue()) << "chris was not dequeued third\n";
    EXPECT_EQ("kerry", test.dequeue()) << "kerry was not dequeued fourth\n";
    EXPECT_EQ("win", test.dequeue()) << "win was not dequeued fifth\n";
    EXPECT_EQ("carl", test.dequeue()) << "carl was not dequeued sixth\n";
    EXPECT_EQ("gary", test.dequeue()) << "gary was not dequeued seventh\n";
}

//
// peek tests
//
TEST(Peek, EmptyPeek) {
    prqueue<string> test;

    EXPECT_EQ(0, test.size()) << "size is not zero somehow\n";
    EXPECT_EQ("", test.peek()) << "Peek did not return default value for the empty prqueue\n";
}

TEST(Peek, SizeOnePeek) {
    prqueue<int> test;

    test.enqueue('f', 1);

    EXPECT_EQ('f', test.peek()) << "peek did not return value of the root\n";
}

TEST(Peek, ExpectedPeek) {
    prqueue<int> test;

    test.enqueue(12, 4);
    test.enqueue(13, 2);
    test.enqueue(14, 5);
    test.enqueue(15, 1);

    EXPECT_EQ(15, test.peek()) << "peek did not return the value of the smallest priority\n";
}

//
// dequeue tests
//

TEST(Dequeue, Empty) {
    prqueue<int> test;

    int l = test.dequeue();

    EXPECT_EQ(0, l) << "dequeue did not return default value\n";
    EXPECT_EQ(0, test.size()) << "size is not zero\n";
}

TEST(Dequeue, SizeOneList) {
    prqueue<string> test;

    test.enqueue("Hello!", 1);

    string t = test.dequeue();

    EXPECT_EQ("Hello!", t) << "Dequeue did not return the correct value\n";
    EXPECT_EQ(0, test.size()) << "size was not updated to zero\n";
    EXPECT_EQ(nullptr, test.getRoot()) << "root is not null\n";
}

TEST(Dequeue, NormalList) {
    prqueue<string> test;

    test.enqueue("chris", 6);
    test.enqueue("adam", 3);
    test.enqueue("harry", 1);
    test.enqueue("joshua", 2);

    EXPECT_EQ("harry", test.dequeue()) << "harry was not dequeued\n";
    EXPECT_EQ("joshua", test.dequeue()) << "joshua was not dequeued\n";
    EXPECT_EQ("adam", test.dequeue()) << "adam was not dequeued\n";
    EXPECT_EQ("chris", test.dequeue()) << "chris was not dequeued\n";
}

//
// as_string tests
//
TEST(AsString, SizeOneTree) {
    prqueue<string> test;

    test.enqueue("jeremy", 3);

    string tstring = "3 value: jeremy\n";

    EXPECT_EQ(tstring, test.as_string()) << "strings did not match\n";
}

TEST(AsString, LargerTree) {
    prqueue<string> test;

    test.enqueue("chris", 3);
    test.enqueue("adam", 1);
    test.enqueue("cory", 5);
    test.enqueue("zach", 2);
    test.enqueue("lyle", 4);

    string tstring = "1 value: adam\n2 value: zach\n3 value: chris\n4 value: lyle\n5 value: cory\n";

    EXPECT_EQ(tstring, test.as_string()) << "strings did not match\n";
}

TEST(AsString, EmptyTree) {
    prqueue<string> test;

    string tstring = "";

    EXPECT_EQ(tstring, test.as_string()) << "strings did not match\n";
}

TEST(AsString, Dupes) {
    prqueue<string> test;

    test.enqueue("chris", 3);
    test.enqueue("lyle", 2);
    test.enqueue("tomar", 2);
    test.enqueue("adam", 1);
    test.enqueue("jeff", 4);
    test.enqueue("cory", 2);

    string tstring = "1 value: adam\n2 value: lyle\n2 value: tomar\n2 value: cory\n3 value: chris\n4 value: jeff\n";

    EXPECT_EQ(tstring, test.as_string()) << "strings were not equivalent\n";
}

//
// clear tests
//
TEST(Clear, EmptyList) {
    prqueue<int> test;

    test.clear();

    EXPECT_EQ(0, test.size()) << "size is not zero\n";
    EXPECT_EQ(nullptr, test.getRoot()) << "root is not nullptr\n";
}

TEST(Clear, NormalTree) {
    prqueue<string> test;

    test.enqueue("chris", 3);
    test.enqueue("adam", 1);
    test.enqueue("cory", 5);
    test.enqueue("zach", 2);
    test.enqueue("lyle", 4);

    test.clear();

    EXPECT_EQ(0, test.size()) << "size is not zero\n";
    EXPECT_EQ(nullptr, test.getRoot()) << "root is not nullptr\n";
}

//
//copy constructor tests
//
TEST(CopyConstructor, EmptyTree) {
    prqueue<int> base;
    prqueue<int> test(base);

    EXPECT_EQ(test.size(), base.size()) << "sizes are not the same\n";
    EXPECT_EQ(test.size(), 0) << "size is not 0\n";
    EXPECT_EQ(test.getRoot(), nullptr) << "root is not nullptr\n";
}

TEST(CopyConstructor, NormalTreeNoLinks) {
    prqueue<int> base;

    base.enqueue(1, 4);
    base.enqueue(4, 2);
    base.enqueue(5, 3);
    base.enqueue(7, 5);
    base.enqueue(2, 1);

    prqueue<int> test(base);

    EXPECT_EQ(base.size(), test.size()) << "sizes are not the same\n";
    EXPECT_EQ(2, test.dequeue()) << "2 was not the first to be returned\n";
    EXPECT_EQ(4, test.dequeue()) << "4 was not the second to be returned\n";
    EXPECT_EQ(5, test.dequeue()) << "5 was not the third to be returned\n";
    EXPECT_EQ(1, test.dequeue()) << "1 was not the fourth to be returned\n";
    EXPECT_EQ(7, test.dequeue()) << "7 was not the fifth to be returned\n";
}

TEST(CopyConstructor, NormalTreeLinks) {
    prqueue<string> base;

    base.enqueue("me", 4);
    base.enqueue("you", 3);
    base.enqueue("them", 3);
    base.enqueue("him", 1);
    base.enqueue("her", 5);

    prqueue<string> test(base);

    EXPECT_EQ(test.size(), base.size()) << "sizes are not equivalent\n";
    EXPECT_EQ("him", test.dequeue()) << "he was not first\n";
    EXPECT_EQ("you", test.dequeue()) << "you were not second\n";
    EXPECT_EQ("them", test.dequeue()) << "they were not third\n";
    EXPECT_EQ("me", test.dequeue()) << "I was not fourth\n";
    EXPECT_EQ("her", test.dequeue()) << "she was not fifth\n";
}

//
//operator= tests
//
TEST(Assignment, EmptyTree) {
    prqueue<int> base;
    prqueue<int> test = base;

    EXPECT_EQ(test.size(), base.size()) << "sizes are not the same\n";
    EXPECT_EQ(test.size(), 0) << "size is not 0\n";
    EXPECT_EQ(test.getRoot(), nullptr) << "root is not nullptr\n";
    EXPECT_EQ(base, test) << "trees were said to not be the same\n";
}

TEST(Assignment, NormalTreeNoLinks) {
    prqueue<int> base;

    base.enqueue(1, 4);
    base.enqueue(4, 2);
    base.enqueue(5, 3);
    base.enqueue(7, 5);
    base.enqueue(2, 1);

    prqueue<int> test = base;

    EXPECT_EQ(base, test) << "trees were said to not be the same\n";
    EXPECT_EQ(base.size(), test.size()) << "sizes are not the same\n";
    EXPECT_EQ(2, test.dequeue()) << "2 was not the first to be returned\n";
    EXPECT_EQ(4, test.dequeue()) << "4 was not the second to be returned\n";
    EXPECT_EQ(5, test.dequeue()) << "5 was not the third to be returned\n";
    EXPECT_EQ(1, test.dequeue()) << "1 was not the fourth to be returned\n";
    EXPECT_EQ(7, test.dequeue()) << "7 was not the fifth to be returned\n";
}

TEST(Assignment, NormalTreeLinks) {
    prqueue<string> base;

    base.enqueue("me", 4);
    base.enqueue("you", 3);
    base.enqueue("them", 3);
    base.enqueue("him", 1);
    base.enqueue("her", 5);

    prqueue<string> test = base;

    EXPECT_EQ(base, test) << "trees were said to not be the same\n";
    EXPECT_EQ(test.size(), base.size()) << "sizes are not equivalent\n";
    EXPECT_EQ("him", test.dequeue()) << "he was not first\n";
    EXPECT_EQ("you", test.dequeue()) << "you were not second\n";
    EXPECT_EQ("them", test.dequeue()) << "they were not third\n";
    EXPECT_EQ("me", test.dequeue()) << "I was not fourth\n";
    EXPECT_EQ("her", test.dequeue()) << "she was not fifth\n";
}

TEST(Assignment, SelfAssignment) {
    prqueue<string> base;

    base.enqueue("me", 4);
    base.enqueue("you", 3);
    base.enqueue("them", 3);
    base.enqueue("him", 1);
    base.enqueue("her", 5);

    base = base;

    EXPECT_EQ(base.size(), base.size()) << "sizes are not equivalent\n";
    EXPECT_EQ("him", base.dequeue()) << "he was not first\n";
    EXPECT_EQ("you", base.dequeue()) << "you were not second\n";
    EXPECT_EQ("them", base.dequeue()) << "they were not third\n";
    EXPECT_EQ("me", base.dequeue()) << "I was not fourth\n";
    EXPECT_EQ("her", base.dequeue()) << "she was not fifth\n";
}

TEST(Assignment, AlreadyFilledTree) {
    prqueue<string> base;

    base.enqueue("Richter", 3);
    base.enqueue("Julius", 4);
    base.enqueue("Simon", 1);
    base.enqueue("Juste", 2);
    base.enqueue("Trevor", 6);
    base.enqueue("Leon", 4);

    prqueue<string> test;

    test.enqueue("Samus", 3);
    test.enqueue("Ridley", 4);
    test.enqueue("Kraid", 2);

    test = base;

    EXPECT_EQ(base, test) << "trees were said to not be the same\n";
}
//
//operator== tests
//
TEST(Equality, NormalTrees) {
    prqueue<string> base;

    base.enqueue("me", 4);
    base.enqueue("you", 3);
    base.enqueue("them", 3);
    base.enqueue("him", 1);
    base.enqueue("her", 5);

    prqueue<string> test(base);

    EXPECT_EQ(test, base) << "equality test did not return true even though it is\n";

    test.enqueue("all of us", 2);

    EXPECT_NE(test, base) << "equality test did not return false even though it is\n";
}

TEST(Equality, ValsSameStructDiff) {
    prqueue<int> test1, test2, test3;

    test1.enqueue(1,1);
    test1.enqueue(2,2);
    test1.enqueue(3,3);

    test2.enqueue(2,2);
    test2.enqueue(1,1);
    test2.enqueue(3,3);

    test3.enqueue(2,2);
    test3.enqueue(3,3);
    test3.enqueue(1,1);

    EXPECT_EQ(test2,test3) << "tree2 and tree3 were said not be the same even though they are\n";
    EXPECT_NE(test1, test3) << "tree1 and tree3 were said to be the same even though they aren't\n";
    EXPECT_NE(test1, test2) << "tree1 and tree2 were said to be the same even though they aren't\n";
}

TEST(Equality, EmptyTree) {
    prqueue<string> base, test;

    EXPECT_EQ(base,test) << "equality returned false for two empty trees\n";
}

//
//begin and next tests
//
TEST(BeginNext, NormalTreeLinks) {
    prqueue<string> test;

    test.enqueue("chris", 4);
    test.enqueue("tomar", 3);
    test.enqueue("adam", 5);
    test.enqueue("zach", 3);
    test.enqueue("lyle", 1);
    test.enqueue("cory", 4);
    test.enqueue("julian", 2);
    test.enqueue("dave", 3);

    test.begin();

    string s = "";
    int pr = -1;

    
    EXPECT_TRUE(test.next(s, pr)) << "1 test.next did not return true when it should have\n";
    EXPECT_EQ("lyle", s) << "lyle was not stored in s\n";
    EXPECT_EQ(1, pr) << "1 was not stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "2 test.next did not return true when it should have\n";
    EXPECT_EQ("julian", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(2, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "3 test.next did not return true when it should have\n";
    EXPECT_EQ("tomar", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(3, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "3 (link 1) test.next did not return true when it should have\n";
    EXPECT_EQ("zach", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(3, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "3 (link 2) test.next did not return true when it should have\n";
    EXPECT_EQ("dave", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(3, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "4 test.next did not return true when it should have\n";
    EXPECT_EQ("chris", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(4, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "4 (link) test.next did not return true when it should have\n";
    EXPECT_EQ("cory", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(4, pr) << "incorrect value stored in pr\n";

    EXPECT_TRUE(test.next(s, pr)) << "5 test.next did not return true when it should have\n";
    EXPECT_EQ("adam", s) << "incorrect value was stored in s\n";
    EXPECT_EQ(5, pr) << "incorrect value stored in pr\n";

    EXPECT_FALSE(test.next(s, pr)) << "END text.next did not return false when it should have\n";

    
}

TEST(BeginNext, LargeRandomTree) {
    srand((unsigned)time(NULL));

    prqueue<int> test;

    for (int i = 0; i < 200; i++) {
        int pr = rand() % 20;
        test.enqueue(i, pr);
    }

    int pr = -1;
    int v = -1;
    int i = 0;

    test.begin();

    set<int> vals;

    while (test.next(v, pr)) {
        //cout << "value: " << v << ", priority: " << pr << endl;
        vals.emplace(v);
        i++;
    }

    EXPECT_EQ(200, i) << "loop did not iterate 200 times, instead it iterated " << i << " times\n";

    i = 0;
    for (auto it : vals) {
        ASSERT_EQ(it, i) << "The value that should have been here was skipped.\n";
        i++;
    }
}