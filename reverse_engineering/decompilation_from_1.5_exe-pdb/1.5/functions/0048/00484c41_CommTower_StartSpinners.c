/*
 * Entry: 00484c41
 * Name: CommTower::StartSpinners
 * Namespace: CommTower
 * Signature: void StartSpinners(CommTower * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CommTower::StartSpinners(CommTower *this,_OBJ76 *param_1)

{
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    if (param_1->class_id == CLASS_ID_SPINNER) {
      param_1->flags = param_1->flags & 0xfffffdff;
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      StartSpinners(this,param_1->child);
    }
  }
  return;
}
