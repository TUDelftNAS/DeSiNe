/******************************************************************************

    source file LinkListMemento.cpp for class: LinkListMemento

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/

// Include(s)
#include "Network/Link.h"
#include "Network/LinkList.h"

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor LinkListMemento::LinkListMemento(Parameters* params)
//------------------------------------------------------------------------------
LinkListMemento::LinkListMemento(const LinkList::IntIntLinkMap* linkmap)
{
    // Copy the maps
    link_map = new LinkList::IntIntLinkMap(*linkmap);

    // iterate source nodes
    for (LinkList::IntIntLinkMap::iterator srcIX = link_map->begin();
         srcIX != link_map->end(); ++srcIX)
    {
        srcIX->second = new LinkList::IntLinkMap(*srcIX->second);
        LinkList::IntLinkMap* dest_map = srcIX->second;
        // iterate destination nodes
        for (LinkList::IntLinkMap::iterator dstIX = dest_map->begin();
             dstIX != dest_map->end(); ++dstIX)
        {
            dstIX->second = new Link(*dstIX->second);
        }
    }
}


//------------------------------------------------------------------------------
//  destructor LinkListMemento::~LinkListMemento()
//------------------------------------------------------------------------------
LinkListMemento::~LinkListMemento()
{
    //remove all elements
    // iterate source nodes
    for (LinkList::IntIntLinkMap::iterator srcIX = link_map->begin();
         srcIX != link_map->end(); ++srcIX)
    {
        LinkList::IntLinkMap* dest_map = srcIX->second;
        // iterate destination nodes
        for (LinkList::IntLinkMap::iterator dstIX = dest_map->begin();
             dstIX != dest_map->end(); ++dstIX)
        {
            delete dstIX->second;
            //dest_map->erase(dstIX++);
        }
        delete dest_map;
        //link_map->erase(srcIX++);
    }
    delete link_map;
}
