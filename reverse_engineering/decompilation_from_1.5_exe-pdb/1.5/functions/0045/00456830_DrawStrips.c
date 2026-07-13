/*
 * Entry: 00456830
 * Name: DrawStrips
 * Namespace: Global
 * Signature: void DrawStrips(float param_1, float param_2, float param_3, float param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawStrips(float param_1,float param_2,float param_3,float param_4,int *param_5)

{
  Strip *pSVar1;
  uint uVar2;
  long lVar3;
  Team *this;
  ulong uVar4;
  ushort uVar5;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  int iVar6;
  uint uVar7;
  bool bVar8;
  int local_20;
  Strip **local_1c;
  float local_18;
  float local_14;
  long local_10;
  long lStack_c;
  long lStack_8;
  long local_4;
  
  GetStrips(param_1,param_2,param_3,param_4,&local_20,&local_1c);
  iVar6 = 0;
  if (0 < local_20) {
    do {
      pSVar1 = local_1c[iVar6];
      uVar2 = pSVar1->material;
      uVar7 = uVar2 & 0xff;
      uVar5 = (ushort)(uVar2 >> 0x10);
      if (uVar5 != 0) {
        this = Team::GetTeam(1);
        uVar4 = Team::GetAllies(this);
        bVar8 = ((int)uVar2 >> 0x10 & 0xffffU & ~(uVar4 & 0xffff)) == 0;
        uVar7 = (uint)(uVar7 == 1);
        if (bVar8 || ((ushort)uVar4 & uVar5) == 0) {
          if (bVar8) {
            uVar7 = uVar7 + 8;
          }
          else {
            uVar7 = uVar7 + 10;
          }
        }
        else {
          uVar7 = uVar7 + 0xc;
        }
      }
      WorldRect(Terrain.Grid_Size * pSVar1->x0,pSVar1->z0 * Terrain.Grid_Size,
                pSVar1->x1 * Terrain.Grid_Size,pSVar1->z1 * Terrain.Grid_Size,param_5[uVar7]);
      iVar6 = iVar6 + 1;
    } while (iVar6 < local_20);
  }
  iVar6 = 0;
  if (0 < local_20) {
    do {
      lVar3 = DisplayInterface::colorBlack;
      pSVar1 = local_1c[iVar6];
      local_14 = pSVar1->x1 * Terrain.Grid_Size;
      local_18 = pSVar1->z1 * Terrain.Grid_Size;
      (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))
                (Terrain.Grid_Size * pSVar1->x0,pSVar1->z0 * Terrain.Grid_Size,&local_4,&local_10);
      (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))
                (unaff_EBX,unaff_EBP,&local_1c,&local_18);
      Graphic_Rect_Empty(&Device.Viewport,local_4,lStack_8,lStack_c,local_10,lVar3,SOLID_PIXELS);
      iVar6 = iVar6 + 1;
    } while (iVar6 < local_20);
  }
  return;
}
