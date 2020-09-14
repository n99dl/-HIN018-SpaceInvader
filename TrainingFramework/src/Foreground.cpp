#include "Foreground.h"
#include "ResourceManagers.h"
#include "GameLogic/GameController.h"
#define BOSS_HP_BAR_LENGTH 980 
#define BOSS_HP_SCALE 0.4

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

#define BOSS_BAR_POSITION Vector2(screenWidth / 2.0, screenHeight - 30)



Foreground::Foreground()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("health_bar");
	m_hpBarBackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_hpBarBackGround->SetSize(200, 35);
	m_hpBarBackGround->Set2DPosition(screenWidth - 120, 30);
	//Hp
	Vector2 bg_pos = m_hpBarBackGround->Get2DPosition();
	texture = ResourceManagers::GetInstance()->GetTexture("health_dot");
	for (int i = 0; i < 10; i++)
	{
		auto newSprite = std::make_shared<Sprite2D>(model, shader, texture);
		newSprite->SetSize(15, 29);
		Vector2 Position = Vector2(bg_pos.x - 90, bg_pos.y) + Vector2(15, 0) * i;
		newSprite->Set2DPosition(Position);
		m_hpDots.push_back(newSprite);
	}
	m_Hp = 100;

	//Power
	texture = ResourceManagers::GetInstance()->GetTexture("power_bar");
	m_powerBarBackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_powerBarBackGround->SetSize(200, 35);
	m_powerBarBackGround->Set2DPosition(120, 30);
	bg_pos = m_powerBarBackGround->Get2DPosition();
	texture = ResourceManagers::GetInstance()->GetTexture("power_dot");
	for (int i = 0; i < 1; i++)
	{
		auto newSprite = std::make_shared<Sprite2D>(model, shader, texture);
		newSprite->SetSize(15, 29);
		Vector2 Position = Vector2(bg_pos.x - 90, bg_pos.y) + Vector2(15, 0) * i;
		newSprite->Set2DPosition(Position);
		m_powerDots.push_back(newSprite);
	}
	m_Power = 1;

	//Boss Hp
	//Invisible when no boss
	texture = ResourceManagers::GetInstance()->GetTexture("boss_hp_bg");
	m_bossHpBg = std::make_shared<Sprite2D>(model, shader, texture);
	m_bossHpBg->Set2DPosition(0, - 50);
	m_bossHpBg->SetSize(1040 * BOSS_HP_SCALE, 30 * BOSS_HP_SCALE);
	
	texture = ResourceManagers::GetInstance()->GetTexture("boss_hp_bar");
	m_bossHp = std::make_shared<Sprite2D>(model, shader, texture);
	m_bossHp->Set2DPosition(Vector2(0, -50));
	m_bossHp->SetSize(BOSS_HP_BAR_LENGTH * BOSS_HP_SCALE, 20 * BOSS_HP_SCALE);
	//Wave Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("play_font");
	m_Text_wave = std::make_shared<Text>(shader, font, "Wave 0", TEXT_COLOR::WHILE, 0.8);
	m_Text_wave->Set2DPosition(Vector2(screenWidth / 2.0 + 30, 80));
	//Phase Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("play_font");
	m_Text_phase = std::make_shared<Text>(shader, font, "Phase 0", TEXT_COLOR::WHILE, 0.8);
	m_Text_phase->Set2DPosition(Vector2(100, -100));
}

Foreground::~Foreground()
{
}

void Foreground::Draw()
{
	m_hpBarBackGround->Draw();
	m_bossHpBg->Draw();
	m_bossHp->Draw();
	m_Text_wave->Draw();
	m_Text_phase->Draw();
	for (auto hpDot : m_hpDots)
	{
		hpDot->Draw();
	}
	m_powerBarBackGround->Draw();
	for (auto hpDot : m_powerDots)
	{
		hpDot->Draw();
	}
}

