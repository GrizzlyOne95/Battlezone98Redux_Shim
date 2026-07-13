/*
 * Entry: 004985c1
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Ufill
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * _Ufill(vector<GameObject_*,std::allocator<GameObject_*>_> * this, GameObject * * param_1, uint param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Ufill
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,GameObject **param_1,
          uint param_2,GameObject **param_3)

{
  stdext::unchecked_fill_n<GameObject_*_*,unsigned_int,GameObject_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
