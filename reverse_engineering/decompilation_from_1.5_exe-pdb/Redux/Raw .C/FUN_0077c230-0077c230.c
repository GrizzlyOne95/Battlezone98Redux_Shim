
void __fastcall FUN_0077c230(int param_1)

{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x80);
  FUN_0077c3c0(0,0,2,6,2,6);
  for (local_c = 1; local_c < 0x10; local_c = local_c + 1) {
    FUN_0077c3c0(local_c,0,0,6,2,6);
  }
  FUN_0077c3c0(0x10,0,0,3,2,6);
  for (local_10 = 1; local_10 < 0x10; local_10 = local_10 + 1) {
    FUN_0077c3c0(0,local_10,2,6,0,6);
  }
  for (local_18 = 1; local_18 < 0x10; local_18 = local_18 + 1) {
    for (local_14 = 1; local_14 < 0x10; local_14 = local_14 + 1) {
      FUN_0077c3c0(local_18,local_14,0,6,0,6);
    }
  }
  FUN_0077c3c0(0,0x10,2,6,0,3);
  for (local_1c = 1; local_1c < 0x10; local_1c = local_1c + 1) {
    FUN_0077c3c0(0x10,local_1c,0,3,0,6);
  }
  for (local_20 = 1; local_20 < 0x10; local_20 = local_20 + 1) {
    FUN_0077c3c0(local_20,0x10,0,6,0,3);
  }
  FUN_0077c3c0(0x10,0x10,0,3,0,3);
  *(undefined4 *)(param_1 + 0x6c) = 0;
  return;
}

