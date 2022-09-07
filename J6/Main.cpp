﻿# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"


void loadTexture() {
	TextureAsset::Register(U"MrJ", U"img/MrJ.png");
}


void Main()
{
	loadTexture();

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);


	// ゲームシーンから開始したい場合はこのコメントを外す
	manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

