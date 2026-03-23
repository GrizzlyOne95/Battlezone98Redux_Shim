
void FUN_00730ae0(void)

{
  uint *puVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_18 [4];
  undefined4 local_14;
  uint local_10;
  uint local_c;
  allocator<char> *local_8;
  
  puVar1 = (uint *)FUN_004b4350();
  local_10 = *puVar1;
  if (local_10 != 0) {
    uVar2 = FUN_00416410();
    local_c = uVar2;
    if (uVar2 == 0) {
      uVar6 = *(undefined4 *)local_8;
      uVar2 = local_10;
      std::allocator<char>::allocator<char>(local_8);
      FUN_00417180(uVar6,uVar2);
      *(undefined4 *)local_8 = 0;
      *(undefined4 *)(local_8 + 8) = 0;
    }
    else if (uVar2 < local_10) {
      uVar6 = *(undefined4 *)local_8;
      uVar3 = std::allocator<char>::allocator<char>(local_8);
      local_14 = FUN_006f31f0(uVar3,uVar2,uVar6);
      puVar4 = (undefined4 *)FUN_00730c80(local_18);
      uVar6 = *puVar4;
      uVar7 = 0;
      uVar3 = FUN_006d0da0(0,uVar6);
      uVar2 = local_c;
      uVar5 = FUN_00417780(local_14,local_c,uVar3);
      FUN_00732880(uVar5,uVar2,uVar3,uVar7,uVar6);
    }
  }
  return;
}

