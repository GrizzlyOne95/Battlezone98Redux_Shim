/*
 * Entry: 0040a402
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::find
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: iterator find(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, GameObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::find(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
       *this,GameObject **param_1)

{
  GameObject *pGVar1;
  GameObject *pGVar2;
  bool bVar3;
  const_iterator *pcVar4;
  iterator iVar5;
  uint *in_stack_00000008;
  const_iterator local_14;
  const_iterator local_c;
  
  lower_bound(this,(GameObject **)&local_c);
  const_iterator::const_iterator(&local_14,this->_Myhead,this);
  bVar3 = const_iterator::operator==(&local_c,&local_14);
  if ((bVar3) || ((GameObject *)*in_stack_00000008 < ((local_c._Ptr)->_Myval).first)) {
    const_iterator::const_iterator(&local_14,this->_Myhead,this);
    pcVar4 = &local_14;
  }
  else {
    pcVar4 = &local_c;
  }
  pGVar1 = (GameObject *)pcVar4->_padding_;
  pGVar2 = (GameObject *)pcVar4->_Ptr;
  *param_1 = pGVar1;
  param_1[1] = pGVar2;
  iVar5._4_4_ = pGVar1;
  iVar5._0_4_ = param_1;
  return iVar5;
}
