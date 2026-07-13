/*
 * Entry: 0052eeb9
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Umove<ExplosionClass_*_*>
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: ExplosionClass * * _Umove<ExplosionClass_*_*>(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Umove<ExplosionClass_*_*>
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,ExplosionClass **param_1
          ,ExplosionClass **param_2,ExplosionClass **param_3)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = stdext::
            unchecked_uninitialized_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
                      (param_1,param_2,param_3,(allocator<ExplosionClass_*> *)&this->_padding_);
  return ppEVar1;
}
