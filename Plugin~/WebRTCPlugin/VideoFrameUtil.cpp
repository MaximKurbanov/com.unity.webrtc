#include "pch.h"

#include <api/make_ref_counted.h>
#include <system_wrappers/include/clock.h>

#include "GpuMemoryBuffer.h"
#include "GraphicsDevice/ITexture2D.h"
#include "GraphicsDevice/IGraphicsDevice.h"
#include "VideoFrameUtil.h"

namespace unity
{
namespace webrtc
{

    rtc::scoped_refptr<VideoFrame>
    CreateTestFrame(IGraphicsDevice* device, const ITexture2D* texture, UnityRenderingExtTextureFormat format)
    {
        NativeTexPtr ptr = NativeTexPtr(texture->GetNativeTexturePtrV());
        Size size = Size(static_cast<int>(texture->GetWidth()), static_cast<int>(texture->GetHeight()));

        rtc::scoped_refptr<GpuMemoryBufferInterface> buffer = rtc::make_ref_counted<GpuMemoryBufferFromUnity>(
            device, ptr, size, format, GpuMemoryBufferHandle::AccessMode::kRead);

        const int64_t timestamp_us = webrtc::Clock::GetRealTimeClock()->TimeInMicroseconds();

        return VideoFrame::WrapExternalGpuMemoryBuffer(
            size, std::move(buffer), nullptr, webrtc::TimeDelta::Micros(timestamp_us));
    }

} // end namespace webrtc
} // end namespace unity
