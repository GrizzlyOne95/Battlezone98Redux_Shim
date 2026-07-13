/*
 * Entry: 0052ee7b
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::back
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: ExplosionClass * * back(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::back
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  ExplosionClass **ppEVar1;
  _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> local_c;
  
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator-
                    ((_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)
                     &local_c,(int)local_14);
  ppEVar1 = _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator*
                      (_Var2._0_4_);
  return ppEVar1;
}
