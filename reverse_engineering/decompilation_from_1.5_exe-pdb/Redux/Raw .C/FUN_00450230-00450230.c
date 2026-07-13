
void FUN_00450230(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_c [8];
  
  uVar2 = FUN_0044ef90(local_c);
  FUN_0044efb0(param_3);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    puVar4 = (undefined1 *)&param_2;
    FUN_0044efb0(param_3);
    cVar1 = FUN_004221b0(puVar4);
    if (cVar1 == '\0') {
      puVar3 = &param_1;
      FUN_0044efd0(param_3);
      FUN_0042da80(puVar3);
      cVar1 = FUN_00420f10(puVar3);
      if (cVar1 != '\0') {
        FUN_0044efd0(param_3);
        FUN_0044f170();
      }
    }
    else {
      puVar3 = (undefined4 *)FUN_0044efb0(param_3);
      *puVar3 = param_1;
    }
  }
  else {
    puVar3 = (undefined4 *)FUN_0044efb0(param_3);
    *puVar3 = param_1;
    puVar3 = (undefined4 *)FUN_0044efd0(param_3);
    *puVar3 = param_1;
  }
  return;
}

