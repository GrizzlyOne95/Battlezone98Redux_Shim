/*
 * Entry: 0050ec6d
 * Name: Escort_Goal::Is_Unit_Appropriate
 * Namespace: Escort_Goal
 * Signature: int Is_Unit_Appropriate(Escort_Goal * this, tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Escort_Goal::Is_Unit_Appropriate(Escort_Goal *this,tagUNIT *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (this->_padding_ == 0) {
    iVar2 = (*(code *)**(undefined4 **)(param_1->id + 0x20))();
    uVar1 = (uint)(*(int *)(iVar2 + 0x20) == 0x57494e47);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
