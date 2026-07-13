/*
 * Entry: 00535733
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Ufill
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: OrdnanceClass * * _Ufill(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, OrdnanceClass * * param_1, uint param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Ufill
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,OrdnanceClass **param_1,
          uint param_2,OrdnanceClass **param_3)

{
  stdext::unchecked_fill_n<OrdnanceClass_*_*,unsigned_int,OrdnanceClass_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
