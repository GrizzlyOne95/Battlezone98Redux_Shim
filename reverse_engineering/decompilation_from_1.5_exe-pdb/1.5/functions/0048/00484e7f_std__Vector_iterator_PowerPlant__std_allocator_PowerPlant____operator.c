/*
 * Entry: 00484e7f
 * Name: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator++
 * Namespace: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * operator++(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * __thiscall
std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator++
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator++
            ((_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *)this);
  return this;
}
