/*
 * Entry: 004a837a
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Tidy
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: void _Tidy(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Tidy
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  if (this->_Myfirst != (PowerPlant **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (PowerPlant **)0x0;
  this->_Mylast = (PowerPlant **)0x0;
  this->_Myend = (PowerPlant **)0x0;
  return;
}
