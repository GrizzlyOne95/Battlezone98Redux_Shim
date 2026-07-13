
undefined4 FUN_005087f0(undefined4 param_1)

{
  float *pfVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  
  pfVar1 = (float *)FUN_004ff820(param_1,1);
  if (pfVar1 != (float *)0x0) {
    uVar2 = FUN_0082ba59();
    uVar3 = FUN_00446460(uVar2,0x811c9dc5);
    if (uVar3 < 0x44e771bd) {
      if (uVar3 == 0x44e771bc) {
        pfVar5 = (float *)FUN_004ff7a0(param_1,2);
        if (pfVar5 != (float *)0x0) {
          FUN_004fef00(pfVar1,(double)*pfVar5,(double)pfVar5[1],(double)pfVar5[2]);
        }
      }
      else if (uVar3 < 0x24f7b5b6) {
        if (uVar3 == 0x24f7b5b5) {
          fVar6 = (float10)FUN_0082ba89(param_1,3);
          pfVar1[5] = (float)fVar6;
        }
        else if (uVar3 == 0x21f7b0fc) {
          fVar6 = (float10)FUN_0082ba89(param_1,3);
          pfVar1[4] = (float)fVar6;
        }
        else if (uVar3 == 0x22f7b28f) {
          fVar6 = (float10)FUN_0082ba89(param_1,3);
          pfVar1[3] = (float)fVar6;
        }
      }
      else if ((uVar3 == 0x43430b20) && (iVar4 = FUN_004ff7a0(param_1,2), iVar4 != 0)) {
        FUN_004fef30(pfVar1,iVar4);
      }
    }
    else if (uVar3 < 0xc6a81d48) {
      if (uVar3 == 0xc6a81d47) {
        fVar6 = (float10)FUN_0082ba89(param_1,3);
        pfVar1[6] = (float)fVar6;
      }
      else if (uVar3 < 0xb86c3f83) {
        if (uVar3 == 0xb86c3f82) {
          fVar6 = (float10)FUN_0082ba89(param_1,3);
          *pfVar1 = (float)fVar6;
        }
        else if (uVar3 == 0x78e32de5) {
          iVar4 = FUN_004ff7a0(param_1,2);
          if (iVar4 != 0) {
            FUN_004fef60(pfVar1,iVar4);
          }
        }
        else if (uVar3 == 0xb66c3c5c) {
          fVar6 = (float10)FUN_0082ba89(param_1,3);
          pfVar1[2] = (float)fVar6;
        }
      }
      else if (uVar3 == 0xb96c4115) {
        fVar6 = (float10)FUN_0082ba89(param_1,3);
        pfVar1[1] = (float)fVar6;
      }
      else if (uVar3 == 0xc5a81bb4) {
        fVar6 = (float10)FUN_0082ba89(param_1,3);
        pfVar1[7] = (float)fVar6;
      }
    }
    else if (uVar3 < 0xebf98a61) {
      if (uVar3 == 0xebf98a60) {
        fVar6 = (float10)FUN_0082ba89(param_1,3);
        *(double *)(pfVar1 + 0xc) = (double)fVar6;
      }
      else if (uVar3 == 0xc8a8206d) {
        fVar6 = (float10)FUN_0082ba89(param_1,3);
        pfVar1[8] = (float)fVar6;
      }
      else if ((uVar3 == 0xe179dbd8) && (iVar4 = FUN_004ff7a0(param_1,2), iVar4 != 0)) {
        FUN_004fef90(pfVar1,iVar4);
      }
    }
    else if (uVar3 == 0xecf98bf3) {
      fVar6 = (float10)FUN_0082ba89(param_1,3);
      *(double *)(pfVar1 + 10) = (double)fVar6;
    }
    else if (uVar3 == 0xeef98f19) {
      fVar6 = (float10)FUN_0082ba89(param_1,3);
      *(double *)(pfVar1 + 0xe) = (double)fVar6;
    }
  }
  return 0;
}

