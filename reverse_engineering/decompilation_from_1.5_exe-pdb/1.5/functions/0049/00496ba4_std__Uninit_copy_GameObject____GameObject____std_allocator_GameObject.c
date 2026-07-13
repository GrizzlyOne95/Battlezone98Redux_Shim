/*
 * Entry: 00496ba4
 * Name: std::_Uninit_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
 * Namespace: std
 * Signature: GameObject * * _Uninit_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3, allocator<GameObject_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::_Uninit_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3,
          allocator<GameObject_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
