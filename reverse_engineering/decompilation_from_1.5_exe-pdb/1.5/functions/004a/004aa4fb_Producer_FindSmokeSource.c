/*
 * Entry: 004aa4fb
 * Name: Producer::FindSmokeSource
 * Namespace: Producer
 * Signature: void FindSmokeSource(Producer * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::FindSmokeSource(Producer *this,_OBJ76 *param_1)

{
  int *piVar1;
  
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    if (param_1->class_id == CLASS_ID_WEAPON_HARDPOINT) {
      piVar1 = &this->smokeCount;
      this->smokeList[*piVar1] = param_1;
      *piVar1 = *piVar1 + 1;
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      FindSmokeSource(this,param_1->child);
    }
  }
  return;
}
