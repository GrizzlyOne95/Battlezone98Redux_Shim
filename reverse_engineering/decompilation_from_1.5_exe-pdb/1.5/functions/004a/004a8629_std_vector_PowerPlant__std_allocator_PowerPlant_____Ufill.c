/*
 * Entry: 004a8629
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Ufill
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: PowerPlant * * _Ufill(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, PowerPlant * * param_1, uint param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Ufill
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,PowerPlant **param_1,
          uint param_2,PowerPlant **param_3)

{
  stdext::unchecked_fill_n<PowerPlant_*_*,unsigned_int,PowerPlant_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
