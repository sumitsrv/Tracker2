QT += core gui opengl quick svg xml qml declarative multimedia widgets

TARGET = TrackerDemo
TEMPLATE = app

SOURCES += main.cpp\
    imageviewer.cpp \
    trackermainwindow.cpp \
    imagefiledialog.cpp \
    featuresmatcher.cpp \
    trackerfeatures.cpp

HEADERS  += \
    imageviewer.h \
    trackermainwindow.h \
    imagefiledialog.h \
    featuresmatcher.h \
    trackerfeatures.h

FORMS    += qtglwebcamdemo.ui

#INCLUDEPATH += /usr/local/include/
#LIBS += /usr/local/lib/*.so.2.4.8

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
ANDROID_PACKAGE_INCLUDE_DIR = /mnt/Signi/Softwares/Linux/OpenCV-2.4.9-android-sdk/sdk/

contains(ANDROID_TARGET_ARCH,armeabi) {
    LIBS += $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi/libopencv_java.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi/libopencv_info.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi/libnonfree.so


    INCLUDEPATH += $$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/ \
$$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/opencv \
$$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/opencv2 \
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    LIBS += $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libopencv_info.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libopencv_java.so \
$$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libnonfree.so

    ANDROID_EXTRA_LIBS += $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libopencv_info.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libopencv_java.so \
$$ANDROID_PACKAGE_SOURCE_DIR/libs/armeabi-v7a/libnonfree.so

    INCLUDEPATH += $$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/
}



contains(ANDROID_TARGET_ARCH,x86) {
    LIBS += $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libopencv_java.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libopencv_info.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libnonfree.so

    ANDROID_EXTRA_LIBS += $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libopencv_java.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libopencv_info.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/libs/x86/libnonfree.so

    INCLUDEPATH += $$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/ \
$$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/opencv \
$$ANDROID_PACKAGE_INCLUDE_DIR/native/jni/include/opencv2

}

OTHER_FILES += \
    android/AndroidManifest.xml
