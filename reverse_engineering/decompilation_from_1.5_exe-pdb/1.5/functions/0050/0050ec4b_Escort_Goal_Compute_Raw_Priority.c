/*
 * Entry: 0050ec4b
 * Name: Escort_Goal::Compute_Raw_Priority
 * Namespace: Escort_Goal
 * Signature: float Compute_Raw_Priority(Escort_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Escort_Goal::Compute_Raw_Priority(Escort_Goal *this)

{
  float fVar1;
  tagAIP_struct *ptVar2;
  
  if (this->_padding_ != 0) {
    return 0.0;
  }
  ptVar2 = this->the_team->AIP;
  if (ptVar2 == (tagAIP_struct *)0x0) {
    fVar1 = this->requested_priority;
  }
  else {
    fVar1 = (float)ptVar2->escort_priority;
  }
  this->_padding_ = (int)fVar1;
  return (float)this->_padding_;
}
