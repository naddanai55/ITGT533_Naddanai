#pragma once

#include <iostream>

using namespace std;

namespace NP
{
	class Enemy
	{
	public:
		Enemy(int power = 0, const string& art = "", const string& art_died = "");
		void setEnemyData(int power, const string& art, const string& art_died);
		int getTargetPower() const;
		void showPower(ostream& os = cout) const;
		void showArt(bool show_died_art = false, ostream& os = cout) const;

	private:
		int m_power;
		string m_art;
		string m_art_died;
	};
}