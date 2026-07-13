/*
 * Entry: 0049983b
 * Name: std::_Uninit_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>(GameObjectClass * * param_1, uint param_2, GameObjectClass * * param_3, allocator<GameObjectClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Uninit_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>
          (GameObjectClass **param_1,uint param_2,GameObjectClass **param_3,
          allocator<GameObjectClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*>
            (param_1,param_2,param_3);
  return;
}
