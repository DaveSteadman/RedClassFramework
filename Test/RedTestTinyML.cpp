// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

#include "RedCoreNamespace.h"

#include "RedTestTinyML.h"

using namespace Red::Core;

namespace Red {
namespace Test {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTestTinyML::RunUnitTest(RedLog& log)
{
    if (RedTestTinyML::TestOne().IsFail())             { log.AddErrorEvent("TinyML Unit Test: TestOne Failed");              return; }
    if (RedTestTinyML::TestTwo().IsFail())             { log.AddErrorEvent("TinyML Unit Test: TestTwo Failed");              return; }
    if (RedTestTinyML::TestIterators().IsFail())       { log.AddErrorEvent("TinyML Unit Test: TestIterators Failed");        return; }
    if (RedTestTinyML::TestTreeEdit().IsFail())        { log.AddErrorEvent("TinyML Unit Test: TestTreeEdit Failed");         return; }
    if (RedTestTinyML::TestQuoteCharacters().IsFail()) { log.AddErrorEvent("TinyML Unit Test: TestQuoteCharacters Failed");  return; }

    log.AddText("TinyML Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Simple Tml Tests
RedResult RedTestTinyML::TestOne(void)
{
    {
        RedDataString TestInTml = "{{name} content}";
        RedTinyMLElement* testElement = RedTinyMLFileIO::CreateTinyML(TestInTml);
        if (testElement == NULL)
        {
            delete testElement;
            return kResultFail;
        }

        if (testElement->IsLeaf() == false)
        {
            delete testElement;
            return kResultFail;
        }

        delete testElement;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestTinyML::TestTwo(void)
{
//    {
//        RedDataString pathFail  = "/tmp/TestNonExistentFile.tml";
//        RedTinyMLElement* newTmlElement = NULL;
//
//        // Check for a non-existant file. Has to return fail
//        RedResult resultOne = RedTinyMLAction::CreateTmlFromFile(pathFail, &newTmlElement);
//        if (resultOne != kResultFail)
//            return kResultFail;
//    }
//
//    RedDataString pathSave1  = "/tmp/TestTwo1.tml";
//    RedDataString pathSave2  = "/tmp/TestTwo2.tml";
//    {
//        // Create small Tml Structure
//        RedTinyMLNode oTop("tmltree");
//        RedTinyMLNode* y = oTop.CreateChildNode("childnode");
//        y->CreateChildLeaf("xyzname1", "xyzdata1");
//        y->CreateChildLeaf("xyzname2", "xyzdata2");
//
//        if (RedTinyMLAction::CreateFileFromTml(&oTop, pathSave1, eLinedIndentedContent) != kResultSuccess)
//            return kResultFail;
//    }
//
//    {
//        RedTinyMLElement* newTmlElement = NULL;
//        if (RedTinyMLAction::CreateTmlFromFile(pathSave1, &newTmlElement) != kResultSuccess)
//            return kResultFail;
//
//        if (RedTinyMLAction::CreateFileFromTml(newTmlElement, pathSave2, eLinedIndentedContent) != kResultSuccess)
//            return kResultFail;
//    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestTinyML::TestIterators(void)
{
    {
        // Create small Tml Structure
        RedTinyMLNode x("topnode");
        RedTinyMLNode* y = x.CreateChildNode("contentnode");
        y->CreateChildLeaf("name1", "data1");
        y->CreateChildLeaf("name2", "data2");
        y->CreateChildLeaf("name3", "data3");
        y->CreateChildLeaf("name4", "data4");
        y->CreateChildLeaf("name5", "data5");

        RedTinyMLNode::TmlElementListItType yIt = y->ElementListIterator();

        int count = 0;

        int count2 = y->ElementCount();

        yIt.First();
        while (!yIt.IsDone())
        {
            RedTinyMLElement* pCurrElem = yIt.CurrentItem();

            if (pCurrElem != NULL)
                count++;
            yIt.Next();
        }

        if (count != 5)
            return kResultFail;
    }

    {
        // Create small Tml Structure
        RedTinyMLNode x("topnode");
        RedTinyMLNode* y = x.CreateChildNode("contentnode");
        y->CreateChildLeaf("name1", "data1");
        y->CreateChildLeaf("name2", "data2");
        y->CreateChildLeaf("name3", "data3");
        y->CreateChildLeaf("name3", "data4");
        y->CreateChildLeaf("name3", "data5");

        // Child search checks
        if (!RedTinyMLAction::ChildLeafExists(*y, RedDataString("name2")))
            return kResultFail;
        if (RedTinyMLAction::NumberOfNamedChildLeaves(*y, RedDataString("name3")) != 3)
            return kResultFail;

        // Tree count checks
        if (RedTinyMLAction::TreeElementCount(x) != 7)
            return kResultFail;
        if (RedTinyMLAction::TreeElementCount(*y) != 6)
            return kResultFail;
        if (x.ElementCount() != 1)
            return kResultFail;
        if (y->ElementCount() != 5)
            return kResultFail;

        int count = 0;
        RedTinyMLNode::TmlElementListItType yIt = y->ElementListIterator();
        yIt.First();
        while (!yIt.IsDone())
        {
            RedTinyMLElement* pCurrElem = yIt.CurrentItem();

            if (pCurrElem != NULL)
                count++;
            yIt.Next();
        }

        int count2 = y->ElementCount();

        if (count != 5)
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestTinyML::TestTreeEdit(void)
{
    {
        // Create small Tml Structure
        RedTinyMLNode x("topnode");
        RedTinyMLNode* y = x.CreateChildNode("contentnode");
        y->CreateChildLeaf("name1", "data1");
        y->CreateChildLeaf("name2", "data2");
        y->CreateChildLeaf("name3", "data3");
        y->CreateChildLeaf("name4", "data4");
        y->CreateChildLeaf("name5", "data5");

        RedTinyMLAction::SetChildLeaf(*y, RedDataString("name2"), RedDataString("NEWDATA2"));

        RedDataString resultName;
        if (RedTinyMLAction::ChildLeafNameForData(*y, RedDataString("NEWDATA2"), resultName) != kResultSuccess)
            return kResultFail;

        if (resultName != RedDataString("name2"))
            return kResultFail;

    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestTinyML::TestQuoteCharacters(void)
{
    {
        RedDataString TestInTml = "{{name} \"content\"}";
        RedTinyMLElement* testElement = RedTinyMLFileIO::CreateTinyML(TestInTml);
        if (testElement == NULL) return kResultFail;
        if (!testElement->IsLeaf()) { delete testElement; return kResultFail; }

        RedTinyMLLeaf* pLeaf = dynamic_cast<RedTinyMLLeaf*>(testElement);
        if (pLeaf->Data() != "\"content\"") { delete testElement; return kResultFail; }
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red

