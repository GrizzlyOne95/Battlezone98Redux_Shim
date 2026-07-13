/*
 * Entry: 00532de1
 * Name: std::pair<unsigned_short,unsigned_short>::pair<unsigned_short,unsigned_short>
 * Namespace: std::pair<unsigned_short,unsigned_short>
 * Signature: pair<unsigned_short,unsigned_short> * pair<unsigned_short,unsigned_short>(pair<unsigned_short,unsigned_short> * this, ushort * param_1, ushort * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_short,unsigned_short> * __thiscall
std::pair<unsigned_short,unsigned_short>::pair<unsigned_short,unsigned_short>
          (pair<unsigned_short,unsigned_short> *this,ushort *param_1,ushort *param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
