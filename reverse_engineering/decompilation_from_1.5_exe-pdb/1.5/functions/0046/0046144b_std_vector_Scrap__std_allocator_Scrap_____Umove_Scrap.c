/*
 * Entry: 0046144b
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Umove<Scrap_*_*>
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: Scrap * * _Umove<Scrap_*_*>(vector<Scrap_*,std::allocator<Scrap_*>_> * this, Scrap * * param_1, Scrap * * param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Umove<Scrap_*_*>
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,Scrap **param_1,Scrap **param_2,
          Scrap **param_3)

{
  Scrap **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
                      (param_1,param_2,param_3,(allocator<Scrap_*> *)&this->_padding_);
  return ppSVar1;
}
