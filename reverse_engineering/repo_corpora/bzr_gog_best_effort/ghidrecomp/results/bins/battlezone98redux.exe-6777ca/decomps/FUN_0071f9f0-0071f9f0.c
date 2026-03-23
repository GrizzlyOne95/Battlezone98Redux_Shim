
XImage * __thiscall FUN_0071f9f0(XImage *param_1,uint param_2)

{
  CMFCRibbonInfo::XImage::~XImage(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

