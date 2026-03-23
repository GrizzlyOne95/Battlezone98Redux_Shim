
int __thiscall FUN_006e3390(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  FUN_0045e0f0(uVar1);
  puVar2 = (undefined4 *)FUN_00417780(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x18) = *puVar2;
  return param_1;
}

