
void FUN_00839037(uint param_1,uint *param_2,uint param_3,uint param_4)

{
  int iVar1;
  byte *pbVar2;
  undefined4 uVar3;
  uint uVar4;
  
  param_2[0xc] = 0;
  param_2[0xe] = param_3;
  *(undefined1 *)(param_2 + 0x11) = 0x2e;
  param_2[1] = 1;
  param_2[2] = 1;
  param_2[0x10] = param_4;
  param_2[0xd] = param_1;
  param_2[8] = 0x11f;
  uVar3 = FUN_00838869(param_1,*(undefined4 *)param_2[0xf],((undefined4 *)param_2[0xf])[2],0x20);
  *(undefined4 *)param_2[0xf] = uVar3;
  *(undefined4 *)(param_2[0xf] + 8) = 0x20;
  iVar1 = *(int *)param_2[0xe];
  *(int *)param_2[0xe] = iVar1 + -1;
  if (iVar1 == 0) {
    uVar4 = FUN_0082ec27(param_2[0xe]);
  }
  else {
    pbVar2 = *(byte **)(param_2[0xe] + 4);
    uVar4 = (uint)*pbVar2;
    *(byte **)(param_2[0xe] + 4) = pbVar2 + 1;
  }
  *param_2 = uVar4;
  return;
}

