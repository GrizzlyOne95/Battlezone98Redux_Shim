
undefined4 __thiscall
FUN_00589fe0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00589620(param_2,param_3);
  if (iVar1 == 0) {
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = param_5;
    }
    uVar2 = 0;
  }
  else {
    if (param_4 != (undefined4 *)0x0) {
      uVar2 = FUN_0058a850(*param_1,param_2,param_3,"ParticleRenderClass",iVar1);
      *param_4 = uVar2;
    }
    uVar2 = 1;
  }
  return uVar2;
}

