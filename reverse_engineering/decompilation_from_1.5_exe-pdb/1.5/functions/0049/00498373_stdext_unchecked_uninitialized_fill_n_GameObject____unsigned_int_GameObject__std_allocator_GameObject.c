/*
 * Entry: 00498373
 * Name: stdext::unchecked_uninitialized_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>(GameObject * * param_1, uint param_2, GameObject * * param_3, allocator<GameObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<GameObject_*_*,unsigned_int,GameObject_*,std::allocator<GameObject_*>_>
          (GameObject **param_1,uint param_2,GameObject **param_3,allocator<GameObject_*> *param_4)

{
  unchecked_fill_n<GameObject_*_*,unsigned_int,GameObject_*>(param_1,param_2,param_3);
  return;
}
