/*
 * Entry: 004a83c9
 * Name: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator+=
 * Namespace: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * operator+=(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * __thiscall
std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator+=
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,int param_1)

{
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator+=
            ((_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *)this,param_1);
  return this;
}
