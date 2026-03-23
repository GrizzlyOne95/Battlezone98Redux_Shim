
undefined4 FUN_0074b690(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  undefined4 local_8;
  
  puVar2 = (undefined4 *)FUN_00578c20(local_10,param_1);
  local_8 = *puVar2;
  uVar3 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    iVar4 = FUN_006cc5c0(param_1);
    uVar3 = *(undefined4 *)(iVar4 + 0x34);
  }
  return uVar3;
}

