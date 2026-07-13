
undefined4 FUN_00579310(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  uVar2 = FUN_00420260(local_c);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 != '\0') {
      FUN_0057a540();
      FUN_00420260(param_1);
      return param_1;
    }
  }
  while (cVar1 = FUN_00420f10(&stack0x0000000c), cVar1 != '\0') {
    puVar3 = (undefined4 *)FUN_004244c0(local_14,0);
    FUN_00579dc0(local_18,*puVar3);
  }
  _Vector_iterator<>(param_2,local_8);
  return param_1;
}

