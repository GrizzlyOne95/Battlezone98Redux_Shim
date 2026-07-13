/*
 * Entry: 004ae2f7
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Ufill
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: Scanner * * _Ufill(vector<Scanner_*,std::allocator<Scanner_*>_> * this, Scanner * * param_1, uint param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Ufill
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,Scanner **param_1,uint param_2,
          Scanner **param_3)

{
  stdext::unchecked_fill_n<Scanner_*_*,unsigned_int,Scanner_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
