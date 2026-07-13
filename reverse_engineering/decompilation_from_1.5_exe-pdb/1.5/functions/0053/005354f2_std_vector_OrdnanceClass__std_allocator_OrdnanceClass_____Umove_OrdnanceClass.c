/*
 * Entry: 005354f2
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Umove<OrdnanceClass_*_*>
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: OrdnanceClass * * _Umove<OrdnanceClass_*_*>(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Umove<OrdnanceClass_*_*>
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,OrdnanceClass **param_1,
          OrdnanceClass **param_2,OrdnanceClass **param_3)

{
  OrdnanceClass **ppOVar1;
  
  ppOVar1 = stdext::
            unchecked_uninitialized_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
                      (param_1,param_2,param_3,(allocator<OrdnanceClass_*> *)&this->_padding_);
  return ppOVar1;
}
