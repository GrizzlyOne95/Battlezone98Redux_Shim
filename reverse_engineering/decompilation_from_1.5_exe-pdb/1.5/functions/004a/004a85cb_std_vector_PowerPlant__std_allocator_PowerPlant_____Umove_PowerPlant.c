/*
 * Entry: 004a85cb
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Umove<PowerPlant_*_*>
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: PowerPlant * * _Umove<PowerPlant_*_*>(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Umove<PowerPlant_*_*>
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,PowerPlant **param_1,
          PowerPlant **param_2,PowerPlant **param_3)

{
  PowerPlant **ppPVar1;
  
  ppPVar1 = stdext::
            unchecked_uninitialized_copy<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>
                      (param_1,param_2,param_3,(allocator<PowerPlant_*> *)&this->_padding_);
  return ppPVar1;
}
