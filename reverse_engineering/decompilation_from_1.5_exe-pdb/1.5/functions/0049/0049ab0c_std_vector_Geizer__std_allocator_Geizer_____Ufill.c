/*
 * Entry: 0049ab0c
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Ufill
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: Geizer * * _Ufill(vector<Geizer_*,std::allocator<Geizer_*>_> * this, Geizer * * param_1, uint param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Ufill
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,Geizer **param_1,uint param_2,
          Geizer **param_3)

{
  stdext::unchecked_fill_n<Geizer_*_*,unsigned_int,Geizer_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
