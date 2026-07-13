/*
 * Entry: 0040bf32
 * Name: APCProcess::DoReload
 * Namespace: APCProcess
 * Signature: void DoReload(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::DoReload(APCProcess *this)

{
  bool bVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  if (pGVar2 != (GameObject *)0x0) {
    bVar1 = APC::FullSoldiers(*(APC **)&this->field_0x2c);
    if (!bVar1) {
                    /* WARNING: Could not recover jumptable at 0x0040bf54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
      return;
    }
  }
  if (((*(GameObject **)&this->field_0x2c)->curCmd).what == CMD_GET_RELOAD) {
    GameObject::ClearCommand(*(GameObject **)&this->field_0x2c);
  }
  *(undefined4 *)&this->field_0x1c = 3;
  return;
}
