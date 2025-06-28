#include "Enemy.hpp"
#include <iostream>

using namespace std;

namespace NP 
{
    Enemy::Enemy(int power, const string& art, const string& art_died) : m_power(power), m_art(art), m_art_died(art_died) {}

    void Enemy::setEnemyData(int power, const string& art, const string& art_died) 
    {
        m_power = power;
        m_art = art;
        m_art_died = art_died;
    }

    int Enemy::getTargetPower() const 
    {
        return m_power;
    }

    void Enemy::showPower(ostream& os) const 
    {
        os << "Enemy Target Power: " << m_power << endl;
    }

    void Enemy::showArt(bool show_died_art, ostream& os) const 
    {
        const string& artToDisplay = show_died_art ? m_art_died : m_art;
        if (artToDisplay.empty()) 
        {
            os << "Enemy Art: No " << (show_died_art ? "died" : "idle") << " art available." << endl;
        }
        else 
        {
            os << artToDisplay << endl;
        }
    }
}