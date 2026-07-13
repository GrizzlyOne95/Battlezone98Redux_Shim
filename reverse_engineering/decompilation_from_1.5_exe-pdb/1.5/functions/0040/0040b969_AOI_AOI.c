/*
 * Entry: 0040b969
 * Name: AOI::AOI
 * Namespace: AOI
 * Signature: AOI * AOI(AOI * this, AiPath * param_1, int param_2, bool param_3, bool param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AOI * __thiscall
AOI::AOI(AOI *this,AiPath *param_1,int param_2,bool param_3,bool param_4,int param_5,int param_6)

{
  this->path = param_1;
  this->interesting = param_3;
  this->inside = param_4;
  this->value = param_5;
  this->force = param_6;
  this->team = param_2;
  _param_3 = this;
  std::list<AOI_*,std::allocator<AOI_*>_>::push_back(&areas,(AOI **)&param_3);
  hasArea[param_2] = true;
  this->bDontSave = false;
  recalc = true;
  return this;
}
