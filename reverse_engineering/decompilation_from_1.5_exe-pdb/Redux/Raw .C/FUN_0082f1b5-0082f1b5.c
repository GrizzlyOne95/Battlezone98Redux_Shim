
int FUN_0082f1b5(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  uVar2 = *(undefined2 *)(param_1 + 0x34);
  iVar3 = *(int *)(param_1 + 0x14);
  iVar4 = *(int *)(param_1 + 0x28);
  uVar1 = *(undefined1 *)(param_1 + 0x39);
  uVar5 = *(undefined4 *)(param_1 + 0x74);
  *(undefined4 *)(param_1 + 0x74) = param_5;
  iVar6 = FUN_0082f4cb(param_1,param_2,param_3);
  if (iVar6 != 0) {
    param_4 = *(int *)(param_1 + 0x20) + param_4;
    FUN_0082f92f(param_1,param_4);
    FUN_0082f5f3(param_1,iVar6,param_4);
    puVar7 = (undefined4 *)((iVar3 - iVar4) + *(int *)(param_1 + 0x28));
    *(undefined2 *)(param_1 + 0x34) = uVar2;
    *(undefined4 **)(param_1 + 0x14) = puVar7;
    *(undefined4 *)(param_1 + 0xc) = *puVar7;
    *(undefined4 *)(param_1 + 0x18) = puVar7[3];
    *(undefined1 *)(param_1 + 0x39) = uVar1;
    FUN_0082f7b4(param_1);
  }
  *(undefined4 *)(param_1 + 0x74) = uVar5;
  return iVar6;
}

