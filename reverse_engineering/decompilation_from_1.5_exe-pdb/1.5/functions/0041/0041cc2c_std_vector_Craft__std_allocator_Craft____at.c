/*
 * Entry: 0041cc2c
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::at
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: Craft * * at(vector<Craft_*,std::allocator<Craft_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::at
          (vector<Craft_*,std::allocator<Craft_*>_> *this,uint param_1)

{
  Craft **ppCVar1;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _Xran();
  }
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_c,this->_Myfirst,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator+
                    ((_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *)&local_c,(int)local_14);
  ppCVar1 = _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(_Var2._0_4_);
  return ppCVar1;
}
