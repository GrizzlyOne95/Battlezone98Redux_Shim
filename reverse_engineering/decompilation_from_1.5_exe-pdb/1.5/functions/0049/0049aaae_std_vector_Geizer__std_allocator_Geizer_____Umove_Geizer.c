/*
 * Entry: 0049aaae
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Umove<Geizer_*_*>
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: Geizer * * _Umove<Geizer_*_*>(vector<Geizer_*,std::allocator<Geizer_*>_> * this, Geizer * * param_1, Geizer * * param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Umove<Geizer_*_*>
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,Geizer **param_1,Geizer **param_2,
          Geizer **param_3)

{
  Geizer **ppGVar1;
  
  ppGVar1 = stdext::unchecked_uninitialized_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
                      (param_1,param_2,param_3,(allocator<Geizer_*> *)&this->_padding_);
  return ppGVar1;
}
