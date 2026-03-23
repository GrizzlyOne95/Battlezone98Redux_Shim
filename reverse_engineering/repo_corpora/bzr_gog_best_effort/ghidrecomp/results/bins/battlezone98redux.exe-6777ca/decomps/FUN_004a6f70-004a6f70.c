
void __fastcall FUN_004a6f70(int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  bool bVar3;
  undefined4 uVar4;
  IExecutionContext *local_8;
  
  for (local_8 = (IExecutionContext *)0x1; (int)local_8 < 0xb; local_8 = local_8 + 1) {
    puVar1 = (undefined4 *)(param_1 + 0x102c + (int)(local_8 + -1) * 0x18);
    uVar4 = FUN_0046faf0(local_8);
    *puVar1 = uVar4;
    cVar2 = FUN_0049f230(local_8);
    if (cVar2 == '\0') {
      bVar3 = Concurrency::details::UMSFreeVirtualProcessorRoot::IsSchedulingContext
                        ((UMSFreeVirtualProcessorRoot *)(param_1 + 0x113c),local_8);
      if (bVar3) {
        puVar1[1] = DAT_0091755c;
      }
      else {
        puVar1[1] = DAT_00917588;
      }
    }
    else {
      bVar3 = Concurrency::details::UMSFreeVirtualProcessorRoot::IsSchedulingContext
                        ((UMSFreeVirtualProcessorRoot *)(param_1 + 0x113c),local_8);
      if (bVar3) {
        puVar1[1] = DAT_00917560;
      }
      else {
        puVar1[1] = DAT_009175b0;
      }
    }
  }
  return;
}

