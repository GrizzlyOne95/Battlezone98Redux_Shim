/*
 * Entry: 00489490
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Ufill
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: Craft * * _Ufill(vector<Craft_*,std::allocator<Craft_*>_> * this, Craft * * param_1, uint param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Ufill
          (vector<Craft_*,std::allocator<Craft_*>_> *this,Craft **param_1,uint param_2,
          Craft **param_3)

{
  stdext::unchecked_fill_n<Craft_*_*,unsigned_int,Craft_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
