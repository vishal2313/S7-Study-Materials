#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"

// local headers
#include <iostream>
#include <string.h>

void printBuffer(unsigned char buffer[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << (int)buffer[i] << " ";
        if (i % 64 == 63)
            std::cout << "\n";
    }
    std::cout << "\n";
}

void printAttributeCatalog() {
    // create objects for the relation catalog and attribute catalog
    RecBuffer relCatBuffer(RELCAT_BLOCK);
    RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

    // creating headers for relation catalog and attribute catalog
    HeadInfo relCatHeader;
    HeadInfo attrCatHeader;

    // load the headers of both the blocks
    relCatBuffer.getHeader(&relCatHeader);
    attrCatBuffer.getHeader(&attrCatHeader);

    // attrCatSlotIndex stores the index of current slot
    for (int i = 0, attrCatSlotIndex = 0; i < relCatHeader.numEntries; i++)
    {
        // will store the record from the relation catalog
        Attribute relCatRecord[RELCAT_NO_ATTRS];
        relCatBuffer.getRecord(relCatRecord, i);

        //  Skip dropped relations (empty name)
        if (strlen(relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0)
            continue;

        printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

        int j = 0;
        for (; j < relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal; j++, attrCatSlotIndex++)
        {
            // declare attrCatRecord and load the attribute catalog entry into it
            Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
            attrCatBuffer.getRecord(attrCatRecord, attrCatSlotIndex);

            //  Skip dropped attributes (empty name)
            if (strlen(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal) == 0 ||
                strlen(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal) == 0)
                continue;

            // if the current attribute belongs to the current relation
            if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,
                       relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0)
            {
                const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER
                                           ? "NUM"
                                           : "STR";
                printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
            }

            // once all the slots are traversed, go to next block
            if (attrCatSlotIndex == attrCatHeader.numSlots - 1) {
                attrCatSlotIndex = -1;
                attrCatBuffer = RecBuffer(attrCatHeader.rblock);
                attrCatBuffer.getHeader(&attrCatHeader);
            }
        }
        printf("\n");
    }
}

void updateAttributeName(const char *relName,
                         const char *oldAttrName, const char *newAttrName) {
    RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
    HeadInfo attrCatHeader;
    attrCatBuffer.getHeader(&attrCatHeader);

    for (int recIndex = 0; recIndex < attrCatHeader.numEntries; recIndex++) {
        Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
        attrCatBuffer.getRecord(attrCatRecord, recIndex);

        //  Skip dropped attributes (empty relation/attribute name)
        if (strlen(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal) == 0 ||
            strlen(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal) == 0)
            continue;

        // matching the relation name, and attribute name
        if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relName) == 0 &&
            strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, oldAttrName) == 0)
        {
            strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, newAttrName);
            attrCatBuffer.setRecord(attrCatRecord, recIndex);
            std::cout << "Update successful!\n\n";
            break;
        }

        // if at end of block, go to next block
        if (recIndex == attrCatHeader.numSlots - 1) {
            recIndex = -1;
            attrCatBuffer = RecBuffer(attrCatHeader.rblock);
            attrCatBuffer.getHeader(&attrCatHeader);
        }
    }
}

int main(int argc, char *argv[])
{
    Disk disk_run;
 
    printAttributeCatalog();
     //updateAttributeName("Students", "Batch", "Class");
     //printAttributeCatalog();
    return 0;
}
