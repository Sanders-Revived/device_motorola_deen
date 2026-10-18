# Deen camera HAL

ARM32 HAL3 for Motorola One (deen), adapted from
[Sanders-Revived](https://github.com/Sanders-Revived/device_motorola_sanders/tree/fe0ea3970f86a0b07dfe73cac17945b96a8927df/camera)
for the Android 11 device tree and its original camera blobs.

Built modules:

- `camera.msm8953`
- `libmmcamera_interface`
- `libmmjpeg_interface`
- `libqomx_core`

After configuring the Android build for `lineage_deen-userdebug`:

```sh
m -j4 camera.msm8953 libmmcamera_interface libmmjpeg_interface libqomx_core
m -j4 vendorimage
```

The daemon, sensor libraries and image-processing libraries remain proprietary.
The source uses the device's msm8953 display/media headers and libraries.

`QCamera2/stack/common/cam_deen_abi.h` checks the ARM32 layouts exchanged with the
original blobs at compile time. Reserved fields preserve those layouts.
`QCamera2/tests/deen_wire_probe.c` exercises metadata serialization independently
of the installed HAL and is not included in the production modules.
