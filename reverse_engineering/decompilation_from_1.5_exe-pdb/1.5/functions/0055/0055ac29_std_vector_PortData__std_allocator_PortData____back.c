/*
 * Entry: 0055ac29
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::back
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: PortData * * back(vector<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::back
          (vector<PortData_*,std::allocator<PortData_*>_> *this)

{
  PortData **ppPVar1;
  _Vector_iterator<PortData_*,std::allocator<PortData_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> local_c;
  
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator-
                    ((_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *)&local_c,
                     (int)local_14);
  ppPVar1 = _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator*(_Var2._0_4_);
  return ppPVar1;
}
