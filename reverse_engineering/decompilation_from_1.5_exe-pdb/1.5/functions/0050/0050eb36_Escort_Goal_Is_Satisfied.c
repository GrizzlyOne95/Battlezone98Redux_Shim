/*
 * Entry: 0050eb36
 * Name: Escort_Goal::Is_Satisfied
 * Namespace: Escort_Goal
 * Signature: int Is_Satisfied(Escort_Goal * this, int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Escort_Goal::Is_Satisfied(Escort_Goal *this,int *param_1)

{
  int iVar1;
  
  if (this->_padding_ == 0) {
    if (this->_padding_ != 0) {
      iVar1 = *(int *)(this->_padding_ + 0x34);
      if (this->min_escort_strength <= iVar1) {
        *param_1 = iVar1 - this->min_escort_strength;
        iVar1 = ScavengerProcess::Get_Escort_Count(this->damsels_ai_process);
        return (uint)(this->min_escort_strength <= iVar1);
      }
    }
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}
