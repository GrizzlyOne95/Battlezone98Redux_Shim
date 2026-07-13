
void FUN_0041f590(int param_1)

{
  bool bVar1;
  uint uVar2;
  
  bVar1 = param_1 == 2;
  uVar2 = (uint)bVar1;
  if ((bool)DAT_00915510 != bVar1) {
    if (DAT_00915510 != '\0') {
      ATL::CDynamicAccessor::ReleaseAccessors((CDynamicAccessor *)&DAT_00946910,(IUnknown *)0x0);
      ATL::CDynamicAccessor::ReleaseAccessors((CDynamicAccessor *)&DAT_00946910,(IUnknown *)0x2);
      ATL::CDynamicAccessor::ReleaseAccessors((CDynamicAccessor *)&DAT_00946910,(IUnknown *)0x1);
      ATL::CDynamicAccessor::ReleaseAccessors((CDynamicAccessor *)&DAT_00946910,(IUnknown *)0x7);
      ATL::CDynamicAccessor::ReleaseAccessors((CDynamicAccessor *)&DAT_00946910,(IUnknown *)0x3);
    }
    if (bVar1) {
      CSliderCtrl::SetRange((CSliderCtrl *)&DAT_00946910,0,10,uVar2);
      CSliderCtrl::SetRange((CSliderCtrl *)&DAT_00946910,2,10,uVar2);
      CSliderCtrl::SetRange((CSliderCtrl *)&DAT_00946910,1,10,uVar2);
      CSliderCtrl::SetRange((CSliderCtrl *)&DAT_00946910,7,10,uVar2);
      CSliderCtrl::SetRange((CSliderCtrl *)&DAT_00946910,3,10,uVar2);
    }
  }
  return;
}

