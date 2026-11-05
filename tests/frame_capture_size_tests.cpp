#include "frame_capture_size.h"
#include "test_check.h"
#include <initializer_list>
int main()
{
    using BZROpenShim::FrameCapture::ParseSize;
    using OpenShimTest::Check;
    const auto hd=ParseSize("2560x1440");
    Check(hd.width==2560 && hd.height==1440,"explicit client dimensions");
    for (const char* bad:{"","1920","1920X1080","-1x1080","1920x0","1920x1080junk","999999999999x1080","319x200","7681x4320","320x4321","x1080","1920x"})
        Check(ParseSize(bad).width==0,"malformed and unbounded sizes are rejected");
    Check(ParseSize("320x200").width==320 && ParseSize("7680x4320").height==4320,"supported bounds");
    return OpenShimTest::ExitCode();
}
