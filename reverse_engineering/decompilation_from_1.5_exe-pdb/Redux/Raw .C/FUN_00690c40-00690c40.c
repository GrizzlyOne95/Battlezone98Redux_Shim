
bool __thiscall
FUN_00690c40(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4,
            undefined4 *param_5)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0069d590((&DAT_02bfdff0)[param_2],param_3,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *param_4 = *puVar1;
    *param_5 = puVar1[1];
  }
  return puVar1 != (undefined4 *)0x0;
}

