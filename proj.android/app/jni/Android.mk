LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameStartScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/MainGameScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameOverScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/MainScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/MainLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/BattleScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/BattleBackgroundLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/HeroLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Bullet.cpp \
                   $(LOCAL_PATH)/../../../Classes/ObjectManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Enemy.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
# LOCAL_STATIC_LIBRARIES += cocosdenshion_static
# LOCAL_STATIC_LIBRARIES += box2d_static
# LOCAL_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_STATIC_LIBRARIES += spine_static
# LOCAL_STATIC_LIBRARIES += cocostudio_static
# LOCAL_STATIC_LIBRARIES += cocos_network_static
# LOCAL_STATIC_LIBRARIES += cocos_extension_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
