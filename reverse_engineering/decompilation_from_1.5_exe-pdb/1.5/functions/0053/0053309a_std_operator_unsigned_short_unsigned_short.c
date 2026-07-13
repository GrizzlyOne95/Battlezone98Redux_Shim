/*
 * Entry: 0053309a
 * Name: std::operator<<unsigned_short,unsigned_short>
 * Namespace: std
 * Signature: bool operator<<unsigned_short,unsigned_short>(pair<unsigned_short,unsigned_short> * param_1, pair<unsigned_short,unsigned_short> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
std::operator<<unsigned_short,unsigned_short>
          (pair<unsigned_short,unsigned_short> *param_1,pair<unsigned_short,unsigned_short> *param_2
          )

{
  if ((param_2->first <= param_1->first) &&
     ((param_2->first < param_1->first || (param_2->second <= param_1->second)))) {
    return false;
  }
  return true;
}
