/*
 * Entry: 004621c4
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator::operator*
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator
 * Signature: OpenNode * operator*(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OpenNode * __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::iterator::operator*(iterator *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00462064;
    }
  }
  iVar2 = *piVar1;
LAB_00462064:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return (OpenNode *)(*(int *)&this->field_0x4 + 0xc);
}
