/*
 * Entry: 004079c4
 * Name: CalcRange
 * Namespace: Global
 * Signature: bool CalcRange(Weapon * param_1, float * param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CalcRange(Weapon *param_1,float *param_2,float *param_3,float *param_4)

{
  WeaponClass *pWVar1;
  ulong uVar2;
  ExplosionClass *pEVar3;
  _OBJ76 *p_Var4;
  OrdnanceClass *pOVar5;
  float fVar6;
  
  fVar6 = 0.0;
  *param_2 = 0.0;
  pWVar1 = param_1->weaponClass;
  *param_3 = 10.0;
  *param_4 = 1.0;
  uVar2 = pWVar1->sig;
  if ((uVar2 == 0x44495350) || (uVar2 == 0x5244524c)) {
    pOVar5 = param_1->ordnanceClass;
    if (pOVar5 != (OrdnanceClass *)0x0) {
      if ((*(int *)pOVar5->odf == 0x50524f58) || (*(int *)pOVar5->odf != 0x544f5250)) {
        *param_3 = 50.0;
        pEVar3 = (ExplosionClass *)0x3f800000;
      }
      else {
        if (pOVar5[3].ammoCost != 0) {
          *param_2 = *(float *)(pOVar5[3].ammoCost + 0x50);
        }
        *param_3 = *(float *)(pOVar5[3].odf + 0xc) * (float)pOVar5[3].xplGround;
        pEVar3 = pOVar5[3].xplGround;
      }
      goto LAB_00407b23;
    }
  }
  else {
    pOVar5 = param_1->ordnanceClass;
    if (pOVar5 != (OrdnanceClass *)0x0) {
LAB_00407a40:
      pEVar3 = pOVar5->xplGround;
      if ((pEVar3 != (ExplosionClass *)0x0) && (fVar6 = 0.0, pEVar3->damageRadius != 0.0)) {
        fVar6 = Max(0.0,pEVar3->damageRadius);
      }
      pEVar3 = pOVar5->xplVehicle;
      if ((pEVar3 != (ExplosionClass *)0x0) && (pEVar3->damageRadius != 0.0)) {
        fVar6 = Max(fVar6,pEVar3->damageRadius);
      }
      pEVar3 = pOVar5->xplBuilding;
      if ((pEVar3 != (ExplosionClass *)0x0) && (pEVar3->damageRadius != 0.0)) {
        fVar6 = Max(fVar6,pEVar3->damageRadius);
      }
      *param_2 = fVar6;
      *param_3 = pOVar5->shotSpeed * pOVar5->lifeSpan;
      pEVar3 = (ExplosionClass *)pOVar5->lifeSpan;
LAB_00407b23:
      *param_4 = (float)pEVar3;
      return true;
    }
    if (uVar2 == 0x43485247) {
      for (p_Var4 = param_1[1].owner; p_Var4 <= *(_OBJ76 **)&param_1[1].field_0x1c;
          p_Var4 = (_OBJ76 *)&(p_Var4->transform).right_y) {
        if (*(int *)&p_Var4->field_0x1c != 0) {
          pOVar5 = *(OrdnanceClass **)&p_Var4->field_0x1c;
          if (pOVar5 == (OrdnanceClass *)0x0) {
            return false;
          }
          goto LAB_00407a40;
        }
      }
    }
  }
  return false;
}
