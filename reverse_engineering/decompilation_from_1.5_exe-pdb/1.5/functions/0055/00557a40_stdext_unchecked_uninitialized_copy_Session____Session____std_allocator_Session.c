/*
 * Entry: 00557a40
 * Name: stdext::unchecked_uninitialized_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
 * Namespace: stdext
 * Signature: Session * * unchecked_uninitialized_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>(Session * * param_1, Session * * param_2, Session * * param_3, allocator<Session_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __cdecl
stdext::unchecked_uninitialized_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
          (Session **param_1,Session **param_2,Session **param_3,allocator<Session_*> *param_4)

{
  Session **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
