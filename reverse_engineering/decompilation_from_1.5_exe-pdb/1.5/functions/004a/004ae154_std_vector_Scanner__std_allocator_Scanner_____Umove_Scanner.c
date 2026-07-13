/*
 * Entry: 004ae154
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Umove<Scanner_*_*>
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: Scanner * * _Umove<Scanner_*_*>(vector<Scanner_*,std::allocator<Scanner_*>_> * this, Scanner * * param_1, Scanner * * param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Umove<Scanner_*_*>
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,Scanner **param_1,Scanner **param_2,
          Scanner **param_3)

{
  Scanner **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
                      (param_1,param_2,param_3,(allocator<Scanner_*> *)&this->_padding_);
  return ppSVar1;
}
