
void FUN_004436c0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_30 [12];
  int local_24;
  int local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0062dfe0(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    iVar1 = FUN_0062dfe0(*(undefined4 *)(param_2 + 4));
    if (iVar1 == 0) goto LAB_004438b7;
    local_18 = *(undefined4 *)(param_2 + 4);
    local_24 = *(int *)(*(int *)(param_1 + 4) + 0x84);
  }
  else {
    local_18 = *(undefined4 *)(param_1 + 4);
    local_24 = *(int *)(*(int *)(param_2 + 4) + 0x84);
  }
  puVar2 = (undefined4 *)
           FUN_004401a0(local_30,*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 100),
                        *(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_2 + 0x60),
                        *(undefined4 *)(param_2 + 100),*(undefined4 *)(param_2 + 0x68));
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  fVar3 = (float10)FUN_004428b0(&local_14,&local_14);
  local_1c = (float)fVar3;
  local_20 = local_24 + -1;
  switch(local_24) {
  case 1:
  case 6:
    if (local_1c <= 1600.0) {
      if (local_1c <= 500.0) {
        if (25.0 < local_1c) {
          FUN_004376c0("vvcbb3.wav",local_18,0);
        }
      }
      else {
        FUN_004376c0("vvcre2.wav",local_18,0);
      }
    }
    else {
      FUN_004376c0("vvch2.wav",local_18,0);
    }
    break;
  default:
    if (local_1c <= 500.0) {
      if (25.0 < local_1c) {
        FUN_004376c0("vnvcs1.wav",local_18,0);
      }
    }
    else {
      FUN_004376c0("vnvcs3.wav",local_18,0);
    }
    break;
  case 3:
  case 4:
    break;
  case 5:
  case 7:
    if (25.0 < local_1c) {
      FUN_004376c0("vnvco3.wav",local_18,0);
    }
    break;
  case 10:
    if (25.0 < local_1c) {
      FUN_004376c0("vvcbb3.wav",local_18,0);
    }
  }
LAB_004438b7:
  FUN_0083e885();
  return;
}

