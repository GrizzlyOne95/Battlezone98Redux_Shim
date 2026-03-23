
void FUN_008393b8(uint *param_1,uint param_2,undefined4 *param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  
  FUN_00839600(param_1,*param_1);
  iVar2 = *(int *)param_1[0xe];
  *(int *)param_1[0xe] = iVar2 + -1;
  if (iVar2 == 0) {
    uVar5 = FUN_0082ec27(param_1[0xe]);
  }
  else {
    pbVar1 = *(byte **)(param_1[0xe] + 4);
    uVar5 = (uint)*pbVar1;
    *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
  }
  *param_1 = uVar5;
  do {
    if (uVar5 == param_2) {
      FUN_00839600(param_1,*param_1);
      iVar2 = *(int *)param_1[0xe];
      *(int *)param_1[0xe] = iVar2 + -1;
      if (iVar2 == 0) {
        uVar5 = FUN_0082ec27(param_1[0xe]);
      }
      else {
        pbVar1 = *(byte **)(param_1[0xe] + 4);
        uVar5 = (uint)*pbVar1;
        *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
      }
      *param_1 = uVar5;
      uVar4 = FUN_00838fac(param_1,*(int *)param_1[0xf] + 1,((int *)param_1[0xf])[1] + -2);
      *param_3 = uVar4;
      return;
    }
    if (*param_1 == 0xffffffff) {
      uVar4 = 0x11f;
LAB_00839592:
      FUN_00838ef5(param_1,"unfinished string",uVar4);
    }
    else {
      if ((*param_1 == 10) || (*param_1 == 0xd)) {
        uVar4 = 0x11e;
        goto LAB_00839592;
      }
      if (*param_1 == 0x5c) {
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar5 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar5 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        *param_1 = uVar5;
        if (0x66 < (int)uVar5) {
          if (uVar5 == 0x6e) {
            uVar5 = 10;
          }
          else if (uVar5 == 0x72) {
            uVar5 = 0xd;
          }
          else if (uVar5 == 0x74) {
            uVar5 = 9;
          }
          else {
            if (uVar5 != 0x76) {
LAB_008394f1:
              iVar2 = isdigit(uVar5);
              if (iVar2 != 0) {
                iVar6 = 0;
                iVar2 = 0;
                do {
                  iVar2 = (*param_1 - 0x30) + iVar2 * 10;
                  iVar3 = *(int *)param_1[0xe];
                  *(int *)param_1[0xe] = iVar3 + -1;
                  if (iVar3 == 0) {
                    uVar5 = FUN_0082ec27(param_1[0xe]);
                  }
                  else {
                    pbVar1 = *(byte **)(param_1[0xe] + 4);
                    uVar5 = (uint)*pbVar1;
                    *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
                  }
                  iVar6 = iVar6 + 1;
                  *param_1 = uVar5;
                } while ((iVar6 < 3) && (iVar3 = isdigit(uVar5), iVar3 != 0));
                if (0xff < iVar2) {
                  FUN_00838ef5(param_1,"escape sequence too large",0x11e);
                }
                FUN_00839600(param_1,iVar2);
                goto LAB_008395a0;
              }
              goto LAB_0083941e;
            }
            uVar5 = 0xb;
          }
          goto LAB_00839420;
        }
        if (uVar5 == 0x66) {
          uVar5 = 0xc;
          goto LAB_00839420;
        }
        if (uVar5 != 0xffffffff) {
          if ((uVar5 != 10) && (uVar5 != 0xd)) {
            if (uVar5 == 0x61) {
              uVar5 = 7;
            }
            else {
              if (uVar5 != 0x62) goto LAB_008394f1;
              uVar5 = 8;
            }
            goto LAB_00839420;
          }
          FUN_00839600(param_1,10);
          FUN_0083893c(param_1);
        }
      }
      else {
LAB_0083941e:
        uVar5 = *param_1;
LAB_00839420:
        FUN_00839600(param_1,uVar5);
        iVar2 = *(int *)param_1[0xe];
        *(int *)param_1[0xe] = iVar2 + -1;
        if (iVar2 == 0) {
          uVar5 = FUN_0082ec27(param_1[0xe]);
        }
        else {
          pbVar1 = *(byte **)(param_1[0xe] + 4);
          uVar5 = (uint)*pbVar1;
          *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
        }
        *param_1 = uVar5;
      }
    }
LAB_008395a0:
    uVar5 = *param_1;
  } while( true );
}

