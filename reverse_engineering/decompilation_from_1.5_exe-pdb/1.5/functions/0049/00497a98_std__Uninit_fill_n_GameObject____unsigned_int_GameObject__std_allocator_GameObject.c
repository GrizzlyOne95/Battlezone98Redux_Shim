/*
 * Entry: 00497a98
 * Name: std::_Uninit_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>(GameObject * * param_1, uint param_2, GameObject * * param_3, allocator<GameObject_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>
          (GameObject **param_1,uint param_2,GameObject **param_3,allocator<GameObject_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<GameObject_*_*,unsigned_int,GameObject_*>(param_1,param_2,param_3);
  return;
}
