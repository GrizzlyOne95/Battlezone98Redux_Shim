/*
 * Entry: 004a898f
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::push_back
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: void push_back(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, PowerPlant * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::push_back
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,PowerPlant **param_1)

{
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var1;
  uint uVar2;
  PowerPlant **ppPVar3;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_c;
  
  ppPVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (PowerPlant **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppPVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppPVar3 = _Ufill(this,ppPVar3,1,param_1);
    this->_Mylast = ppPVar3;
  }
  else {
    _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
    _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
              (&local_c,ppPVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (PowerPlant **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
