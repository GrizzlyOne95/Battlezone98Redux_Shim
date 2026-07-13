/*
 * Entry: 0050ec07
 * Name: Escort_Goal::Compute_Matching_Value
 * Namespace: Escort_Goal
 * Signature: float Compute_Matching_Value(Escort_Goal * this, tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float __thiscall Escort_Goal::Compute_Matching_Value(Escort_Goal *this,tag_squad *param_1)

{
  tagAIP_struct *ptVar1;
  float10 fVar2;
  
  if (this->_padding_ == 0) {
    fVar2 = (float10)(**(code **)(this->_padding_ + 0x10))(param_1);
    if (this->the_team->AIP == (tagAIP_struct *)0x0) {
      fVar2 = fVar2 * (float10)_DAT_0000000c + (float10)this->requested_priority;
    }
    else {
      ptVar1 = this->the_team->AIP;
      fVar2 = fVar2 * (float10)ptVar1->distance_priority + (float10)ptVar1->escort_priority;
    }
    if ((float10)(float)this->_padding_ < fVar2) {
      this->_padding_ = (int)(float)fVar2;
    }
  }
  else {
    fVar2 = (float10)0;
  }
  return (float)fVar2;
}
