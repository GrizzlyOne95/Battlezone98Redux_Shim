
void __fastcall FUN_0044ddc0(undefined4 *param_1)

{
  *param_1 = ParticleRender::vftable;
  param_1[0x19] = 0;
  FUN_0044e470(param_1);
  if (param_1[0x1a] != 0) {
    *(undefined4 *)param_1[0x1a] = 0;
    param_1[0x1a] = 0;
  }
  return;
}

