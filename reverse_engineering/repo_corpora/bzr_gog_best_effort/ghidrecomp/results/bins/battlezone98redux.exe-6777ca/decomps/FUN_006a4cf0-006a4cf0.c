
void FUN_006a4cf0(int param_1,int param_2,int param_3)

{
  int iVar1;
  float10 fVar2;
  float local_2c;
  float local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = 0;
  while ((local_18 < param_3 &&
         ((*(char *)(param_2 + 4 + local_18 * 8) == '\0' ||
          (iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_2 + local_18 * 8) + 0x18))(),
          *(int *)(iVar1 + 0x14) != 0x57494e47))))) {
    local_18 = local_18 + 1;
  }
  if (local_18 != param_3) {
    local_24 = *(int *)(param_1 + 0x40) << 4;
    fVar2 = (float10)FUN_006a0980(*(int *)(param_1 + 0x44) << 4);
    local_28 = (float)fVar2;
    fVar2 = (float10)FUN_006a09b0(local_24);
    local_20 = 0x42a00000;
    FUN_006a49c0(param_2,param_3,local_28 + 40.0,(float)fVar2 + 40.0,local_14,&local_2c);
    local_1c = FUN_00462630(*(undefined4 *)(param_1 + 0x84));
    if ((local_1c != 0) && (iVar1 = FUN_0045bdf0(), iVar1 != 0)) {
      for (; local_18 < param_3; local_18 = local_18 + 1) {
        if ((*(char *)(param_2 + 4 + local_18 * 8) != '\0') &&
           (iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_2 + local_18 * 8) + 0x18))(),
           *(int *)(iVar1 + 0x14) == 0x57494e47)) {
          if (local_2c == 0.0) {
            FUN_004dbd60(4,local_1c);
          }
          else {
            FUN_004dbd60(4,local_1c);
          }
          *(undefined1 *)(param_2 + 4 + local_18 * 8) = 0;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

