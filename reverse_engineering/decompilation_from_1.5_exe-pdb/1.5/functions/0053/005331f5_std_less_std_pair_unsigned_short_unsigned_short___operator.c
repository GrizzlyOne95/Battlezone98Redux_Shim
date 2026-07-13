/*
 * Entry: 005331f5
 * Name: std::less<std::pair<unsigned_short,unsigned_short>_>::operator()
 * Namespace: std::less<std::pair<unsigned_short,unsigned_short>_>
 * Signature: bool operator()(less<std::pair<unsigned_short,unsigned_short>_> * this, pair<unsigned_short,unsigned_short> * param_1, pair<unsigned_short,unsigned_short> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::less<std::pair<unsigned_short,unsigned_short>_>::operator()
          (less<std::pair<unsigned_short,unsigned_short>_> *this,
          pair<unsigned_short,unsigned_short> *param_1,pair<unsigned_short,unsigned_short> *param_2)

{
  bool bVar1;
  
  bVar1 = operator<<unsigned_short,unsigned_short>(param_1,param_2);
  return bVar1;
}
