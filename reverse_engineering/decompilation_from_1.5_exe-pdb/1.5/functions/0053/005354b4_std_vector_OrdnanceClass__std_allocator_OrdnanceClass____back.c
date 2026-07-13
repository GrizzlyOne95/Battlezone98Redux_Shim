/*
 * Entry: 005354b4
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::back
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: OrdnanceClass * * back(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::back
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  OrdnanceClass **ppOVar1;
  _Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> local_c;
  
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator-
                    ((_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)&local_c,
                     (int)local_14);
  ppOVar1 = _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator*
                      (_Var2._0_4_);
  return ppOVar1;
}
