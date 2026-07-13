/*
 * Entry: 00532dfb
 * Name: std::pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>::pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>
 * Namespace: std::pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>
 * Signature: pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> * pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>(pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> * this, pair<unsigned_short,unsigned_short> * param_1, Ordnance * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> * __thiscall
std::pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>::
pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*>
          (pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> *this,
          pair<unsigned_short,unsigned_short> *param_1,Ordnance **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
