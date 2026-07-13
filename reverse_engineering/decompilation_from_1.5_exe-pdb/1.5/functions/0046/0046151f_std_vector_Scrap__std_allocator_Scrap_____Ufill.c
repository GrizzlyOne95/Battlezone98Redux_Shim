/*
 * Entry: 0046151f
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Ufill
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: Scrap * * _Ufill(vector<Scrap_*,std::allocator<Scrap_*>_> * this, Scrap * * param_1, uint param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Ufill
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,Scrap **param_1,uint param_2,
          Scrap **param_3)

{
  stdext::unchecked_fill_n<Scrap_*_*,unsigned_int,Scrap_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
