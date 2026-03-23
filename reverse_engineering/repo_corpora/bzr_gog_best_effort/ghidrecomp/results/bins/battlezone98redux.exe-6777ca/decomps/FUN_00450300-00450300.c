
void FUN_00450300(void)

{
  uint uVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 local_8;
  
  fVar2 = (float10)FUN_00450520();
  fVar3 = (float10)FUN_004504a0();
  if ((float)fVar2 < (float)fVar3) {
    local_8 = FUN_004187d0();
    if (local_8 < 0x200) {
      local_8 = local_8 << 3;
    }
    else {
      uVar1 = FID_conflict_max_size();
      if (local_8 < uVar1 >> 1) {
        local_8 = local_8 << 1;
      }
    }
    FUN_0044f090(local_8);
    FUN_00450540();
  }
  return;
}

