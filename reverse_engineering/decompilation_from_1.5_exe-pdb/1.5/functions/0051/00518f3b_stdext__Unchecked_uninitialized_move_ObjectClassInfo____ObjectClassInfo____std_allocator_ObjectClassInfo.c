/*
 * Entry: 00518f3b
 * Name: stdext::_Unchecked_uninitialized_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: stdext
 * Signature: ObjectClassInfo * * _Unchecked_uninitialized_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3, allocator<ObjectClassInfo_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __cdecl
stdext::
_Unchecked_uninitialized_move<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
          (ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3,
          allocator<ObjectClassInfo_*> *param_4)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = std::
            _Uninit_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppOVar1;
}
