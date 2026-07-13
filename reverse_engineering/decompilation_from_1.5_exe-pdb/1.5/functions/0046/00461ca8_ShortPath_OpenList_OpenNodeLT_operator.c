/*
 * Entry: 00461ca8
 * Name: ShortPath::OpenList::OpenNodeLT::operator()
 * Namespace: ShortPath::OpenList::OpenNodeLT
 * Signature: bool operator()(OpenNodeLT * this, OpenNode param_1, OpenNode param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ShortPath::OpenList::OpenNodeLT::operator()(OpenNodeLT *this,OpenNode param_1,OpenNode param_2)

{
  return param_2.h + param_2.g < param_1.h + param_1.g;
}
