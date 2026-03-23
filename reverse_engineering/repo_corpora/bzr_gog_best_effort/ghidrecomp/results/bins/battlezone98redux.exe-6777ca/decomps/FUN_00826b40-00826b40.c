
int __thiscall FUN_00826b40(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = FUN_0062ccc0(param_2,"world2",param_1);
  if ((iVar1 != 0) && (param_3 != (undefined4 *)0x0)) {
    *(undefined4 *)(iVar1 + 8) = *param_3;
    *(undefined4 *)(iVar1 + 0xc) = param_3[1];
  }
  return iVar1;
}

