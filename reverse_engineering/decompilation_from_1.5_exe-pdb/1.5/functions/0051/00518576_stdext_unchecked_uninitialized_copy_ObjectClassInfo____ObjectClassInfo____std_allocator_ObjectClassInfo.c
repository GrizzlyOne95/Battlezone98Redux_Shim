/*
 * Entry: 00518576
 * Name: stdext::unchecked_uninitialized_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: stdext
 * Signature: ObjectClassInfo * * unchecked_uninitialized_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3, allocator<ObjectClassInfo_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __cdecl
stdext::
unchecked_uninitialized_copy<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::allocator<ObjectClassInfo_*>_>
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
