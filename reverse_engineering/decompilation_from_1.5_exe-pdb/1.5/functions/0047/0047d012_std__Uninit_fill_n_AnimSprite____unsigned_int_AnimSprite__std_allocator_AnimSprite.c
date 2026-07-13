/*
 * Entry: 0047d012
 * Name: std::_Uninit_fill_n<AnimSprite_*_*,unsigned_int,AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<AnimSprite_*_*,unsigned_int,AnimSprite_*,std::allocator<AnimSprite_*>_>(AnimSprite * * param_1, uint param_2, AnimSprite * * param_3, allocator<AnimSprite_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<AnimSprite_*_*,unsigned_int,AnimSprite_*,std::allocator<AnimSprite_*>_>
          (AnimSprite **param_1,uint param_2,AnimSprite **param_3,allocator<AnimSprite_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<AnimSprite_*_*,unsigned_int,AnimSprite_*>(param_1,param_2,param_3);
  return;
}
