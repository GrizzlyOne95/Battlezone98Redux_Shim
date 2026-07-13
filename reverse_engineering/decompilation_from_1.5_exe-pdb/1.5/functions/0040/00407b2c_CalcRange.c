/*
 * Entry: 00407b2c
 * Name: CalcRange
 * Namespace: Global
 * Signature: void CalcRange(Craft * param_1, float * param_2, float * param_3, float * param_4, Weapon * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CalcRange(Craft *param_1,float *param_2,float *param_3,float *param_4,Weapon **param_5)

{
  uint uVar1;
  float *pfVar2;
  Weapon **ppWVar3;
  bool bVar4;
  Weapon *pWVar5;
  float local_10;
  float local_c;
  Carrier *local_8;
  
  ppWVar3 = param_5;
  pfVar2 = param_3;
  *param_2 = 0.0;
  *param_3 = 10.0;
  *param_4 = 1.0;
  *param_5 = (Weapon *)0x0;
  local_8 = (Carrier *)param_1->_padding_;
  if (local_8 != (Carrier *)0x0) {
    uVar1 = param_1->_padding_;
    param_3 = (float *)0x0;
    do {
      if ((uVar1 & 1 << ((byte)param_3 & 0x1f)) != 0) {
        pWVar5 = Carrier::GetWeapon(local_8,(int)param_3);
        if (pWVar5 != (Weapon *)0x0) {
          if (*ppWVar3 == (Weapon *)0x0) {
            *ppWVar3 = pWVar5;
          }
          bVar4 = CalcRange(pWVar5,&local_c,(float *)&param_5,&local_10);
          if (bVar4) {
            if (((*ppWVar3)->weaponClass->sig != 0x44495350) &&
               (pWVar5->weaponClass->sig == 0x44495350)) {
              param_5 = (Weapon **)0xf149f2ca;
            }
            if (*pfVar2 < (float)param_5) {
              *param_2 = local_c;
              *pfVar2 = (float)param_5;
              *param_4 = local_10;
              *ppWVar3 = pWVar5;
            }
          }
        }
      }
      param_3 = (float *)((int)param_3 + 1);
    } while ((int)param_3 < 5);
    *pfVar2 = *pfVar2 - 1.0;
  }
  return;
}
