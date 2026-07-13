
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_005cb1c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 != 0) {
    _DAT_02a13d68 = 0;
    _DAT_02a13d6c = 0;
    _DAT_02a13d70 = 1;
    _DAT_02a13d74 = param_3;
    _DAT_02a13d78 = 0;
    _DAT_02a13d7c = 0x3f800000;
    _DAT_02a13d80 = 0;
    (**(code **)(*(int *)(iVar1 + 0x18) + 0x38))(&DAT_02a13d68,&DAT_02a13d78);
  }
  return;
}

