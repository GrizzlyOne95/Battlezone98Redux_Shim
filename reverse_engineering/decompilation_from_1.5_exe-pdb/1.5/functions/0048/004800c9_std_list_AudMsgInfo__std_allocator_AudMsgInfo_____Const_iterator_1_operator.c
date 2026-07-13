/*
 * Entry: 004800c9
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator!=
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>
 * Signature: bool operator!=(_Const_iterator<1> * this, _Const_iterator<1> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator!=
          (_Const_iterator<1> *this,_Const_iterator<1> *param_1)

{
  bool bVar1;
  
  bVar1 = operator==(this,param_1);
  return !bVar1;
}
