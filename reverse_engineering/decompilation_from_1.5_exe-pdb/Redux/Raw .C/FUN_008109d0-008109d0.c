
uint FUN_008109d0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  undefined1 *puVar4;
  
  uVar3 = FID_conflict_operator__(param_2);
  if ((uVar3 & 0xff) == 0) {
    uVar1 = *param_1;
    puVar4 = (undefined1 *)FUN_00417780(param_3);
    cVar2 = FUN_008118b0(param_1,param_2,*puVar4);
    if (cVar2 == '\0') {
      *param_1 = uVar1;
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = uVar3 & 0xffffff00;
  }
  return uVar3;
}

