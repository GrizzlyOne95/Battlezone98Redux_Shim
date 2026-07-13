/*
 * Entry: 004b3ba1
 * Name: TurretCraft::FindTurret
 * Namespace: TurretCraft
 * Signature: void FindTurret(TurretCraft * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::FindTurret(TurretCraft *this,_OBJ76 *param_1)

{
  int *piVar1;
  char cVar2;
  
  do {
    if (param_1 == (_OBJ76 *)0x0) {
      return;
    }
    if (param_1->class_id == CLASS_ID_TURRET_GEOMETRY) {
      cVar2 = *(char *)((int)&param_1->id + 6);
      if (cVar2 == 'X') {
LAB_004b3beb:
        piVar1 = &this->turretXCount;
        this->turretXObj[*piVar1] = param_1;
        *piVar1 = *piVar1 + 1;
      }
      else {
        if (cVar2 != 'Y') {
          if (cVar2 == 'x') goto LAB_004b3beb;
          if (cVar2 != 'y') {
            Trace("Unusual turret id \"%.8s\" in object \"%.8s\"; assuming Y\n");
          }
        }
        this->turretYObj = param_1;
      }
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      FindTurret(this,param_1->child);
    }
    param_1 = param_1->sibling;
  } while( true );
}
