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
        if (!this->m_player1) {
            log::warn("No player object found!");
            return;
        }

        auto startPos = this->m_player1->getStartPos();
        auto endPos = this->getEndPosition();

        float songTime = this->timeForPos(startPos, 0, 0, true, -1);
        float levelTime = this->timeForPos(endPos, 0, 0, true, -1);

        this->m_fields->m_startPosPercent = (songTime / levelTime) * 100.0f;
        this->m_fields->active = 0 == PlayLayer::getCurrentPercent();
    }

    float getCurrentPercent() {
        if (!this->m_player1 || this->m_fields->m_startPosPercent < 0.f || !this->m_fields->active)
            return PlayLayer::getCurrentPercent();

        float basePercent = this->m_fields->m_startPosPercent;
        float progressPercent = PlayLayer::getCurrentPercent();
        return basePercent + progressPercent;
    }
};
