/*
 * Entry: 004a8005
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::capacity
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: uint capacity(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::capacity
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  if (this->_Myfirst == (PowerPlant **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
