/*
 * Entry: 0052272a
 * Name: BuildShadows
 * Namespace: Global
 * Signature: void BuildShadows(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildShadows(void)

{
  int iVar1;
  float fVar2;
  float fVar3;
  undefined4 extraout_EAX;
  int iVar4;
  uchar *puVar5;
  uint unaff_ESI;
  uint uVar6;
  int unaff_EDI;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float fVar7;
  double dVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  ulonglong uVar11;
  int in_stack_ffffffdc;
  uint local_18;
  int local_14;
  int local_c;
  int local_8;
  
  if (Sun_Light.y <= 0.999) {
    Set_Rounding(in_stack_ffffffdc);
    fpatan((float10)Sun_Light.z,(float10)Sun_Light.x);
    _ftol2_sse();
    dVar8 = rsqrt((double)(extraout_ST0 * extraout_ST0 + extraout_ST1 * extraout_ST1));
    fVar2 = (float)dVar8 * Sun_Light.y;
    if ((0.999 <= Sun_Light.x) || (Sun_Light.x <= -0.999)) {
      fVar3 = Sun_Light.z / Sun_Light.x;
    }
    else {
      fVar3 = 0.0;
    }
    Trace("Building shadows");
    uVar11 = (ulonglong)unaff_ESI;
    local_18 = 0;
    do {
      if (Terrain.Zone_Page_Table[local_18] != &Empty_Zone) {
        uVar6 = local_18 & 0x8000007f;
        if ((int)uVar6 < 0) {
          uVar6 = (uVar6 - 1 | 0xffffff80) + 1;
        }
        local_c = 0;
        do {
          iVar1 = local_c + (((int)(local_18 + ((int)local_18 >> 0x1f & 0x7fU)) >> 7) + -0x18) *
                            0x80;
          local_14 = 0x80;
          local_8 = (uVar6 - 0x18) * 0x80;
          do {
            dVar8 = (double)fVar2;
            uVar9 = (undefined4)((ulonglong)(double)fVar3 >> 0x20);
            iVar4 = iVar1;
            uVar10 = extraout_EAX;
            fVar7 = GetTerrainHeight(local_8,iVar1);
            iVar4 = GridInShadow(local_8,fVar7,iVar4,(double)CONCAT44(SUB84(dVar8,0),uVar9),
                                 (double)CONCAT44(uVar10,(int)((ulonglong)dVar8 >> 0x20)),unaff_EDI)
            ;
            if (iVar4 != 0) {
              puVar5 = GetNormalPtr(unaff_EDI,(int)uVar11);
              *puVar5 = '\0';
            }
            local_8 = local_8 + 1;
            local_14 = local_14 + -1;
          } while (local_14 != 0);
          local_c = local_c + 1;
        } while (local_c < 0x80);
        Trace(".");
      }
      local_18 = local_18 + 1;
    } while ((int)local_18 < 0x4000);
    Trace("\n");
    Set_Rounding(unaff_EDI);
  }
  return;
}
