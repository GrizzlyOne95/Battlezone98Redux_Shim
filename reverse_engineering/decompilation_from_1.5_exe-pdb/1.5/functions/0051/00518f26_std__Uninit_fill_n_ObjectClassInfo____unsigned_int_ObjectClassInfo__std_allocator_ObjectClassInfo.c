/*
 * Entry: 00518f26
 * Name: std::_Uninit_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(ObjectClassInfo * * param_1, uint param_2, ObjectClassInfo * * param_3, allocator<ObjectClassInfo_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Uninit_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
          (ObjectClassInfo **param_1,uint param_2,ObjectClassInfo **param_3,
          allocator<ObjectClassInfo_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*>
            (param_1,param_2,param_3);
  return;
}
