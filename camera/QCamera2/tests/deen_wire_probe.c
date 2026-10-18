/* Freestanding ARM probe of the production serialization macros. */
#define LOGE(...) ((void)0);
#include <stddef.h>
#include "cam_intf.h"

void *memset(void *destination, int value, size_t length)
{
    unsigned char *out = destination;
    for (size_t i = 0; i < length; ++i) out[i] = value;
    return destination;
}
void *memcpy(void *destination, const void *source, size_t length)
{
    unsigned char *out = destination;
    const unsigned char *in = source;
    for (size_t i = 0; i < length; ++i) out[i] = in[i];
    return destination;
}
void __aeabi_memcpy4(void *out, const void *in, size_t size) { memcpy(out, in, size); }
void __aeabi_memcpy8(void *out, const void *in, size_t size) { memcpy(out, in, size); }
void __aeabi_memclr4(void *out, size_t size) { memset(out, 0, size); }
void __aeabi_memclr8(void *out, size_t size) { memset(out, 0, size); }

void deen_clear(metadata_buffer_t *metadata) { clear_metadata_buffer(metadata); }

int deen_fill(metadata_buffer_t *metadata)
{
    cam_stream_ID_t streams = {0};
    streams.num_streams = 2;
    streams.stream_request[0].streamID = 0x12345678;
    streams.stream_request[0].buf_index = 7;
    streams.stream_request[1].streamID = 0x23456789;
    streams.stream_request[1].buf_index = -1;
    cam_area_t roi = {0};
    roi.rect.left = 11;
    roi.rect.top = 22;
    roi.rect.width = 333;
    roi.rect.height = 444;
    roi.weight = 500;
    cam_stream_size_info_t config = {0};
    config.num_streams = 2;
    config.stream_sizes[0].width = 1920;
    config.stream_sizes[0].height = 1080;
    config.stream_sizes[1].width = 4160;
    config.stream_sizes[1].height = 3120;
    config.type[0] = CAM_STREAM_TYPE_PREVIEW;
    config.type[1] = CAM_STREAM_TYPE_SNAPSHOT;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_PARM_HAL_VERSION, 3)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_FRAME_NUMBER, 42)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_STREAM_ID, streams)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_STREAM_INFO, config)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_AEC_ROI, roi)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_AF_ROI, roi)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_SENSOR_EXPOSURE_TIME, 123456789LL)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_SENSOR_SENSITIVITY, 200)) return -1;
    if (ADD_SET_PARAM_ENTRY_TO_BATCH(metadata, CAM_INTF_META_JPEG_QUALITY, 95)) return -1;
    return 0;
}
