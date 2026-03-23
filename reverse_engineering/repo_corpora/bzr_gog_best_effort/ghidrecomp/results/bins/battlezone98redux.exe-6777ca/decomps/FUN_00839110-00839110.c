
void FUN_00839110(uint *param_1,undefined4 *param_2,int param_3)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  
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
  if ((uVar4 == 10) || (uVar4 == 0xd)) {
    FUN_0083893c(param_1);
  }
LAB_00839164:
  do {
    while (*param_1 == 0xffffffff) {
      pcVar5 = "unfinished long string";
      uVar3 = 0x11f;
      if (param_2 == (undefined4 *)0x0) {
        pcVar5 = "unfinished long comment";
      }
LAB_00839289:
      FUN_00838ef5(param_1,pcVar5,uVar3);
    }
    if ((*param_1 == 10) || (*param_1 == 0xd)) {
      FUN_00839600(param_1,10);
      FUN_0083893c(param_1);
      if (param_2 == (undefined4 *)0x0) {
        *(undefined4 *)(param_1[0xf] + 4) = 0;
      }
      goto LAB_00839164;
    }
    if (*param_1 == 0x5b) {
      iVar2 = FUN_0083966e(param_1);
      if (iVar2 == param_3) {
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
        if (param_3 == 0) {
          uVar3 = 0x5b;
          pcVar5 = "nesting of [[...]] is deprecated";
          goto LAB_00839289;
        }
      }
    }
    else if (*param_1 == 0x5d) {
      iVar2 = FUN_0083966e(param_1);
      if (iVar2 == param_3) {
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
        if (param_2 != (undefined4 *)0x0) {
          uVar3 = FUN_00838fac(param_1,*(int *)param_1[0xf] + 2 + param_3,
                               ((int *)param_1[0xf])[1] + param_3 * -2 + -4);
          *param_2 = uVar3;
        }
        return;
      }
    }
    else {
      if (param_2 != (undefined4 *)0x0) {
        FUN_00839600(param_1,*param_1);
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
    }
  } while( true );
}

