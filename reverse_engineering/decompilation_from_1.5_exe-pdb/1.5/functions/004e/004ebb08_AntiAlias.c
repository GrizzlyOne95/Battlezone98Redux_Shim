/*
 * Entry: 004ebb08
 * Name: AntiAlias
 * Namespace: Global
 * Signature: void AntiAlias(_GRAPHIC_BUFFER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AntiAlias(_GRAPHIC_BUFFER *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  _GRAPHIC_BUFFER *p_Var5;
  uchar uVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  p_Var5 = param_1;
  local_8 = 0;
  if (param_1->Height != 2 && -1 < param_1->Height + -2) {
    do {
      iVar1 = p_Var5->Width;
      iVar9 = iVar1 * local_8;
      iVar8 = 0;
      if (iVar1 != 2 && -1 < iVar1 + -2) {
        do {
          Get_RGB_Values((uint)p_Var5->Buffer[iVar9 + iVar8],&local_14,&local_24,&local_34);
          Get_RGB_Values((uint)p_Var5->Buffer[iVar9 + iVar8 + 1],&local_10,&local_20,&local_30);
          Get_RGB_Values((uint)p_Var5->Buffer[iVar9 + iVar8 + p_Var5->Width],&local_c,&local_1c,
                         &local_2c);
          Get_RGB_Values((uint)p_Var5->Buffer[iVar9 + iVar8 + p_Var5->Width + 1],(float *)&param_1,
                         &local_18,&local_28);
          fVar2 = ((float)param_1 + local_c + local_10 + local_14) * 0.25;
          fVar4 = (local_18 + local_1c + local_20 + local_24) * 0.25;
          fVar3 = (local_28 + local_2c + local_30 + local_34) * 0.25;
          if (((0.00392 <= fVar2) || (0.00392 <= fVar4)) || (0.00392 <= fVar3)) {
            lVar7 = Get_Closest_RGB_Entry(fVar2,fVar4,fVar3);
            uVar6 = (uchar)lVar7;
          }
          else {
            uVar6 = 0xff;
          }
          p_Var5->Buffer[iVar9 + iVar8] = uVar6;
          p_Var5->Buffer[iVar9 + iVar8 + 1] = uVar6;
          p_Var5->Buffer[iVar9 + iVar8 + p_Var5->Width] = uVar6;
          p_Var5->Buffer[iVar9 + iVar8 + p_Var5->Width + 1] = uVar6;
          iVar8 = iVar8 + 2;
        } while (iVar8 < p_Var5->Width + -2);
      }
      local_8 = local_8 + 2;
    } while (local_8 < p_Var5->Height + -2);
  }
  return;
}
