/*
 * Entry: 0040bc41
 * Name: APCProcess::DoAttack
 * Namespace: APCProcess
 * Signature: void DoAttack(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::DoAttack(APCProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    if (((*(GameObject **)&this->field_0x2c)->curCmd).what == CMD_ATTACK) {
      GameObject::ClearCommand(*(GameObject **)&this->field_0x2c);
    }
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0040bc70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
