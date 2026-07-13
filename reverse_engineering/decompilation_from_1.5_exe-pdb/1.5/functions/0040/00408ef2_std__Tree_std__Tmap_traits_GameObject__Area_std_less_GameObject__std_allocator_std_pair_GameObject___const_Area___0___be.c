/*
 * Entry: 00408ef2
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::begin
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: iterator begin(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::begin(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        *this)

{
  undefined4 extraout_EDX;
  iterator iVar1;
  const_iterator *in_stack_00000004;
  
  const_iterator::const_iterator(in_stack_00000004,this->_Myhead->_Left,this);
  iVar1._4_4_ = extraout_EDX;
  iVar1._0_4_ = in_stack_00000004;
  return iVar1;
}
