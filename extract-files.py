#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: 2021-2026 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

import os

import extract_utils.tools

extract_utils.tools.DEFAULT_PATCHELF_VERSION = '0_9'

from extract_utils.elf import file_needs_lib
from extract_utils.fixups_blob import blob_fixup, blob_fixups_user_type
from extract_utils.fixups_lib import lib_fixups, lib_fixups_user_type
from extract_utils.main import ExtractUtils, ExtractUtilsModule
from extract_utils.postprocess import PostprocessCtx
from extract_utils.tools import patchelf_version_path_map
from extract_utils.utils import run_cmd

namespace_imports = [
    'device/motorola/deen',
    'hardware/motorola',
    'hardware/qcom-caf/msm8996',
    'hardware/qcom-caf/wlan',
    'vendor/qcom/opensource/dataservices',
]

blob_fixups: blob_fixups_user_type = {
    'vendor/lib/hw/audio.primary.msm8953.so': blob_fixup()
        .replace_needed('libcutils.so', 'libprocessgroup.so'),
    (
        'product/lib/lib-imscamera.so',
        'product/lib/lib-imsvideocodec.so',
        'product/lib64/lib-imscamera.so',
    ): blob_fixup()
        .add_needed('libgui_shim.so'),
    'vendor/lib/libmot_gpu_mapper.so': blob_fixup()
        .add_needed('libgui_shim_vendor.so'),
    'vendor/lib/libmmcamera2_pproc_modules.so': blob_fixup()
        .binary_regex_replace(
            b'ro.product.manufacturer',
            b'ro.product.nopefacturer',
        ),
    'vendor/lib/libmmcamera_vstab_module.so': blob_fixup()
        .binary_regex_replace(b'libgui', b'libwui'),
    (
        'product/etc/permissions/vendor.qti.hardware.data.connection-V1.0-java.xml',
        'product/etc/permissions/vendor.qti.hardware.data.connection-V1.1-java.xml',
    ): blob_fixup()
        .regex_replace('xml version="2.0"', 'xml version="1.0"'),
    'vendor/lib64/libril-qc-hal-qmi.so': blob_fixup()
        .add_needed('libcutils_shim.so'),
    'vendor/bin/charge_only_mode': blob_fixup()
        .add_needed('libmemset_shim.so'),
    (
        'vendor/lib/mediadrm/libwvhidl.so',
        'vendor/mediadrm/lib64/libwvhidl.so',
    ): blob_fixup()
        .replace_needed(
            'libprotobuf-cpp-lite.so',
            'libprotobuf-cpp-lite-v29.so',
        ),
}  # fmt: skip


def remove_legacy_hidl_dependencies(ctx: PostprocessCtx):
    proprietary_path = os.path.join(module.vendor_path, 'proprietary')
    patchelf = patchelf_version_path_map['0_9']

    for root, _, files in os.walk(proprietary_path):
        for filename in files:
            file_path = os.path.join(root, filename)
            if not os.path.isfile(file_path):
                continue

            for library in ('libhwbinder.so', 'libhidltransport.so'):
                if file_needs_lib(file_path, library):
                    run_cmd([patchelf, '--remove-needed', library, file_path])


module = ExtractUtilsModule(
    'deen',
    'motorola',
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
    namespace_imports=namespace_imports,
)
module.add_postprocess_fn(remove_legacy_hidl_dependencies)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
