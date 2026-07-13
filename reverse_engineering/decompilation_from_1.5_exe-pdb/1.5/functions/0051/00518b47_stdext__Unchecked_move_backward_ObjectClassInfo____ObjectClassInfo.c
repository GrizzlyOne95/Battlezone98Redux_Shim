/*
 * Entry: 00518b47
 * Name: stdext::_Unchecked_move_backward<ObjectClassInfo_*_*,ObjectClassInfo_*_*>
 * Namespace: stdext
 * Signature: ObjectClassInfo * * _Unchecked_move_backward<ObjectClassInfo_*_*,ObjectClassInfo_*_*>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __cdecl
stdext::_Unchecked_move_backward<ObjectClassInfo_*_*,ObjectClassInfo_*_*>
          (ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = std::
            _Move_backward_opt<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppOVar1;
}
