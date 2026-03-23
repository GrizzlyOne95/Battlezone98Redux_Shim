
undefined4 FUN_0082ce29(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  puVar1 = (undefined *)FUN_0082c4a6(param_1,param_2);
  puVar2 = (undefined *)FUN_0082c4a6(param_1,param_3);
  if ((puVar1 == &DAT_0086ed18) || (puVar2 == &DAT_0086ed18)) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0082eafa(puVar1,puVar2);
  }
  return uVar3;
}

