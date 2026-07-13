/*
 * Entry: 004a8476
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::~vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: void ~vector<PowerPlant_*,std::allocator<PowerPlant_*>_>(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::
~vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
