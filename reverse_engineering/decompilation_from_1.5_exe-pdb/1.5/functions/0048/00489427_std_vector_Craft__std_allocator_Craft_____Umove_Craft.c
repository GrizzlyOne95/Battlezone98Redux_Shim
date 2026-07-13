/*
 * Entry: 00489427
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Umove<Craft_*_*>
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: Craft * * _Umove<Craft_*_*>(vector<Craft_*,std::allocator<Craft_*>_> * this, Craft * * param_1, Craft * * param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Umove<Craft_*_*>
          (vector<Craft_*,std::allocator<Craft_*>_> *this,Craft **param_1,Craft **param_2,
          Craft **param_3)

{
  Craft **ppCVar1;
  
  ppCVar1 = stdext::unchecked_uninitialized_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
                      (param_1,param_2,param_3,(allocator<Craft_*> *)&this->_padding_);
  return ppCVar1;
}
