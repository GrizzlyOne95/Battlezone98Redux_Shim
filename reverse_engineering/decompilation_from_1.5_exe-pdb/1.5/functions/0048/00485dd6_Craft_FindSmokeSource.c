/*
 * Entry: 00485dd6
 * Name: Craft::FindSmokeSource
 * Namespace: Craft
 * Signature: void FindSmokeSource(Craft * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::FindSmokeSource(Craft *this,_OBJ76 *param_1)

{
  long *plVar1;
  
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    if (param_1->class_id == CLASS_ID_SMOKE_EMITTER) {
      plVar1 = &this->smokeCount;
      this->smokeList[*plVar1] = param_1;
      *plVar1 = *plVar1 + 1;
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      FindSmokeSource(this,param_1->child);
    }
  }
  return;
}
