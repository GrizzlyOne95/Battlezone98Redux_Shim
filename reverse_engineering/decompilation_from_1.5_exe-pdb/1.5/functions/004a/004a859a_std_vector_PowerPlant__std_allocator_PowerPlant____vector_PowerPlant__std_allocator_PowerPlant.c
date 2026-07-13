/*
 * Entry: 004a859a
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * vector<PowerPlant_*,std::allocator<PowerPlant_*>_>(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::
vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  _Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_>
            ((_Vector_val<PowerPlant_*,std::allocator<PowerPlant_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
