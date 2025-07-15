//==================================================================
//
//パーティクル処理 [particle.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "particle.h"
#include "effect.h"

//================================================
//静的メンバ変数
//================================================
int CParticle::m_ParticleCount = 0;
int CParticle::m_Life = 0;
D3DXCOLOR CParticle::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
D3DXVECTOR3 CParticle::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CParticle::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float CParticle::fRadius = 1.0f;

//================================================
//コンストラクタ
//================================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{

}

//================================================
//デストラクタ
//================================================
CParticle::~CParticle()
{

}

//================================================
//生成処理
//================================================
CParticle* CParticle::Create(float posX, float posY, int ParticleCount)
{
	CParticle* pParticle = new CParticle();
	pParticle->SetPosition(posX, posY, 0.0f);
	pParticle->SetParticleCount(ParticleCount);

	return pParticle;
}

//================================================
//初期化処理
//================================================
HRESULT CParticle::Init(void)
{

    return S_OK;
}

//================================================
//破棄処理
//================================================
void CParticle::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CParticle::Update(void)
{
	for (int nCntParticle = 0; nCntParticle < m_ParticleCount; nCntParticle++)
	{
		//移動量の設定
		int fAngle = (float)(rand() % 629 - 314) / 100.0f;
		int fLength = (float)(rand() % 20) / 10.0f + 0.2f;

		m_move.x = sinf(fAngle) * fLength;
		m_move.y = cosf(fAngle) * fLength;

		//色の指定
		m_col = (1.0f, 1.0f, 1.0f, 1.0f);

		//半径の設定
		fRadius = (float)(rand() % 100) / 10.0f + 0.5f;

		//寿命の設定
		m_Life = (float)(rand() % 1200) / 10.0f + 0.2;

		////エフェクトの設定
		//SetEffect(pos, col, fRadius, nLife, move);

		CEffect::Create(
			CObject2D::TYPE_NORMAL,
			30,
			30,
			0, 0,
			0, 0,
			0,
			m_pos.x, m_pos.y,m_pos.z,
			0.0f,
			0.0f,
			m_Life
		);

	}
}

//================================================
//描画処理
//================================================
void CParticle::Draw(void)
{
}

//================================================
//位置セット処理
//================================================
void CParticle::SetPosition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//================================================
//移動値セット処理
//================================================
void CParticle::SetMove(float x, float y, float z)
{
	m_move.x = x;
	m_move.y = y;
	m_move.z = z;
}

//================================================
//体力セット処理
//================================================
void CParticle::SetLife(int life)
{
	m_Life = life;
}

//================================================
//色セット処理
//================================================
void CParticle::SetColor(float r, float g, float b, float a)
{
	m_col.r = r;
	m_col.g = g;
	m_col.b = b;
	m_col.a = a;
}

//================================================
//半径処理
//================================================
void CParticle::SetRadius(float radius)
{
	fRadius = radius;
}

//================================================
//パーティクル数値セット処理
//================================================
void CParticle::SetParticleCount(int count)
{
	m_ParticleCount = count;
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CParticle::GetPosition(void)
{
    return m_pos;
}

//================================================
//移動値取得処理
//================================================
D3DXVECTOR3 CParticle::GetMove(void)
{
    return m_move;
}

//================================================
//体力取得処理
//================================================
int CParticle::GetLife(void)
{
    return m_Life;
}

//================================================
//色取得処理
//================================================
D3DXCOLOR CParticle::GetColor(void)
{
	return m_col;
}

//================================================
//半径取得処理
//================================================
float CParticle::GetRadius(void)
{
	return fRadius;
}

//================================================
//パーティクル数値取得処理
//================================================
int CParticle::GetParticleCount(void)
{
	return m_ParticleCount;
}

D3DXVECTOR3 CParticle::GetPos(void)
{
	// 必要に応じて適切な値を返す
	return D3DXVECTOR3(m_pos.x, m_pos.y,m_pos.z);
}

int CParticle::GetWidth(void)
{
	// パーティクルの幅（仮に30固定なら30）
	return 30;
}

int CParticle::GetHeight(void)
{
	// パーティクルの高さ（仮に30固定なら30）
	return 30;
}