/*
 * Entry: 0052ee45
 * Name: std::_Uninit_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*,std::allocator<ExplosionClass_*>_>(ExplosionClass * * param_1, uint param_2, ExplosionClass * * param_3, allocator<ExplosionClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Uninit_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*,std::allocator<ExplosionClass_*>_>
          (ExplosionClass **param_1,uint param_2,ExplosionClass **param_3,
          allocator<ExplosionClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
            (param_1,param_2,param_3);
  return;
}
