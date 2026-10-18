LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libgralloc1_shim
LOCAL_MODULE_TAGS := optional
LOCAL_VENDOR_MODULE := true
LOCAL_SRC_FILES := gralloc1_shim.cpp
LOCAL_SHARED_LIBRARIES := libgrallocutils
LOCAL_HEADER_LIBRARIES := libhardware_headers libsystem_headers
include $(BUILD_SHARED_LIBRARY)
