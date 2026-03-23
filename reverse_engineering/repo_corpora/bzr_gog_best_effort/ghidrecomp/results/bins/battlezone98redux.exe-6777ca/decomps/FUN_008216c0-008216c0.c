
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008216c0(void)

{
  float *pfVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  ulong *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  float10 fVar11;
  int local_20;
  uint local_18;
  undefined4 *local_14;
  
  uVar7 = DAT_02cecee4;
  uVar6 = DAT_02cecee0;
  puVar5 = DAT_0091552c;
  local_14 = DAT_02cc1b0c;
  do {
    if (local_14 == (undefined4 *)0x0) {
      _DAT_02cc1b10 = uVar6;
      _DAT_02cc1b14 = uVar7;
      return;
    }
    piVar2 = (int *)local_14[2];
    if ((piVar2[0x17] & 2U) != 0) {
      if (piVar2[9] != 0) {
        if ((piVar2[0x17] & 4U) == 0) {
          piVar2[9] = piVar2[9] + -1;
        }
        else {
          piVar2[9] = piVar2[9] + -4;
        }
        if ((uint)piVar2[9] % 4 == 0) {
          piVar2[7] = (piVar2[7] + 1U) % (piVar2[4] + 5U);
          uVar10 = (uint)(piVar2[7] + 4 + piVar2[4]) % (piVar2[4] + 5U);
          *(undefined4 *)(piVar2[10] + 0x50 + uVar10 * 0x58) = 0xbf800000;
          *(undefined4 *)(piVar2[10] + 0x54 + uVar10 * 0x58) = 0;
          *(undefined1 *)(piVar2[10] + uVar10 * 0x58) = 0;
        }
      }
      iVar3 = piVar2[9];
      iVar4 = piVar2[6];
      FUN_00689960(puVar5,0xffffffff);
      local_20 = 0;
      for (local_18 = 0; local_18 < piVar2[4] + 1U; local_18 = local_18 + 1) {
        uVar10 = (piVar2[7] + local_18) % (piVar2[4] + 5U);
        if ((piVar2[0x17] & 1U) == 0) {
LAB_008218e2:
          if (*(char *)(piVar2[10] + uVar10 * 0x58) != '\0') {
            if (piVar2[0xc] == -1) {
              FUN_006899e0();
            }
            else {
              FUN_00689970(piVar2[0xc],piVar2 + 0xd);
            }
            uVar8 = (uint)(((DAT_02cecef0 - DAT_02cecee8) + 1) * *piVar2) / 0x280;
            iVar9 = ((uint)(((DAT_02cecef4 - DAT_02ceceec) + 1) * piVar2[1]) / 0x1e0 + local_20) -
                    (((4U - iVar3) % 4) * iVar4 >> 2);
            std::_Init_atomic_counter(puVar5,0);
            FUN_00689d10(puVar5,&DAT_02cecee0,uVar8 + 1,iVar9 + 1,piVar2[10] + uVar10 * 0x58);
            std::_Init_atomic_counter(puVar5,*(ulong *)(piVar2[10] + 0x54 + uVar10 * 0x58));
            FUN_00689d10(puVar5,&DAT_02cecee0,uVar8,iVar9,piVar2[10] + uVar10 * 0x58);
            if (piVar2[0xc] != -1) {
              FUN_006899e0();
            }
          }
        }
        else {
          iVar9 = piVar2[10];
          fVar11 = (float10)FUN_00822da0();
          pfVar1 = (float *)(iVar9 + 0x50 + uVar10 * 0x58);
          if ((float)fVar11 < *pfVar1 || (float)fVar11 == *pfVar1) {
            if ((float)piVar2[0x16] == -1.0) {
              piVar2[0x16] = *(int *)(piVar2[10] + 0x50 + uVar10 * 0x58);
            }
          }
          else {
            *(undefined4 *)(piVar2[10] + 0x50 + uVar10 * 0x58) = 0xbf800000;
          }
          pfVar1 = (float *)(piVar2[10] + 0x50 + uVar10 * 0x58);
          if (0.0 < *pfVar1 || *pfVar1 == 0.0) goto LAB_008218e2;
        }
        local_20 = local_20 + piVar2[6];
      }
      if (piVar2[9] == 0) {
        piVar2[0x17] = piVar2[0x17] & 0x7fffffff;
      }
    }
    local_14 = (undefined4 *)*local_14;
  } while( true );
}

