/*
 * Entry: 0055acc1
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::_Umove<Session_*_*>
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: Session * * _Umove<Session_*_*>(vector<Session_*,std::allocator<Session_*>_> * this, Session * * param_1, Session * * param_2, Session * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::_Umove<Session_*_*>
          (vector<Session_*,std::allocator<Session_*>_> *this,Session **param_1,Session **param_2,
          Session **param_3)

{
  Session **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
                      (param_1,param_2,param_3,(allocator<Session_*> *)&this->_padding_);
  return ppSVar1;
}
