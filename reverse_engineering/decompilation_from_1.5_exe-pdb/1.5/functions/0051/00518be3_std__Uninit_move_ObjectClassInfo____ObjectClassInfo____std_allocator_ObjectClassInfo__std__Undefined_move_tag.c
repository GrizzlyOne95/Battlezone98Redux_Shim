/*
 * Entry: 00518be3
 * Name: std::_Uninit_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ObjectClassInfo * * _Uninit_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>,std::_Undefined_move_tag>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3, allocator<ObjectClassInfo_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __cdecl
std::
_Uninit_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>,std::_Undefined_move_tag>
          (ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3,
          allocator<ObjectClassInfo_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = stdext::
            unchecked_uninitialized_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppOVar1;
}
