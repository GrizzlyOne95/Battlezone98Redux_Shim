
void __fastcall FUN_0065fc80(int param_1)

{
  undefined4 uVar1;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x554) = 0;
  while( true ) {
    if (*(int *)(&DAT_008ecfd0 + *(int *)(param_1 + 0x55c) * 0x1c) == 0) {
      local_38 = *(int *)(param_1 + 0x560);
    }
    else {
      local_38 = 1;
    }
    local_34 = 0;
    local_30 = *(int *)(param_1 + 0x554);
    for (; local_34 < *(int *)(&DAT_008ecfcc + *(int *)(param_1 + 0x55c) * 0x1c);
        local_34 = local_34 + 1) {
      sprintf(local_28,(&PTR_s_pilot__d_008ecfd4)[*(int *)(param_1 + 0x55c) * 7],local_34 + 1);
      for (local_3c = 0; local_3c < local_38; local_3c = local_3c + 1) {
        *(undefined4 *)(param_1 + 0x324 + local_30 * 4) = 0;
        uVar1 = FUN_005c8250((&PTR_s_cspilo_008ecfd8)[*(int *)(param_1 + 0x55c) * 7],2,local_28,0,0)
        ;
        *(undefined4 *)(param_1 + 0xac + local_30 * 4) = uVar1;
        FUN_005cb820(*(undefined4 *)(param_1 + 0xac + local_30 * 4),*(undefined4 *)(param_1 + 0xa4),
                     1);
        local_30 = local_30 + 1;
      }
    }
    *(int *)(param_1 + 0x554) =
         *(int *)(&DAT_008ecfcc + *(int *)(param_1 + 0x55c) * 0x1c) * local_38 +
         *(int *)(param_1 + 0x554);
    if (*(int *)(&DAT_008ecfc8 + *(int *)(param_1 + 0x55c) * 0x1c) == 0) break;
    *(int *)(param_1 + 0x55c) = *(int *)(param_1 + 0x55c) + 1;
  }
  FUN_0083e885();
  return;
}

