
undefined4 __thiscall FUN_007d2270(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  iVar1 = size(param_1);
  if (param_2 < iVar1) {
    puVar2 = (undefined4 *)FUN_004200d0(param_2);
    uVar3 = *puVar2;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