void Foreground::Update(float dt)
{
	int p_Hp = GameController::GetInstance()->GetPlayerHp();
	int p_Power = GameController::GetInstance()->GetPlayerPower();
	while (p_Hp < m_Hp)
	{
		if (m_hpDots.size())
		m_hpDots.pop_back();
		m_Hp -= 10;
	}
	while (p_Hp > m_Hp && m_Hp <= 100)
	{
		Vector2 bg_pos = m_hpBarBackGround->Get2DPosition();
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("health_dot");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto newSprite = std::make_shared<Sprite2D>(model, shader, texture);
		newSprite->SetSize(15, 29);
		Vector2 Position = Vector2(bg_pos.x - 90, bg_pos.y) + Vector2(15, 0) * m_hpDots.size();
		newSprite->Set2DPosition(Position);
		m_hpDots.push_back(newSprite);
		m_Hp += 10;
	}
	while (p_Power > m_Power && m_Power <= 11)
	{
		Vector2 bg_pos = m_powerBarBackGround->Get2DPosition();
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("power_dot");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto newSprite = std::make_shared<Sprite2D>(model, shader, texture);
		newSprite->SetSize(15, 29);
		Vector2 Position = Vector2(bg_pos.x - 90, bg_pos.y) + Vector2(15, 0) * m_powerDots.size();
		newSprite->Set2DPosition(Position);
		m_powerDots.push_back(newSprite);
		m_Power += 1;
	}
	m_hpBarBackGround->Update(dt);
	for (auto hpDot : m_hpDots)
	{
		hpDot->Update(dt);
	}

	m_powerBarBackGround->Update(dt);
	for (auto powerDot : m_powerDots)
	{
		powerDot->Update(dt);
	}
	if (GameController::GetInstance()->IsFightingBoss())
	{
		m_bossHpBg->Set2DPosition(BOSS_BAR_POSITION);
		m_bossHp->Set2DPosition(BOSS_BAR_POSITION);
		int bossPhase = GameController::GetInstance()->GetBossPhase();
		switch (bossPhase)
		{
		case 0:
			break;
		case 1:
			m_Text_phase->setText("First phase !");
			m_Text_phase->Set2DPosition(BOSS_BAR_POSITION - Vector2(53, 30));
			break;
		case 2:
			m_Text_phase->setText("Advanced phase !!");
			m_Text_phase->SetColor(m_Text_phase->EnumToVector(TEXT_COLOR::YELLOW));
			m_Text_phase->Set2DPosition(BOSS_BAR_POSITION - Vector2(63, 30));
			break;
		case 3:
			m_Text_phase->setText("Final phase !!!");
			m_Text_phase->SetColor(m_Text_phase->EnumToVector(TEXT_COLOR::RED));
			m_Text_phase->Set2DPosition(BOSS_BAR_POSITION - Vector2(53, 30));
			break;
		}
		float bossHpScale = GameController::GetInstance()->GetBossHpPercent();
		m_bossHp->SetSize(BOSS_HP_BAR_LENGTH * BOSS_HP_SCALE * bossHpScale, 20 * BOSS_HP_SCALE);
		m_bossHpBg->Update(dt);
		m_bossHp->Update(dt);
		m_Text_wave->Update(dt);
	}

	int wave = GameController::GetInstance()->GetWave();
	if (GameController::GetInstance()->IsFightingBoss())
	{
		m_Text_wave->setText("Imperial Ship Bullet Hell!");
		m_Text_wave->SetColor(m_Text_wave->EnumToVector(TEXT_COLOR::RED));
	}
	else
	{
		switch (wave)
		{
		case 0:
			break;
		case 1:
			m_Text_wave->setText("Wave 1 Straight Enemy");
			break;
		case 2:
			m_Text_wave->setText("Wave 2 Aiming Shooter");
			m_Text_wave->SetColor(m_Text_wave->EnumToVector(TEXT_COLOR::CYAN));
			break;
		case 3:
			m_Text_wave->setText("Wave 3 Formation!");
			m_Text_wave->SetColor(m_Text_wave->EnumToVector(TEXT_COLOR::BLUE));
			break;
		case 4:
			m_Text_wave->setText("Wave 4 Homing captain!");
			m_Text_wave->SetColor(m_Text_wave->EnumToVector(TEXT_COLOR::PURPLE));
			break;
		}
	}
	m_Text_wave->Update(dt);

}
