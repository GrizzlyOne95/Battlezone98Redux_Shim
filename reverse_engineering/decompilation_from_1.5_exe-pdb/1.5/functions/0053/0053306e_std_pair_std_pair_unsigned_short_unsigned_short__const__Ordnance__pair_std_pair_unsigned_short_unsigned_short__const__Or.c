/*
 * Entry: 0053306e
 * Name: std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*><std::pair<unsigned_short,unsigned_short>,Ordnance_*>
 * Namespace: std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>
 * Signature: pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*><std::pair<unsigned_short,unsigned_short>,Ordnance_*>(pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * this, pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * __thiscall
std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>::
pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*><std::pair<unsigned_short,unsigned_short>,Ordnance_*>
          (pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *this,
          pair<std::pair<unsigned_short,unsigned_short>,Ordnance_*> *param_1)

{
  this->first = param_1->first;
  this->second = param_1->second;
  return this;
}
