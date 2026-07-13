/*
 * Entry: 005184d2
 * Name: std::_Move_backward_opt<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ObjectClassInfo * * _Move_backward_opt<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __cdecl
std::
_Move_backward_opt<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = _Copy_backward_opt<ObjectClassInfo_*_*,ObjectClassInfo_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppOVar1;
}
