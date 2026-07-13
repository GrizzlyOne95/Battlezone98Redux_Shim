/*
 * Entry: 005b9f77
 * Name: symbexec
 * Namespace: Global
 * Signature: uint symbexec(Proto * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl symbexec(Proto *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  int extraout_ECX;
  uint uVar10;
  OpArgMask unaff_EBX;
  uint uVar11;
  int unaff_ESI;
  uint uVar12;
  uint *puVar13;
  Proto *unaff_EDI;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  uint local_1c;
  int local_18;
  uint local_10;
  int local_c;
  
  iVar6 = param_1->sizecode;
  iVar1 = iVar6 + -1;
  if (0xfa < param_1->maxstacksize) {
    return 0;
  }
  bVar3 = param_1->is_vararg;
  uVar8 = (uint)param_1->maxstacksize;
  if (uVar8 < (bVar3 & 1) + (uint)param_1->numparams) {
    return 0;
  }
  if (((bVar3 & 4) != 0) && ((bVar3 & 1) == 0)) {
    return 0;
  }
  if ((int)(uint)param_1->nups < param_1->sizeupvalues) {
    return 0;
  }
  if ((param_1->sizelineinfo != iVar6) && (param_1->sizelineinfo != 0)) {
    return 0;
  }
  if (iVar6 < 1) {
    return 0;
  }
  puVar5 = param_1->code;
  if (((byte)puVar5[iVar6 + -1] & 0x3f) != 0x1e) {
    return 0;
  }
  local_c = 0;
  local_18 = iVar1;
  if (0 < param_2) {
    do {
      puVar13 = puVar5 + local_c;
      uVar10 = *puVar13;
      uVar11 = uVar10 & 0x3f;
      uVar12 = 0;
      uVar14 = uVar10 >> 6 & 0xff;
      local_10 = 0;
      if (0x25 < uVar11) {
        return 0;
      }
      if (uVar8 <= uVar14) {
        return 0;
      }
      bVar4 = luaP_opmodes[uVar11];
      if ((bVar4 & 3) == 0) {
        local_10 = uVar10 >> 0xe & 0x1ff;
        uVar12 = uVar10 >> 0x17;
        iVar6 = checkArgMode(unaff_EDI,unaff_ESI,unaff_EBX);
        if (iVar6 == 0) {
          return 0;
        }
        iVar6 = checkArgMode(unaff_EDI,unaff_ESI,unaff_EBX);
        if (iVar6 == 0) {
          return 0;
        }
      }
      else if ((bVar4 & 3) == 1) {
        uVar12 = uVar10 >> 0xe;
        if (((bVar4 & 0x30) == 0x30) && (param_1->sizek <= (int)uVar12)) {
          return 0;
        }
      }
      else if ((bVar4 & 3) == 2) {
        uVar12 = (uVar10 >> 0xe) - 0x1ffff;
        if ((bVar4 & 0x30) == 0x20) {
          iVar6 = ((uVar10 >> 0xe) - 0x1fffe) + local_c;
          if (iVar6 < 0) {
            return 0;
          }
          if (param_1->sizecode <= iVar6) {
            return 0;
          }
          if (0 < iVar6) {
            local_1c = 0;
            if (0 < iVar6) {
              puVar9 = puVar5 + iVar6 + -1;
              do {
                if ((((byte)*puVar9 & 0x3f) != 0x22) || ((*puVar9 & 0x7fc000) != 0)) break;
                local_1c = local_1c + 1;
                puVar9 = puVar9 + -1;
              } while ((int)local_1c < iVar6);
            }
            if ((local_1c & 1) != 0) {
              return 0;
            }
          }
        }
      }
      if (((luaP_opmodes[uVar11] & 0x40) != 0) && (uVar14 == param_3)) {
        local_18 = local_c;
      }
      if ((char)luaP_opmodes[uVar11] < '\0') {
        if (param_1->sizecode <= local_c + 2) {
          return 0;
        }
        if (((byte)puVar13[1] & 0x3f) != 0x16) {
          return 0;
        }
      }
      iVar6 = local_c;
      iVar7 = local_18;
      if (uVar11 < 0x17) {
        if (uVar11 == 0x16) goto LAB_005ba27c;
        if (7 < uVar11) {
          if (uVar11 == 8) {
LAB_005ba222:
            bVar16 = SBORROW4(uVar12,(uint)param_1->nups);
            bVar15 = (int)(uVar12 - param_1->nups) < 0;
            goto LAB_005ba228;
          }
          if (uVar11 == 0xb) {
            if (uVar8 <= uVar14 + 1) {
              return 0;
            }
            iVar7 = local_c;
            if (param_3 == uVar14 + 1) goto LAB_005ba3b8;
          }
          else if (uVar11 == 0x15) {
            bVar16 = SBORROW4(uVar12,local_10);
            bVar15 = (int)(uVar12 - local_10) < 0;
            goto LAB_005ba228;
          }
          goto switchD_005ba23f_caseD_23;
        }
        if (uVar11 == 7) {
LAB_005ba189:
          if (param_1->k[uVar12].tt != 4) {
            return 0;
          }
        }
        else {
          if (uVar11 == 2) {
            if (local_10 == 1) {
              if (param_1->sizecode <= local_c + 2) {
                return 0;
              }
              if (((byte)puVar13[1] & 0x3f) == 0x22) {
                if ((puVar13[1] & 0x7fc000) == 0) {
                  return 0;
                }
                goto LAB_005ba3b8;
              }
            }
            goto switchD_005ba23f_caseD_23;
          }
          if (uVar11 == 3) {
            if ((param_3 < (int)uVar14) || (iVar7 = local_c, (int)uVar12 < param_3))
            goto switchD_005ba23f_caseD_23;
          }
          else {
            if (uVar11 == 4) goto LAB_005ba222;
            if (uVar11 == 5) goto LAB_005ba189;
          }
        }
        goto LAB_005ba3b8;
      }
      switch(uVar11) {
      case 0x1c:
      case 0x1d:
        if ((uVar12 != 0) && ((int)uVar8 <= (int)((uVar12 - 1) + uVar14))) {
          return 0;
        }
        if (local_10 == 0) {
          iVar7 = luaG_checkopenop(puVar13[1]);
          iVar6 = extraout_ECX;
          if (iVar7 == 0) {
            return 0;
          }
        }
        else if ((local_10 != 1) && ((int)uVar8 <= (int)((local_10 - 2) + uVar14))) {
          return 0;
        }
        goto LAB_005ba262;
      case 0x1e:
        if (0 < (int)(uVar12 - 1)) {
          iVar6 = (uVar12 - 2) + uVar14;
          bVar16 = SBORROW4(iVar6,uVar8);
          bVar15 = (int)(iVar6 - uVar8) < 0;
LAB_005ba228:
          iVar6 = local_c;
          if (bVar16 == bVar15) {
            return 0;
          }
          goto LAB_005ba3b8;
        }
        break;
      case 0x1f:
      case 0x20:
        if (uVar8 <= uVar14 + 3) {
          return 0;
        }
LAB_005ba27c:
        iVar2 = uVar12 + local_c + 1;
        if ((param_3 != 0xff) && (local_c < iVar2)) {
          if (iVar2 <= param_2) {
            iVar6 = uVar12 + local_c;
          }
          goto LAB_005ba3b8;
        }
        break;
      case 0x21:
        if (local_10 == 0) {
          return 0;
        }
        if (uVar8 <= local_10 + 2 + uVar14) {
          return 0;
        }
        uVar14 = uVar14 + 2;
LAB_005ba262:
        iVar7 = iVar6;
        if (param_3 < (int)uVar14) break;
        goto LAB_005ba3b8;
      case 0x22:
        if ((0 < (int)uVar12) && ((int)uVar8 <= (int)(uVar12 + uVar14))) {
          return 0;
        }
        if (local_10 == 0) {
          local_c = local_c + 1;
          bVar16 = SBORROW4(local_c,iVar1);
          bVar15 = local_c - iVar1 < 0;
          goto LAB_005ba228;
        }
        break;
      case 0x24:
        if (param_1->sizep <= (int)uVar12) {
          return 0;
        }
        uVar10 = (uint)param_1->p[uVar12]->nups;
        if (param_1->sizecode <= (int)(uVar10 + local_c)) {
          return 0;
        }
        iVar6 = 1;
        if (uVar10 != 0) {
          do {
            puVar13 = puVar13 + 1;
            if (((*puVar13 & 0x3f) != 4) && ((*puVar13 & 0x3f) != 0)) {
              return 0;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 <= (int)uVar10);
        }
        if (param_3 != 0xff) {
          local_c = uVar10 + local_c;
        }
        break;
      case 0x25:
        if ((param_1->is_vararg & 2) == 0) {
          return 0;
        }
        if ((bVar3 & 4) != 0) {
          return 0;
        }
        if ((uVar12 == 0) && (iVar6 = luaG_checkopenop(puVar13[1]), iVar6 == 0)) {
          return 0;
        }
        if ((int)uVar8 <= (int)((uVar12 - 2) + uVar14)) {
          return 0;
        }
      }
switchD_005ba23f_caseD_23:
      iVar6 = local_c;
      iVar7 = local_18;
LAB_005ba3b8:
      local_18 = iVar7;
      local_c = iVar6 + 1;
    } while (local_c < param_2);
  }
  return puVar5[local_18];
}
