
uint FUN_008389c5(uint *param_1,int *param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
LAB_008389cf:
  *(undefined4 *)(param_1[0xf] + 4) = 0;
LAB_008389d5:
  do {
    if (0x2e < (int)*param_1) {
      uVar4 = *param_1;
      if (uVar4 == 0x3c) {
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar4 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar4 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        *param_1 = uVar4;
        if (uVar4 != 0x3d) {
          return 0x3c;
        }
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar4 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar4 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        uVar3 = 0x11a;
        goto LAB_00838eb2;
      }
      if (uVar4 != 0x3d) {
        if (uVar4 == 0x3e) {
          iVar2 = *(int *)param_1[0xe];
          *(int *)param_1[0xe] = iVar2 + -1;
          if (iVar2 == 0) {
            uVar4 = FUN_0082ec27(param_1[0xe]);
          }
          else {
            pbVar1 = *(byte **)(param_1[0xe] + 4);
            uVar4 = (uint)*pbVar1;
            *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
          }
          *param_1 = uVar4;
          if (uVar4 != 0x3d) {
            return 0x3e;
          }
          iVar2 = *(int *)param_1[0xe];
          *(int *)param_1[0xe] = iVar2 + -1;
          if (iVar2 == 0) {
            uVar4 = FUN_0082ec27(param_1[0xe]);
          }
          else {
            pbVar1 = *(byte **)(param_1[0xe] + 4);
            uVar4 = (uint)*pbVar1;
            *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
          }
          uVar3 = 0x119;
          goto LAB_00838eb2;
        }
        if (uVar4 != 0x5b) {
          if (uVar4 == 0x7e) {
            iVar2 = *(int *)param_1[0xe];
            *(int *)param_1[0xe] = iVar2 + -1;
            if (iVar2 == 0) {
              uVar4 = FUN_0082ec27(param_1[0xe]);
            }
            else {
              pbVar1 = *(byte **)(param_1[0xe] + 4);
              uVar4 = (uint)*pbVar1;
              *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
            }
            *param_1 = uVar4;
            if (uVar4 != 0x3d) {
              return 0x7e;
            }
            iVar2 = *(int *)param_1[0xe];
            *(int *)param_1[0xe] = iVar2 + -1;
            if (iVar2 == 0) {
              uVar4 = FUN_0082ec27(param_1[0xe]);
            }
            else {
              pbVar1 = *(byte **)(param_1[0xe] + 4);
              uVar4 = (uint)*pbVar1;
              *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
            }
            uVar3 = 0x11b;
            goto LAB_00838eb2;
          }
          goto LAB_00838b25;
        }
        iVar2 = FUN_0083966e(param_1);
        if (-1 < iVar2) {
          FUN_00839110(param_1,param_2,iVar2);
          return 0x11e;
        }
        if (iVar2 == -1) {
          return 0x5b;
        }
        FUN_00838ef5(param_1,"invalid long string delimiter",0x11e);
      }
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar4 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar4 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      *param_1 = uVar4;
      if (uVar4 != 0x3d) {
        return 0x3d;
      }
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar4 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar4 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      uVar3 = 0x118;
LAB_00838eb2:
      *param_1 = uVar4;
      return uVar3;
    }
    if (*param_1 == 0x2e) {
      FUN_00839600(param_1,*param_1);
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar4 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar4 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      *param_1 = uVar4;
      iVar2 = FUN_008388ea(param_1,&DAT_008752b0);
      if (iVar2 != 0) {
        iVar2 = FUN_008388ea(param_1,&DAT_008752b0);
        return (iVar2 != 0) + 0x116;
      }
      iVar2 = isdigit(*param_1);
      if (iVar2 == 0) {
        return 0x2e;
      }
      goto LAB_00838bfa;
    }
    if (*param_1 == 0xffffffff) {
      return 0x11f;
    }
    if ((*param_1 != 10) && (*param_1 != 0xd)) {
      if ((*param_1 == 0x22) || (*param_1 == 0x27)) {
        FUN_008393b8(param_1,*param_1,param_2);
        return 0x11e;
      }
      if (*param_1 != 0x2d) {
LAB_00838b25:
        iVar2 = isspace(*param_1);
        if (iVar2 == 0) {
          iVar2 = isdigit(*param_1);
          if (iVar2 != 0) {
LAB_00838bfa:
            FUN_008392cf(param_1,param_2);
            return 0x11c;
          }
          iVar2 = isalpha(*param_1);
          if ((iVar2 != 0) || (uVar3 = *param_1, uVar3 == 0x5f)) {
            do {
              FUN_00839600(param_1,*param_1);
              iVar2 = *(int *)param_1[0xe];
              *(int *)param_1[0xe] = iVar2 + -1;
              if (iVar2 == 0) {
                uVar4 = FUN_0082ec27(param_1[0xe]);
              }
              else {
                pbVar1 = *(byte **)(param_1[0xe] + 4);
                uVar4 = (uint)*pbVar1;
                *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
              }
              *param_1 = uVar4;
              iVar2 = isalnum(uVar4);
            } while ((iVar2 != 0) || (*param_1 == 0x5f));
            iVar2 = FUN_00838fac(param_1,*(undefined4 *)param_1[0xf],((undefined4 *)param_1[0xf])[1]
                                );
            if (*(byte *)(iVar2 + 6) == 0) {
              *param_2 = iVar2;
              uVar4 = 0x11d;
            }
            else {
              uVar4 = *(byte *)(iVar2 + 6) + 0x100;
            }
            return uVar4;
          }
          iVar2 = *(int *)param_1[0xe];
          *(int *)param_1[0xe] = iVar2 + -1;
          if (iVar2 == 0) {
            uVar4 = FUN_0082ec27(param_1[0xe]);
          }
          else {
            pbVar1 = *(byte **)(param_1[0xe] + 4);
            uVar4 = (uint)*pbVar1;
            *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
          }
          goto LAB_00838eb2;
        }
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar4 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar4 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        *param_1 = uVar4;
        goto LAB_008389d5;
      }
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar4 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar4 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      *param_1 = uVar4;
      if (uVar4 != 0x2d) {
        return 0x2d;
      }
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar4 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar4 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      *param_1 = uVar4;
      if (uVar4 == 0x5b) {
        iVar2 = FUN_0083966e(param_1);
        *(undefined4 *)(param_1[0xf] + 4) = 0;
        if (-1 < iVar2) break;
      }
      uVar4 = *param_1;
      while (((uVar4 != 10 && (*param_1 != 0xd)) && (*param_1 != 0xffffffff))) {
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar4 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar4 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        *param_1 = uVar4;
      }
      goto LAB_008389d5;
    }
    FUN_0083893c(param_1);
  } while( true );
  FUN_00839110(param_1,0,iVar2);
  goto LAB_008389cf;
}

