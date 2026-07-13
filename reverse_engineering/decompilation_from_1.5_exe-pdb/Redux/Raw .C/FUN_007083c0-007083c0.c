
void __thiscall
FUN_007083c0(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_006d6720(param_4,param_1);
  uVar2 = (uint)CONCAT11(iVar1 == *param_2,iVar1 == *param_2) << 0x10;
  FUN_00708360(param_2,param_3);
  FUN_006d76c0(param_3,param_4);
  FUN_00708720(param_5,param_3,param_4,uVar2 >> 0x10 & 0xff);
  return;
}

