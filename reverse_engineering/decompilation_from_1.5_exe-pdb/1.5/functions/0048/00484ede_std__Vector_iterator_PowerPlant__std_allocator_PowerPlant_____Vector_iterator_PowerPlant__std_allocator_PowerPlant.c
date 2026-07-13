/*
 * Entry: 00484ede
 * Name: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Namespace: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, PowerPlant * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * __thiscall
std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,PowerPlant **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            ((_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *)this,param_1,
             param_2);
  return this;
}
