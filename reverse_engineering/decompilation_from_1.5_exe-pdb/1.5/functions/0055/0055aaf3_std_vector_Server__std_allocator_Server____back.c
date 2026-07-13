/*
 * Entry: 0055aaf3
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::back
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: Server * * back(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::back
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  Server **ppSVar1;
  _Vector_iterator<Server_*,std::allocator<Server_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_c;
  
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<Server_*,std::allocator<Server_*>_>::operator-
                    ((_Vector_iterator<Server_*,std::allocator<Server_*>_> *)&local_c,(int)local_14)
  ;
  ppSVar1 = _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(_Var2._0_4_);
  return ppSVar1;
}
