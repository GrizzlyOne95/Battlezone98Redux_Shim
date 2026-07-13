
void __fastcall FUN_00478930(int param_1)

{
  undefined4 *puVar1;
  undefined1 local_28 [12];
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = *(int *)(param_1 + 8) + -2;
  local_18 = param_1;
  switch(*(int *)(param_1 + 8)) {
  case 2:
  case 0xb:
  case 0xc:
    FUN_00601200();
    break;
  case 3:
    FUN_00602920();
    break;
  case 9:
    *(undefined4 *)(param_1 + 0x13c) = 0;
  case 5:
  case 7:
  case 8:
  case 10:
    if ((((*(int *)(param_1 + 0xc) != 5) && (*(int *)(param_1 + 0xc) != 7)) &&
        (*(int *)(param_1 + 0xc) != 8)) &&
       ((*(int *)(param_1 + 0xc) != 9 && (*(int *)(param_1 + 0xc) != 10)))) {
      FUN_00605780();
    }
  }
  puVar1 = (undefined4 *)FUN_00440000(local_28,0,0,0);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_18 + 0x4c) = local_14;
  *(undefined4 *)(local_18 + 0x50) = local_10;
  *(undefined4 *)(local_18 + 0x54) = local_c;
  FUN_0083e885();
  return;
}

