/*
 * Entry: 0055acf7
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::_Umove<PortData_*_*>
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: PortData * * _Umove<PortData_*_*>(vector<PortData_*,std::allocator<PortData_*>_> * this, PortData * * param_1, PortData * * param_2, PortData * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::_Umove<PortData_*_*>
          (vector<PortData_*,std::allocator<PortData_*>_> *this,PortData **param_1,
          PortData **param_2,PortData **param_3)

{
  PortData **ppPVar1;
  
  ppPVar1 = stdext::
            unchecked_uninitialized_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
                      (param_1,param_2,param_3,(allocator<PortData_*> *)&this->_padding_);
  return ppPVar1;
}
