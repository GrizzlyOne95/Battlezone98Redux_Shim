
undefined4 FUN_0058a4b0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_10 [4];
  undefined4 local_c;
  
  uVar2 = FUN_0058a560(local_10);
  FUN_0044efb0(param_2);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    FUN_0058a560(param_1);
    return param_1;
  }
  puVar3 = (undefined4 *)FUN_0044efd0(param_2);
  local_c = *puVar3;
                    /* WARNING: Subroutine does not return */
  FUN_0042de70();
}

