/*
 * Entry: 004e0f66
 * Name: std::pair<unsigned_short_const_,NetPlayer_*>::pair<unsigned_short_const_,NetPlayer_*>
 * Namespace: std::pair<unsigned_short_const_,NetPlayer_*>
 * Signature: pair<unsigned_short_const_,NetPlayer_*> * pair<unsigned_short_const_,NetPlayer_*>(pair<unsigned_short_const_,NetPlayer_*> * this, ushort * param_1, NetPlayer * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_short_const_,NetPlayer_*> * __thiscall
std::pair<unsigned_short_const_,NetPlayer_*>::pair<unsigned_short_const_,NetPlayer_*>
          (pair<unsigned_short_const_,NetPlayer_*> *this,ushort *param_1,NetPlayer **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
