
void __fastcall FUN_005ee140(int param_1)

{
  int iVar1;
  undefined *local_70;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x18) + 0x30))();
  sprintf(local_58," TugProcess:",iVar1);
  FUN_004b70f0();
  FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",iVar1 + 8);
  FUN_004b70f0();
  sprintf(local_58," State (%s)");
  FUN_004b70f0();
  iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x20) + 0x18))();
  if ((*(int *)(iVar1 + 0x1c) == 1) ||
     (iVar1 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x20) + 0x18))(),
     *(int *)(iVar1 + 0x1c) == 6)) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x20) + 0x230);
    sprintf(local_58," Craft (0x%p)");
    FUN_004b70f0();
    sprintf(local_58," Cargo (0x%p)");
    FUN_004b70f0();
    if (*(int *)(*(int *)(param_1 + 0x20) + 0x300) != 0) {
      FUN_004623e0();
      sprintf(local_58," Cargo (%s)");
      FUN_004b70f0();
    }
    sprintf(local_58," Steer (%+.2f)",(double)*(float *)(iVar1 + 0xc4));
    FUN_004b70f0();
    sprintf(local_58," Braccel (%+.2f)",(double)*(float *)(iVar1 + 0xd0));
    FUN_004b70f0();
    sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)*(float *)(iVar1 + 200),
            (double)*(float *)(iVar1 + 0xcc));
    FUN_004b70f0();
    if (*(int *)(iVar1 + 0xd4) == 0) {
      local_70 = &DAT_008865a8;
    }
    else {
      local_70 = &DAT_00886520;
    }
    sprintf(local_58," Turbo (%s) Jump (%s)",local_70);
    FUN_004b70f0();
    iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x18) + 0x30))();
    sprintf(local_58," Transform Position:");
    FUN_004b70f0();
    sprintf(local_58," X (%.2f)",*(undefined8 *)(iVar1 + 0x48));
    FUN_004b70f0();
    sprintf(local_58," Y (%.2f)",*(undefined8 *)(iVar1 + 0x50));
    FUN_004b70f0();
    sprintf(local_58," Z (%.2f)",*(undefined8 *)(iVar1 + 0x58));
    FUN_004b70f0();
    iVar1 = FUN_0045c490();
    sprintf(local_58," Velocity:");
    FUN_004b70f0();
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)*(float *)(iVar1 + 0x18),
            (double)*(float *)(iVar1 + 0x1c),(double)*(float *)(iVar1 + 0x20));
    FUN_004b70f0();
    sprintf(local_58," Accel:");
    FUN_004b70f0();
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)*(float *)(iVar1 + 0x30),
            (double)*(float *)(iVar1 + 0x34),(double)*(float *)(iVar1 + 0x38));
    FUN_004b70f0();
    sprintf(local_58," Omega:");
    FUN_004b70f0();
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)*(float *)(iVar1 + 0x24),
            (double)*(float *)(iVar1 + 0x28),(double)*(float *)(iVar1 + 0x2c));
    FUN_004b70f0();
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    (**(code **)(**(int **)(param_1 + 0x34) + 0x20))();
  }
  FUN_0083e885();
  return;
}

