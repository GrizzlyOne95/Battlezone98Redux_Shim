/*
 * Entry: 004a836e
 * Name: std::_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>::~_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Namespace: std::_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: void ~_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>(_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>::
~_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>
          (_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
