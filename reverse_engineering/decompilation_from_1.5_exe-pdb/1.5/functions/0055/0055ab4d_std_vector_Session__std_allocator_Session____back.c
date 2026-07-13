/*
 * Entry: 0055ab4d
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::back
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: Session * * back(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::back
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  Session **ppSVar1;
  _Vector_iterator<Session_*,std::allocator<Session_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_c;
  
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<Session_*,std::allocator<Session_*>_>::operator-
                    ((_Vector_iterator<Session_*,std::allocator<Session_*>_> *)&local_c,
                     (int)local_14);
  ppSVar1 = _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*(_Var2._0_4_);
  return ppSVar1;
}
