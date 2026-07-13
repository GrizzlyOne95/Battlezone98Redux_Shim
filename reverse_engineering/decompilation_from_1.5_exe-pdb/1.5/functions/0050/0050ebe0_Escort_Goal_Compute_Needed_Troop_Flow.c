/*
 * Entry: 0050ebe0
 * Name: Escort_Goal::Compute_Needed_Troop_Flow
 * Namespace: Escort_Goal
 * Signature: void Compute_Needed_Troop_Flow(Escort_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Escort_Goal::Compute_Needed_Troop_Flow(Escort_Goal *this)

{
  tag_team *ptVar1;
  int iVar2;
  
  ptVar1 = this->the_team;
  if (ptVar1->AIP == (tagAIP_struct *)0x0) {
    this->_padding_ = this->min_escort_strength;
    iVar2 = this->max_escort_strength;
  }
  else {
    this->_padding_ = ptVar1->AIP->min_escort_force;
    iVar2 = ptVar1->AIP->max_escort_force;
  }
  this->_padding_ = iVar2;
  return;
}
