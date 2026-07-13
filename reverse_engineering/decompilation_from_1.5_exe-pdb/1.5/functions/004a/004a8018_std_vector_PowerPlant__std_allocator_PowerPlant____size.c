/*
 * Entry: 004a8018
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::size
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: uint size(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::size
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
