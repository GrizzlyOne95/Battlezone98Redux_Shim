/*
 * Entry: 0058259d
 * Name: TextInput_ProcessInput
 * Namespace: Global
 * Signature: ulong TextInput_ProcessInput(void * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl TextInput_ProcessInput(void *param_1,uint param_2,uint param_3,long param_4)

{
  int *piVar1;
  int iVar2;
  INPUT_REGION *pIVar3;
  uint uVar4;
  code *pcVar5;
  INPUT_REGION *pIVar6;
  void *pvVar7;
  ulong uVar8;
  ulong unaff_ESI;
  INPUT_REGION *unaff_EDI;
  int iVar9;
  undefined4 uVar10;
  
  iVar2 = *(int *)((int)param_1 + 8);
  if ((*(uint *)(iVar2 + 0x124) & 0x100) == 0) {
    return 0;
  }
  if (param_2 == 0x100) {
    if (param_3 < 0x26) {
      if (param_3 == 0x25) {
        uVar4 = *(uint *)(iVar2 + 0x110);
        if (*(uint *)(iVar2 + 0x108) < uVar4) {
          *(uint *)(iVar2 + 0x110) = uVar4 - 1;
          TextInput_AdjustScrollPosLeft(unaff_EDI,unaff_ESI);
        }
        goto LAB_00582780;
      }
      if (param_3 == 8) {
        uVar4 = *(uint *)(iVar2 + 0x110);
        if (*(uint *)(iVar2 + 0x108) < uVar4) {
          pvVar7 = (void *)(uVar4 + iVar2 + 0x10);
          pIVar6 = (INPUT_REGION *)(uVar4 + iVar2 + 0xf);
          memmove(pIVar6,pvVar7,(*(int *)(iVar2 + 0x104) - uVar4) + 2);
          *(int *)(iVar2 + 0x110) = *(int *)(iVar2 + 0x110) + -1;
          piVar1 = (int *)(iVar2 + 0x10c);
          *piVar1 = *piVar1 + -1;
          TextInput_AdjustScrollPosLeft(pIVar6,(ulong)pvVar7);
          TextInput_AdjustScrollPosRightIfLower((INPUT_REGION *)*piVar1,(ulong)pIVar6);
        }
        *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
        goto LAB_0058283e;
      }
      if (param_3 == 0xd) {
        pcVar5 = *(code **)(iVar2 + 0x128);
        if (pcVar5 != (code *)0x0) {
          iVar9 = *(int *)(iVar2 + 0x108) + 0x10 + iVar2;
LAB_00582685:
          (*pcVar5)(param_1,iVar9);
        }
      }
      else {
        if (param_3 != 0x1b) {
          if (param_3 == 0x23) {
            pIVar3 = *(INPUT_REGION **)(iVar2 + 0x10c);
            pIVar6 = (INPUT_REGION *)((int)&pIVar3->x + 1);
            if (pIVar6 < *(INPUT_REGION **)(iVar2 + 0x104)) {
              *(INPUT_REGION **)(iVar2 + 0x110) = pIVar6;
            }
            else {
              *(INPUT_REGION **)(iVar2 + 0x110) = pIVar3;
              pIVar6 = pIVar3;
            }
            goto LAB_0058264f;
          }
          if (param_3 != 0x24) {
            return 0;
          }
          *(undefined4 *)(iVar2 + 0x110) = *(undefined4 *)(iVar2 + 0x108);
          if (*(int *)(iVar2 + 0x114) != 0) {
            *(int *)(iVar2 + 0x114) = 0;
            *(undefined4 *)(iVar2 + 0x118) = 0;
          }
          *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
          goto LAB_0058283e;
        }
        memset(iVar2 + 0x10,0,0xf0);
        pcVar5 = *(code **)(iVar2 + 0x128);
        *(undefined4 *)(iVar2 + 0x10c) = 0;
        *(undefined4 *)(iVar2 + 0x110) = 0;
        if (pcVar5 != (code *)0x0) {
          iVar9 = 0;
          goto LAB_00582685;
        }
      }
      uVar8 = 2;
    }
    else {
      if (param_3 == 0x26) {
        pcVar5 = *(code **)(iVar2 + 300);
        if (pcVar5 != (code *)0x0) {
          uVar10 = 1;
LAB_005827c9:
          (*pcVar5)(param_1,uVar10);
        }
        goto LAB_0058283e;
      }
      if (param_3 == 0x27) {
        uVar4 = *(uint *)(iVar2 + 0x110);
        if (uVar4 <= *(uint *)(iVar2 + 0x10c)) {
          pIVar6 = (INPUT_REGION *)(uVar4 + 1);
          *(uint *)(iVar2 + 0x110) = (uint)pIVar6;
LAB_0058264f:
          TextInput_AdjustScrollPosRight(pIVar6,(ulong)unaff_EDI);
        }
      }
      else {
        if (param_3 == 0x28) {
          pcVar5 = *(code **)(iVar2 + 300);
          if (pcVar5 != (code *)0x0) {
            uVar10 = 0;
            goto LAB_005827c9;
          }
          goto LAB_0058283e;
        }
        if (param_3 != 0x2e) {
          return 0;
        }
        uVar4 = *(uint *)(iVar2 + 0x110);
        if (uVar4 < *(int *)(iVar2 + 0x10c) + 1U) {
          pvVar7 = (void *)(uVar4 + iVar2 + 0x10);
          memmove(pvVar7,(void *)(uVar4 + iVar2 + 0x11),0xef - uVar4);
          *(int *)(iVar2 + 0x10c) = *(int *)(iVar2 + 0x10c) + -1;
          *(undefined1 *)(iVar2 + 0xff) = 0;
          TextInput_AdjustScrollPosRightIfLower(*(INPUT_REGION **)(iVar2 + 0x10c),(ulong)pvVar7);
        }
      }
LAB_00582780:
      uVar8 = 1;
    }
    *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
  }
  else {
    if ((param_2 != 0x102) || (0xdf < param_3 - 0x20)) {
      return 0;
    }
    if (*(int *)(iVar2 + 0x10c) != *(int *)(iVar2 + 0x104)) {
      iVar9 = *(int *)(iVar2 + 0x110) + iVar2;
      pvVar7 = (void *)(iVar9 + 0x11);
      memmove(pvVar7,(void *)(iVar9 + 0x10),(*(int *)(iVar2 + 0x104) - *(int *)(iVar2 + 0x110)) + 2)
      ;
      *(char *)(iVar2 + 0x10 + *(int *)(iVar2 + 0x110)) = (char)param_3;
      *(int *)(iVar2 + 0x110) = *(int *)(iVar2 + 0x110) + 1;
      *(int *)(iVar2 + 0x10c) = *(int *)(iVar2 + 0x10c) + 1;
      *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
      TextInput_AdjustScrollPosRight(*(INPUT_REGION **)(iVar2 + 0x110),(ulong)pvVar7);
    }
LAB_0058283e:
    uVar8 = 1;
  }
  return uVar8;
}
