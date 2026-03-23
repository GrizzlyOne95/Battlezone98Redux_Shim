
void __thiscall FUN_006cffd0(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [4];
  undefined4 local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x78) == 0) {
    FUN_006d08b0(0x400,"asio::init_asio");
    *(undefined4 *)(local_8 + 0x48) = param_2;
    *(undefined1 *)(local_8 + 0x4c) = 1;
    uVar2 = select_on_container_copy_construction(local_10,*(undefined4 *)(local_8 + 0x48));
    local_c = FUN_006dd830(local_18,uVar2);
    FID_conflict_operator_(local_c);
    FUN_006ca8c0();
    *(undefined4 *)(local_8 + 0x78) = 1;
    puVar1 = (undefined4 *)FUN_006ab750();
    uVar2 = puVar1[1];
    *param_3 = *puVar1;
    param_3[1] = uVar2;
  }
  else {
    FUN_006d47b0(2,"asio::init_asio called from the wrong state");
    puVar1 = (undefined4 *)make_error_code(local_20,9);
    uVar2 = puVar1[1];
    *param_3 = *puVar1;
    param_3[1] = uVar2;
  }
  return;
}

