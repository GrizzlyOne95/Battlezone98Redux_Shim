/*
 * Entry: 0047894d
 * Name: ControlWeapons
 * Namespace: Global
 * Signature: void ControlWeapons(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ControlWeapons(void)

{
  int iVar1;
  tagENTITY *ptVar2;
  float fVar3;
  
  iVar1 = UserPref_arcadeMode();
  if (iVar1 == 0) {
    ptVar2 = FirstCollidable();
    while (ptVar2 != (tagENTITY *)0x0) {
      Vector_Transform(&ptVar2->worldOrigin,&(ptVar2->bSphere).origin,1,&ptVar2->obj76->transform);
      ptVar2 = NextCollidable();
    }
    fVar3 = TimeStep();
    Weapon_ControlAll(fVar3);
    fVar3 = TimeStep();
    Ordnance_ControlAll(fVar3);
    fVar3 = TimeStep();
    Weapon_SimulateAll(fVar3);
    iVar1 = Net_IsNetGame();
    if (iVar1 != 0) {
      Ordnance_SendNew();
    }
    fVar3 = TimeStep();
    Ordnance_SimulateAll(fVar3);
  }
  return;
}
