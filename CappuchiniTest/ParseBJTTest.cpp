#include "pch.h"

#include "../Cappuchini/CircuitDescriptionParser.h"

// For this test to work, follow https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/test/unit-testing-existing-cpp-applications-with-test-explorer?view=vs-2015#objectRef

// If you want to test the class CircuitDescriptionParser
// 1. In the Test Project, select the "References"/"Verweise" node and Select "Add reference" from the context menu.
//    Add a reference to the main project folder.
// 2. Open the properties of the test project > Liner > Allgemein > Zusätzliche Bibliotheksverzeichnisse > 
//    Add the Debug folder of the main folder, so that the obj files are found
// 3. you have to add CircuitDescriptionParser.obj to 
// Linker > Input > AdditionalInput in the test project! Otherwise you get unresolved external symbols.

TEST(ParseBJTTest, ParseBJT_NPN) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/bjt.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 4);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).id, "QN1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).type, "QN");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeA, "1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeB, "2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeC, "3");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).scaleFactor, 1);
}

TEST(ParseBJTTest, ParseBJT_NPN_WithScaleFactor) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/bjt.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 4);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).id, "QN2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).type, "QN");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeA, "1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeB, "2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).nodeC, "3");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(1).scaleFactor, 10.1);
}

TEST(ParseBJTTest, ParseBJT_PNP) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/bjt.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 4);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).id, "QP1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).type, "QP");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).nodeA, "1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).nodeB, "2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).nodeC, "3");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(2).scaleFactor, 1);
}

TEST(ParseBJTTest, ParseBJT_PNP_WithScaleFactor) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/bjt.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 4);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).id, "QP2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).type, "QP");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).nodeA, "1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).nodeB, "2");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).nodeC, "3");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).value, 0);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(3).scaleFactor, 10.1);
}