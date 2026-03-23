
int FUN_004cf950(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10 [2];
  allocator<char> local_6;
  undefined1 local_5;
  
  FUN_0046b430(local_10,param_1);
  uVar2 = FID_conflict_begin(local_18);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    uVar3 = FUN_00422f10(uVar2);
    uVar2 = param_1;
    FUN_00422f60(&local_5);
    cVar1 = FUN_0046b460(uVar2,uVar3);
    if (cVar1 == '\0') goto LAB_004cf9ef;
  }
  local_14 = local_10[0];
  uVar2 = std::allocator<char>::allocator<char>(&local_6);
  uVar3 = FUN_00427550(local_1c,param_1,uVar2);
  puVar4 = (undefined4 *)FUN_004cfa20(local_20,local_14,&DAT_009b5a4d,uVar3,uVar2);
  local_10[0] = *puVar4;
LAB_004cf9ef:
  iVar5 = FUN_00422150();
  return iVar5 + 8;
}

