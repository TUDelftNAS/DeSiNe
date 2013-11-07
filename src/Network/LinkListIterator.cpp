/******************************************************************************

    source file LinkListIterator.cpp for class: LinkListIterator

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/



// Include(s)
#include "Network/Link.h"
#include "Network/LinkList.h"

//------------------------------------------------------------------------------
//  constructor LinkListIterator(IntIntLinkMap* linkmap);
//------------------------------------------------------------------------------
LinkListIterator::LinkListIterator(const LinkList::IntIntLinkMap* linkmap)
{
    src_iter      = linkmap->begin();
    src_iter_end  = linkmap->end();
    link_iter     = src_iter->second->begin();
    link_iter_end = src_iter->second->end();
    allLinks = true;
}


//------------------------------------------------------------------------------
//  constructor LinkListIterator(IntIntLinkMap* linkmap, int source)
//------------------------------------------------------------------------------
LinkListIterator::LinkListIterator(const LinkList::IntIntLinkMap* linkmap,
    const int &source)
{
    src_iter      = linkmap->find(source);
    link_iter     = src_iter->second->begin();
    link_iter_end = src_iter->second->end();
    allLinks = false;
}


//------------------------------------------------------------------------------
//  void operator++();
//------------------------------------------------------------------------------
void LinkListIterator::operator++()
{
    ++link_iter;
/* This is done by operator() now
    if (allLinks && link_iter == link_iter_end)
    {
        ++src_iter;
        if (src_iter != src_iter_end)
        {
            link_iter = src_iter->second->begin();
            link_iter_end = src_iter->second->end();
        }
    }
*/
}


//------------------------------------------------------------------------------
//  bool operator()();
//------------------------------------------------------------------------------
bool LinkListIterator::operator()()
{

    bool result = (link_iter != link_iter_end);  // true if more elements

    if (allLinks && !result)
    {
        result = true;
        while ( (link_iter == link_iter_end) && result)
//                (src_iter != src_iter_end) )  // end of adj list of a node
        {
            ++src_iter;
            if (result = src_iter != src_iter_end)
            {
                link_iter     = src_iter->second->begin();
                link_iter_end = src_iter->second->end();
            }
        }
    }
//    cout << " result: " << result << endl;
    return result;
}
