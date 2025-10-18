#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/GameObject.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <cocos2d.h>

using namespace geode::prelude;

class $modify(PlayLayer) {
    struct Fields {
        float m_startPosPercent = -1.f;
        bool active = true;
    };

    void resetSPTriggered() {
        PlayLayer::resetSPTriggered();
        this->updateStartPosPercent();
    }

    void updateStartPosPercent() {
        if (!this->m_player1)return;
        if(this->m_isPlatformer)return;
        if (!this->m_startPosObject)return;


        if(!m_level->m_timestamp){
            return;
        }

        float currTime = this->timeForPos(m_startPosObject->getStartPos(), 0, this->m_gameState.m_currentChannel, true, -1);



        this->m_fields->m_startPosPercent = (currTime / (this->m_level->m_timestamp / 240)) * 100.0f;
    }

    float getCurrentPercent() {
        if (!this->m_player1 || this->m_fields->m_startPosPercent < 0.f || !this->m_startPosObject || !m_level->m_timestamp || this->m_isPlatformer)
            return PlayLayer::getCurrentPercent();

        float basePercent = this->m_fields->m_startPosPercent;
        float progressPercent = PlayLayer::getCurrentPercent();
        return basePercent + progressPercent;
    }
};
