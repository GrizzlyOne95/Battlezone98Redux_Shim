
undefined4 FUN_0074b6f0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_10 [8];
  undefined1 local_8 [4];
  
  FUN_00578c20(local_8,param_1);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150();
    *(undefined4 *)(iVar3 + 0x44) = param_2;
  }
  get(param_2);
  FUN_006c54f0(param_2);
  return 1;
}

