#pragma once


#include "npc.h"


class Bear final: public NPC {
public:
    Bear() : NPC() {};
    Bear(const unsigned int x, const unsigned int y, const std::string &name) : NPC(x, y, name) {};

    Bear(Bear &&other) noexcept : NPC(std::move(other)) {};
    Bear(const Bear &other) = default;

    bool accept(std::shared_ptr<NPC> npc_ptr) const override;

    std::string info() const override;
};