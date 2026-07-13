
void FUN_0044edb0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_0044f140(local_c);
  puVar4 = local_c;
  FUN_0044efd0(param_2);
  cVar2 = FUN_004221b0(puVar4);
  if (cVar2 == '\0') {
    puVar4 = local_c;
    FUN_0044efb0(param_2);
    cVar2 = FUN_004221b0(puVar4);
    if (cVar2 != '\0') {
      puVar3 = (undefined4 *)FUN_0042da80();
      uVar1 = *puVar3;
      puVar3 = (undefined4 *)FUN_0044efb0(param_2);
      *puVar3 = uVar1;
    }
  }
  else {
    puVar4 = local_c;
    FUN_0044efb0(param_2);
    cVar2 = FUN_004221b0(puVar4);
    if (cVar2 == '\0') {
      puVar3 = (undefined4 *)FUN_0044f170();
      uVar1 = *puVar3;
      puVar3 = (undefined4 *)FUN_0044efd0(param_2);
      *puVar3 = uVar1;
    }
    else {
      puVar3 = (undefined4 *)FUN_0044ef90(local_10);
      uVar1 = *puVar3;
      puVar3 = (undefined4 *)FUN_0044efb0(param_2);
      *puVar3 = uVar1;
      puVar3 = (undefined4 *)FUN_0044ef90(local_14);
      uVar1 = *puVar3;
      puVar3 = (undefined4 *)FUN_0044efd0(param_2);
      *puVar3 = uVar1;
    }
  }
  return;
}

