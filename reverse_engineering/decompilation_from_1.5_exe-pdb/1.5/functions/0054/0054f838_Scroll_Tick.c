/*
 * Entry: 0054f838
 * Name: Scroll_Tick
 * Namespace: Global
 * Signature: void Scroll_Tick(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_Tick(void)

{
  int *piVar1;
  int iVar2;
  wrap_struct *pwVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  float fVar11;
  int local_14;
  uint local_c;
  FONT *local_8;
  
  local_8 = Default_Font;
  iVar6 = IsJapanese();
  lVar5 = Device.Viewport.Height;
  lVar4 = Device.Viewport.Width;
  pwVar3 = region_list;
  if (iVar6 != 0) {
    local_8 = J_Font;
  }
  do {
    if (pwVar3 == (wrap_struct *)0x0) {
      resWidth = lVar4;
      resHeight = lVar5;
      return;
    }
    piVar1 = pwVar3->ptr;
    if ((piVar1[0x18] & 2U) != 0) {
      iVar6 = piVar1[9];
      if (iVar6 != 0) {
        if ((piVar1[0x18] & 4U) == 0) {
          uVar7 = iVar6 - 1;
        }
        else {
          uVar7 = iVar6 - 4;
        }
        piVar1[9] = uVar7;
        if ((uVar7 & 3) == 0) {
          uVar7 = piVar1[4] + 5;
          uVar9 = (piVar1[7] + 1U) % uVar7;
          piVar1[7] = uVar9;
          iVar6 = ((uVar9 + 4 + piVar1[4]) % uVar7) * 0x58;
          *(undefined4 *)(iVar6 + 0x50 + piVar1[10]) = 0xbf800000;
          *(undefined4 *)(iVar6 + 0x54 + piVar1[10]) = 0;
          *(undefined1 *)(iVar6 + piVar1[10]) = 0;
        }
      }
      iVar6 = piVar1[9];
      iVar2 = piVar1[6];
      Font_Set_Background(local_8,-1);
      local_c = 0;
      local_14 = 0;
      if (piVar1[4] != -1) {
        do {
          uVar7 = (piVar1[7] + local_c) % (piVar1[4] + 5U);
          if ((*(byte *)(piVar1 + 0x18) & 1) == 0) {
LAB_0054f97a:
            iVar8 = uVar7 * 0x58;
            if (*(char *)(iVar8 + piVar1[10]) != '\0') {
              if (piVar1[0xd] == -1) {
                Font_Reset_Tabs();
              }
              else {
                Font_Set_Tabs(piVar1[0xd],piVar1 + 0xe);
              }
              uVar7 = (uint)(((Device.Viewport.Pane.x1 - Device.Viewport.Pane.x0) + 1) * *piVar1) /
                      0x280;
              iVar10 = ((uint)(((Device.Viewport.Pane.y1 - Device.Viewport.Pane.y0) + 1) * piVar1[1]
                              ) / 0x1e0 - ((-iVar6 & 3U) * iVar2 >> 2)) + local_14;
              Font_Set_Foreground(local_8,0);
              Font_Print_String(local_8,&Device.Viewport,uVar7 + 1,iVar10 + 1,
                                (char *)(piVar1[10] + iVar8));
              Font_Set_Foreground(local_8,*(long *)(iVar8 + 0x54 + piVar1[10]));
              Font_Print_String(local_8,&Device.Viewport,uVar7,iVar10,(char *)(piVar1[10] + iVar8));
              if (piVar1[0xd] != -1) {
                Font_Reset_Tabs();
              }
            }
          }
          else {
            iVar8 = piVar1[10];
            iVar10 = uVar7 * 0x58;
            fVar11 = Get_TimeLocal();
            if (fVar11 <= *(float *)(iVar10 + 0x50 + iVar8)) {
              if ((float)piVar1[0x17] == -1.0) {
                piVar1[0x17] = *(int *)(iVar10 + 0x50 + piVar1[10]);
              }
            }
            else {
              *(undefined4 *)(iVar10 + 0x50 + piVar1[10]) = 0xbf800000;
            }
            if (0.0 <= *(float *)(iVar10 + 0x50 + piVar1[10])) goto LAB_0054f97a;
          }
          local_14 = local_14 + piVar1[6];
          local_c = local_c + 1;
        } while (local_c < piVar1[4] + 1U);
      }
      if (piVar1[9] == 0) {
        piVar1[0x18] = piVar1[0x18] & 0x7fffffff;
      }
    }
    pwVar3 = pwVar3->next;
  } while( true );
}
