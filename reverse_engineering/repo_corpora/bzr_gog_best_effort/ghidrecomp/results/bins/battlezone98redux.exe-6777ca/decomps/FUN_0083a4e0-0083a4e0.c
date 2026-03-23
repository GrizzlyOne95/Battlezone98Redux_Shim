
void FUN_0083a4e0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_10 [12];
  
  uVar1 = *(undefined4 *)(param_1 + 0x30);
  FUN_0083a00d(uVar1,local_10,1);
  FUN_00838ffd(param_1);
  uVar2 = FUN_0083b57b(param_1);
  if (*(int *)(param_1 + 0x10) != 0x2c) {
    if (*(int *)(param_1 + 0x10) == 0x3d) {
      FUN_0083a3ff(param_1,uVar2,param_2);
      goto LAB_0083a543;
    }
    if (*(int *)(param_1 + 0x10) != 0x10b) {
      FUN_008390b7(param_1,"\'=\' or \'in\' expected");
      goto LAB_0083a543;
    }
  }
  FUN_0083a2fd(param_1,uVar2);
LAB_0083a543:
  FUN_00839b38(param_1,0x106,0x108,param_2);
  FUN_0083a945(uVar1);
  return;
}

