#include "pch.h"

#include "../Cappuchini/CircuitDescriptionParser.h"

// For this test to work, follow https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/test/unit-testing-existing-cpp-applications-with-test-explorer?view=vs-2015#objectRef
// If you want to test the class CircuitDescriptionParser, you have to add CircuitDescriptionParser.obj to 
// Linker > Input > AdditionalInput in the test project! Otherwise you get unresolved external symbols.

TEST(ParseVoltageSourceTest, ParseVoltageSource) {

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("../CappuchiniTest/voltagesource.cd");

	EXPECT_EQ(circuitDescriptionParser.circuitElements.size(), 1);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).id, "V1");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).type, "V");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeA, "5");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeB, "0");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).nodeC, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).value, 2);
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).group, "N/A");
	EXPECT_EQ(circuitDescriptionParser.circuitElements.at(0).scaleFactor, 1);
}