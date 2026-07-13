
undefined4 FUN_0082e24d(int param_1,int param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  bool bVar12;
  uint local_18;
  int local_10;
  int local_c;
  
  iVar6 = *(int *)(param_1 + 0x2c);
  local_10 = iVar6 + -1;
  if (((((0xfa < *(byte *)(param_1 + 0x4b)) ||
        (bVar1 = *(byte *)(param_1 + 0x4a),
        (uint)*(byte *)(param_1 + 0x4b) < (bVar1 & 1) + (uint)*(byte *)(param_1 + 0x49))) ||
       (((bVar1 & 4) != 0 && ((bVar1 & 1) == 0)))) ||
      (uVar2 = (uint)*(byte *)(param_1 + 0x48), (int)uVar2 < *(int *)(param_1 + 0x24))) ||
     ((((*(int *)(param_1 + 0x30) != iVar6 && (*(int *)(param_1 + 0x30) != 0)) || (iVar6 < 1)) ||
      (iVar10 = *(int *)(param_1 + 0xc),
      ((byte)*(undefined4 *)(iVar10 + -4 + iVar6 * 4) & 0x3f) != 0x1e)))) {
    return 0;
  }
  local_c = 0;
  if (0 < param_2) {
    do {
      uVar4 = *(uint *)(iVar10 + local_c * 4);
      uVar8 = 0;
      local_18 = 0;
      uVar9 = uVar4 & 0x3f;
      uVar3 = uVar4 >> 6 & 0xff;
      if (0x25 < uVar9) {
        return 0;
      }
      uVar5 = (uint)*(byte *)(param_1 + 0x4b);
      if (uVar5 <= uVar3) {
        return 0;
      }
      bVar1 = (&DAT_00870638)[uVar9];
      if ((bVar1 & 3) == 0) {
        local_18 = uVar4 >> 0xe & 0x1ff;
        uVar8 = uVar4 >> 0x17;
        iVar6 = FUN_0082d9b5(param_1,uVar8,bVar1 >> 4 & 3);
        if (iVar6 == 0) {
          return 0;
        }
        iVar6 = FUN_0082d9b5(param_1,local_18,bVar1 >> 2 & 3);
        if (iVar6 == 0) {
          return 0;
        }
      }
      else if ((bVar1 & 3) == 1) {
        uVar8 = uVar4 >> 0xe;
        if ((((&DAT_00870638)[uVar9] & 0x30) == 0x30) && (*(int *)(param_1 + 0x28) <= (int)uVar8)) {
          return 0;
        }
      }
      else if ((bVar1 & 3) == 2) {
        uVar8 = (uVar4 >> 0xe) - 0x1ffff;
        if (((&DAT_00870638)[uVar9] & 0x30) == 0x20) {
          iVar6 = ((uVar4 >> 0xe) - 0x1fffe) + local_c;
          if (iVar6 < 0) {
            return 0;
          }
          if (*(int *)(param_1 + 0x2c) <= iVar6) {
            return 0;
          }
          if (0 < iVar6) {
            uVar4 = 0;
            if (0 < iVar6) {
              uVar4 = 0;
              puVar7 = (uint *)(*(int *)(param_1 + 0xc) + (iVar6 + -1) * 4);
              do {
                if ((((byte)*puVar7 & 0x3f) != 0x22) || ((*puVar7 & 0x7fc000) != 0)) break;
                uVar4 = uVar4 + 1;
                puVar7 = puVar7 + -1;
              } while ((int)uVar4 < iVar6);
            }
            if ((uVar4 & 1) != 0) {
              return 0;
            }
          }
        }
      }
      if ((((&DAT_00870638)[uVar9] & 0x40) != 0) && (uVar3 == param_3)) {
        local_10 = local_c;
      }
      if ((char)(&DAT_00870638)[uVar9] < '\0') {
        if (*(int *)(param_1 + 0x2c) <= local_c + 2) {
          return 0;
        }
        if (((byte)*(undefined4 *)(*(int *)(param_1 + 0xc) + 4 + local_c * 4) & 0x3f) != 0x16) {
          return 0;
        }
      }
      if (uVar9 < 0x17) {
        if (uVar9 == 0x16) goto LAB_0082e59b;
        if (uVar9 < 8) {
          if (uVar9 == 7) {
LAB_0082e4f3:
            if (*(int *)(*(int *)(param_1 + 8) + 8 + uVar8 * 0x10) != 4) {
              return 0;
            }
            goto switchD_0082e557_caseD_23;
          }
          if (uVar9 == 2) {
            if (local_18 != 1) goto switchD_0082e557_caseD_23;
            if (*(int *)(param_1 + 0x2c) <= local_c + 2) {
              return 0;
            }
            iVar10 = *(int *)(param_1 + 0xc);
            uVar3 = *(uint *)(iVar10 + 4 + local_c * 4);
            if ((((byte)uVar3 & 0x3f) == 0x22) && ((uVar3 & 0x7fc000) == 0)) {
              return 0;
            }
          }
          else {
            if (uVar9 != 3) {
              if (uVar9 == 4) goto LAB_0082e546;
              if (uVar9 == 5) goto LAB_0082e4f3;
              goto switchD_0082e557_caseD_23;
            }
            iVar10 = *(int *)(param_1 + 0xc);
            if (((int)uVar3 <= (int)param_3) && ((int)param_3 <= (int)uVar8)) goto LAB_0082e4b3;
          }
          goto LAB_0082e48e;
        }
        if (uVar9 == 8) {
LAB_0082e546:
          bVar12 = SBORROW4(uVar8,uVar2);
          bVar11 = (int)(uVar8 - uVar2) < 0;
          goto LAB_0082e51b;
        }
        if (uVar9 != 0xb) {
          if (uVar9 == 0x15) {
            bVar12 = SBORROW4(uVar8,local_18);
            bVar11 = (int)(uVar8 - local_18) < 0;
            goto LAB_0082e51b;
          }
          goto switchD_0082e557_caseD_23;
        }
        if (uVar5 <= uVar3 + 1) {
          return 0;
        }
        iVar10 = *(int *)(param_1 + 0xc);
        if (param_3 != uVar3 + 1) goto LAB_0082e48e;
        goto LAB_0082e4b3;
      }
      switch(uVar9) {
      case 0x1c:
      case 0x1d:
        if ((uVar8 != 0) && ((int)uVar5 <= (int)((uVar3 - 1) + uVar8))) {
          return 0;
        }
        if (local_18 == 0) {
          iVar10 = *(int *)(param_1 + 0xc);
          iVar6 = FUN_0082de36(*(undefined4 *)(iVar10 + 4 + local_c * 4));
          if (iVar6 == 0) {
            return 0;
          }
        }
        else {
          if ((local_18 != 1) && ((int)uVar5 <= (int)((local_18 - 2) + uVar3))) {
            return 0;
          }
          iVar10 = *(int *)(param_1 + 0xc);
        }
        goto LAB_0082e57e;
      case 0x1e:
        if (0 < (int)(uVar8 - 1)) {
          iVar6 = (uVar3 - 1) + (uVar8 - 1);
          bVar12 = SBORROW4(iVar6,uVar5);
          bVar11 = (int)(iVar6 - uVar5) < 0;
LAB_0082e51b:
          if (bVar12 == bVar11) {
            return 0;
          }
        }
      default:
switchD_0082e557_caseD_23:
LAB_0082e488:
        iVar10 = *(int *)(param_1 + 0xc);
        break;
      case 0x1f:
      case 0x20:
        if (uVar5 <= uVar3 + 3) {
          return 0;
        }
LAB_0082e59b:
        iVar6 = uVar8 + local_c + 1;
        if ((param_3 != 0xff) && (local_c < iVar6)) {
          iVar10 = *(int *)(param_1 + 0xc);
          if (iVar6 <= param_2) {
            local_c = uVar8 + local_c;
          }
          break;
        }
        goto LAB_0082e488;
      case 0x21:
        if (local_18 == 0) {
          return 0;
        }
        if (uVar5 <= local_18 + 2 + uVar3) {
          return 0;
        }
        iVar10 = *(int *)(param_1 + 0xc);
        uVar3 = uVar3 + 2;
LAB_0082e57e:
        if ((int)uVar3 <= (int)param_3) {
LAB_0082e4b3:
          local_10 = local_c;
        }
        break;
      case 0x22:
        if ((0 < (int)uVar8) && ((int)uVar5 <= (int)(uVar8 + uVar3))) {
          return 0;
        }
        if (local_18 == 0) {
          local_c = local_c + 1;
          if (*(int *)(param_1 + 0x2c) + -1 <= local_c) {
            return 0;
          }
          goto LAB_0082e488;
        }
        goto switchD_0082e557_caseD_23;
      case 0x24:
        if (*(int *)(param_1 + 0x34) <= (int)uVar8) {
          return 0;
        }
        uVar3 = (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + uVar8 * 4) + 0x48);
        if (*(int *)(param_1 + 0x2c) <= (int)(uVar3 + local_c)) {
          return 0;
        }
        iVar6 = 1;
        if (uVar3 != 0) {
          puVar7 = (uint *)(*(int *)(param_1 + 0xc) + (local_c + 1) * 4);
          do {
            if (((*puVar7 & 0x3f) != 4) && ((*puVar7 & 0x3f) != 0)) {
              return 0;
            }
            iVar6 = iVar6 + 1;
            puVar7 = puVar7 + 1;
          } while (iVar6 <= (int)uVar3);
        }
        iVar10 = *(int *)(param_1 + 0xc);
        if (param_3 != 0xff) {
          local_c = uVar3 + local_c;
        }
        break;
      case 0x25:
        if ((*(byte *)(param_1 + 0x4a) & 2) == 0) {
          return 0;
        }
        if ((*(byte *)(param_1 + 0x4a) & 4) != 0) {
          return 0;
        }
        iVar10 = *(int *)(param_1 + 0xc);
        if ((uVar8 - 1 == -1) &&
           (iVar6 = FUN_0082de36(*(undefined4 *)(iVar10 + 4 + local_c * 4)), iVar6 == 0)) {
          return 0;
        }
        if ((int)uVar5 <= (int)((uVar3 - 1) + (uVar8 - 1))) {
          return 0;
        }
      }
LAB_0082e48e:
      local_c = local_c + 1;
    } while (local_c < param_2);
  }
  return *(undefined4 *)(iVar10 + local_10 * 4);
}

