#pragma once

namespace ORC
{
    class Orc
    {
        private:
            int m_hp;
            int m_atk;
        public:
            Orc();
            void attack();
            void die();
    };
}