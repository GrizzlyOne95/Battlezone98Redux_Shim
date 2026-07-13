/*
 * Entry: 0055b9f6
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::_Ufill
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: Session * * _Ufill(vector<Session_*,std::allocator<Session_*>_> * this, Session * * param_1, uint param_2, Session * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::_Ufill
          (vector<Session_*,std::allocator<Session_*>_> *this,Session **param_1,uint param_2,
          Session **param_3)

{
  stdext::unchecked_fill_n<Session_*_*,unsigned_int,Session_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
