/*
 * Entry: 0055ba16
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::_Ufill
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: Player * * _Ufill(vector<Player_*,std::allocator<Player_*>_> * this, Player * * param_1, uint param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::_Ufill
          (vector<Player_*,std::allocator<Player_*>_> *this,Player **param_1,uint param_2,
          Player **param_3)

{
  stdext::unchecked_fill_n<Player_*_*,unsigned_int,Player_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
