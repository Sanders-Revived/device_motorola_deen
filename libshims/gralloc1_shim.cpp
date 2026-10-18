/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <hardware/gralloc1.h>
#include <system/graphics.h>

struct private_handle_t;

namespace gralloc {

struct BufferInfo {
    BufferInfo(int w, int h, int f, uint64_t usage = 0)
        : width(w), height(h), format(f), layer_count(1), usage(usage) {}
    int width;
    int height;
    int format;
    int layer_count;
    uint64_t usage;
};

void GetAlignedWidthAndHeight(const BufferInfo &d, unsigned int *aligned_w,
                              unsigned int *aligned_h);
unsigned int GetSize(const BufferInfo &d, unsigned int alignedw, unsigned int alignedh);
int GetBufferSizeAndDimensions(const BufferInfo &d, unsigned int *size, unsigned int *alignedw,
                               unsigned int *alignedh);
bool CpuCanWrite(uint64_t usage);
bool CpuCanAccess(uint64_t usage);
bool IsUBwcEnabled(int format, uint64_t usage);
int GetYUVPlaneInfo(const private_handle_t *hnd, struct android_ycbcr *ycbcr);
int GetRgbDataAddress(private_handle_t *hnd, void **rgb_data);
bool IsUncompressedRGBFormat(int format);

}  // namespace gralloc

namespace gralloc1 {

struct BufferInfo {
    BufferInfo(int w, int h, int f,
               gralloc1_producer_usage_t prod = GRALLOC1_PRODUCER_USAGE_NONE,
               gralloc1_consumer_usage_t cons = GRALLOC1_CONSUMER_USAGE_NONE)
        : width(w), height(h), format(f), prod_usage(prod), cons_usage(cons) {}
    int width;
    int height;
    int format;
    gralloc1_producer_usage_t prod_usage;
    gralloc1_consumer_usage_t cons_usage;
};

void GetAlignedWidthAndHeight(const BufferInfo &d, unsigned int *aligned_w,
                              unsigned int *aligned_h) {
    gralloc::BufferInfo info(d.width, d.height, d.format,
                             static_cast<uint64_t>(d.prod_usage) | static_cast<uint64_t>(d.cons_usage));
    gralloc::GetAlignedWidthAndHeight(info, aligned_w, aligned_h);
}

unsigned int GetSize(const BufferInfo &d, unsigned int alignedw, unsigned int alignedh) {
    gralloc::BufferInfo info(d.width, d.height, d.format,
                             static_cast<uint64_t>(d.prod_usage) | static_cast<uint64_t>(d.cons_usage));
    return gralloc::GetSize(info, alignedw, alignedh);
}

int GetBufferSizeAndDimensions(const BufferInfo &d, unsigned int *size, unsigned int *alignedw,
                               unsigned int *alignedh) {
    gralloc::BufferInfo info(d.width, d.height, d.format,
                             static_cast<uint64_t>(d.prod_usage) | static_cast<uint64_t>(d.cons_usage));
    return gralloc::GetBufferSizeAndDimensions(info, size, alignedw, alignedh);
}

bool CpuCanWrite(gralloc1_producer_usage_t usage) {
    return gralloc::CpuCanWrite(static_cast<uint64_t>(usage));
}

bool CpuCanAccess(gralloc1_producer_usage_t prod_usage, gralloc1_consumer_usage_t cons_usage) {
    return gralloc::CpuCanAccess(static_cast<uint64_t>(prod_usage) | static_cast<uint64_t>(cons_usage));
}

bool IsUBwcEnabled(int format, gralloc1_producer_usage_t prod_usage, gralloc1_consumer_usage_t cons_usage) {
    return gralloc::IsUBwcEnabled(format, static_cast<uint64_t>(prod_usage) | static_cast<uint64_t>(cons_usage));
}

int GetYUVPlaneInfo(const private_handle_t *hnd, struct android_ycbcr *ycbcr) {
    return gralloc::GetYUVPlaneInfo(hnd, ycbcr);
}

int GetRgbDataAddress(private_handle_t *hnd, void **rgb_data) {
    return gralloc::GetRgbDataAddress(hnd, rgb_data);
}

bool IsUncompressedRGBFormat(int format) {
    return gralloc::IsUncompressedRGBFormat(format);
}

}  // namespace gralloc1
