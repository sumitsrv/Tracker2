include $(CLEAR_VARS)
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
LOCAL_LDLIBS    += -lm -llog -landroid

include $(BUILD_SHARED_LIBRARY)
include /mnt/Signi/Softwares/Linux/OpenCV-2.4.9-android-sdk/sdk/native/jni/include/OpenCV.mk
