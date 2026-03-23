
void FUN_006dcef0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  allocator<char> *local_c;
  byte local_5;
  
  cVar1 = FUN_006e1cd0();
  if (cVar1 == '\0') {
    local_5 = 0;
    local_10 = FUN_006e1d10();
    uVar4 = (uint)local_5;
    uVar2 = FUN_00417780(param_1,uVar4);
    puVar5 = (undefined4 *)FUN_006e1d30(local_14,uVar2);
    FUN_006ef220(local_18,&local_10,1,*puVar5,uVar4);
  }
  else {
    uVar2 = FUN_00417780(param_1);
    uVar2 = FUN_006e1d50(uVar2);
    uVar3 = std::allocator<char>::allocator<char>(local_c);
    FUN_006ef1f0(uVar3,uVar2);
    *(int *)(local_c + 4) = *(int *)(local_c + 4) + 1;
  }
  return;
}

