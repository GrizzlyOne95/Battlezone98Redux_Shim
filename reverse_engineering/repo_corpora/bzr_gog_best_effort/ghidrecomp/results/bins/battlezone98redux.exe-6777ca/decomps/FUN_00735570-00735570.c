
void __thiscall FUN_00735570(allocator<char> *param_1,allocator<char> *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  allocator<char> *local_10;
  undefined1 local_a;
  undefined1 local_9;
  char local_8;
  char local_7;
  char local_6;
  char local_5;
  
  local_10 = param_1;
  local_18 = std::allocator<char>::allocator<char>(param_1);
  local_14 = std::allocator<char>::allocator<char>(param_2);
  local_9 = 1;
  uVar3 = 1;
  uVar2 = local_18;
  puVar1 = (undefined4 *)std::allocator<char>::allocator<char>(param_2);
  local_6 = FUN_007357a0(local_14,*puVar1,uVar2,uVar3);
  uVar3 = 1;
  uVar2 = local_14;
  puVar1 = (undefined4 *)std::allocator<char>::allocator<char>(local_10);
  local_7 = FUN_007357a0(local_18,*puVar1,uVar2,uVar3);
  if ((local_6 == '\0') || (local_7 == '\0')) {
    local_5 = '\0';
  }
  else {
    local_5 = '\x01';
  }
  local_8 = local_5;
  if (local_5 == '\0') {
    if (local_6 == '\0') {
      uVar2 = FUN_006cc720(local_24);
      local_1c = FUN_00736870(uVar2);
      uVar2 = FUN_006cc6f0(local_28);
      local_20 = FUN_00736870(uVar2);
      uVar3 = 0;
      puVar1 = (undefined4 *)FUN_00732a50(local_2c,&local_1c,0);
      uVar2 = *puVar1;
      puVar1 = (undefined4 *)FUN_00732a50(local_30,&local_20,uVar2);
      FUN_00736890(*puVar1,uVar2,uVar3);
    }
    else {
      FUN_007306b0();
      uVar2 = *(undefined4 *)(local_10 + 8);
      uVar3 = *(undefined4 *)local_10;
      std::allocator<char>::allocator<char>(local_10);
      FUN_00417180(uVar3,uVar2);
      FUN_00735810(param_2);
    }
  }
  else {
    FUN_007306b0();
    FUN_007357c0(param_2);
  }
  FUN_00735700(local_18,local_14,local_a);
  return;
}

