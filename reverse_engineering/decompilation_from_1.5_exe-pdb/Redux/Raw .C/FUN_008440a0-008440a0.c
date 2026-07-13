
void __fastcall FUN_008440a0(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00844020();
    operator_delete(pvVar1);
  }
  return;
}

