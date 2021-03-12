#include "pch.h"

#include "../Cappuchini/CircuitDescriptionParser.h"

// For this test to work, follow https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/test/unit-testing-existing-cpp-applications-with-test-explorer?view=vs-2015#objectRef
// If you want to test the class CircuitDescriptionParser, you have to add CircuitDescriptionParser.obj to 
// Linker > Input > AdditionalInput in the test project! Otherwise you get unresolved external symbols.

TEST(ParseInductorTest, ParseInductor) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/inductor.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 1);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).id, "L1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).type, "L");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeA, "11");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeB, "12");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).value, 12.9);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).scaleFactor, 1);
}