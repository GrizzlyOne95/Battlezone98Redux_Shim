
void __fastcall FUN_00663450(Listener *param_1)

{
  uint uVar1;
  int iVar2;
  Listener *local_28;
  int *local_24;
  Listener *local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084dcfc;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = RTListener::vftable;
  *(undefined ***)(param_1 + 4) = RTListener::vftable;
  *(undefined ***)(param_1 + 8) = RTListener::vftable;
  local_8 = 3;
  if (*(int *)(param_1 + 0x14) != 0) {
    Ogre::CompositorInstance::removeListener(*(CompositorInstance **)(param_1 + 0x14),param_1);
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    if (param_1 == (Listener *)0x0) {
      local_1c = (Listener *)0x0;
    }
    else {
      local_1c = param_1 + 4;
    }
    (**(code **)(**(int **)(param_1 + 0x18) + 0x78))(local_1c,uVar1);
  }
  iVar2 = FUN_0044d2a0();
  if (iVar2 == 0) {
    local_24 = (int *)0x0;
  }
  else {
    local_24 = *(int **)(iVar2 + 8);
  }
  if (local_24 != (int *)0x0) {
    if (param_1 == (Listener *)0x0) {
      local_28 = (Listener *)0x0;
    }
    else {
      local_28 = param_1 + 8;
    }
    (**(code **)(*local_24 + 0x324))(local_28);
  }
  local_8._0_1_ = 2;
  FUN_00428210();
  local_8._0_1_ = 1;
  Ogre::RenderQueueListener::~RenderQueueListener((RenderQueueListener *)(param_1 + 8));
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::RenderTargetListener::~RenderTargetListener((RenderTargetListener *)(param_1 + 4));
  local_8 = 0xffffffff;
  Ogre::CompositorInstance::Listener::~Listener(param_1);
  ExceptionList = local_10;
  return;
}

