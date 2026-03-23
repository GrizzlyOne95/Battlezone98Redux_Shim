
void __fastcall FUN_004f0b40(int param_1)

{
  float10 fVar1;
  
  FUN_004b6f30();
  FUN_004b6fa0("throt",*(undefined4 *)(param_1 + 0x78));
  FUN_004b6fa0("steer",*(undefined4 *)(param_1 + 0x70));
  FUN_004b6fa0("straf",*(undefined4 *)(param_1 + 0x7c));
  FUN_004b6fa0("brake",*(undefined4 *)(param_1 + 0x80));
  FUN_004b7030("posit",*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
               *(undefined4 *)(param_1 + 0x10));
  FUN_004b7030("veloc",*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),
               *(undefined4 *)(param_1 + 0x1c));
  fVar1 = (float10)FUN_0045c420(*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),
                                *(undefined4 *)(param_1 + 0x1c));
  FUN_004b6fa0("veloc",(float)fVar1);
  FUN_004b7030("accel",*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
               *(undefined4 *)(param_1 + 0x28));
  fVar1 = (float10)FUN_0045c420(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                                *(undefined4 *)(param_1 + 0x28));
  FUN_004b6fa0("accel",(float)fVar1);
  FUN_004b6fa0("heightRatio",*(undefined4 *)(param_1 + 0x88));
  FUN_004b6fa0("thrustRatio",*(undefined4 *)(param_1 + 0x84));
  FUN_004b6fa0("trackRatio",*(undefined4 *)(param_1 + 0x8c));
  return;
}

