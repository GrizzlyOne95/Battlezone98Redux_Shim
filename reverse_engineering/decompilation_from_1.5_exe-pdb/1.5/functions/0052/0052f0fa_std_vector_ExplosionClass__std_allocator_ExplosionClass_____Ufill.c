/*
 * Entry: 0052f0fa
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Ufill
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: ExplosionClass * * _Ufill(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, ExplosionClass * * param_1, uint param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Ufill
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,ExplosionClass **param_1
          ,uint param_2,ExplosionClass **param_3)

{
  stdext::unchecked_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
            (param_1,param_2,param_3);
  return param_1 + param_2;
}
