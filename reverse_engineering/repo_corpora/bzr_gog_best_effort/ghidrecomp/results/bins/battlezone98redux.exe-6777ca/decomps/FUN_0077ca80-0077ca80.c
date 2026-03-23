
int FUN_0077ca80(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_20 [8];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10 [2];
  allocator<char> local_5;
  
  FUN_0044ecb0(local_10,param_1);
  uVar2 = FUN_0044eaa0(local_14);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    uVar2 = std::allocator<char>::allocator<char>(&local_5);
    uVar3 = FUN_00427550(local_18,param_1,uVar2);
    puVar4 = (undefined4 *)FUN_0077cde0(local_20,&DAT_0260b617,uVar3,uVar2);
    local_10[0] = *puVar4;
  }
  iVar5 = FUN_0042da60();
  return iVar5 + 4;
}

