
undefined4 __thiscall
FUN_007c6fa0(int *param_1,undefined4 param_2,undefined2 param_3,char param_4,undefined1 param_5)

{
  undefined4 uVar1;
  undefined3 uVar2;
  
  if (param_4 == '\0') {
    uVar1 = (**(code **)(*param_1 + 0x18))(param_2,param_3);
    uVar2 = (undefined3)((uint)uVar1 >> 8);
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x14))(param_2,param_3,param_5);
    uVar2 = (undefined3)((uint)uVar1 >> 8);
  }
  return CONCAT31(uVar2,1);
}

